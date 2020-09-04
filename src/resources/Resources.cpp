#include <malloc.h>
#include <cstring>
#include <string>
#include "Resources.h"
#include "../fs/FSUtils.h"
#include "../gui/GuiSound.h"
#include "../gui/GuiTextureData.h"

#include <chrono>

#include "filelist.h"
#include "../utils/logger.h"

Resources *Resources::instance = nullptr;

void Resources::Clear() {
    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        if (RecourceList[i].CustomFile) {
            free(RecourceList[i].CustomFile);
            RecourceList[i].CustomFile = nullptr;
        }

        if (RecourceList[i].CustomFileSize != 0) {
            RecourceList[i].CustomFileSize = 0;
        }
    }

    delete instance;

    instance = nullptr;
}

bool Resources::LoadFiles(const char *path) {
    if (!path) {
        return false;
    }

    bool result = false;
    Clear();

    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        std::string fullpath(path);
        fullpath += "/";
        fullpath += RecourceList[i].filename;
        DEBUG_FUNCTION_LINE("%s", fullpath.c_str());

        uint8_t *buffer = nullptr;
        uint32_t filesize = 0;

        auto res = FSUtils::LoadFileToMem(fullpath.c_str(), &buffer, &filesize);
        if (filesize > 0) {
            RecourceList[i].CustomFile = buffer;
            RecourceList[i].CustomFileSize = (uint32_t) filesize;

        }
        result |= (buffer != 0);
    }

    return result;
}

const uint8_t *Resources::GetFile(const char *filename) {
    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        if (strcasecmp(filename, RecourceList[i].filename) == 0) {
            return (RecourceList[i].CustomFile ? RecourceList[i].CustomFile : RecourceList[i].DefaultFile);
        }
    }

    return nullptr;
}

uint32_t Resources::GetFileSize(const char *filename) {
    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        if (strcasecmp(filename, RecourceList[i].filename) == 0) {
            return (RecourceList[i].CustomFile ? RecourceList[i].CustomFileSize : RecourceList[i].DefaultFileSize);
        }
    }
    return 0;
}

GuiTextureData *Resources::GetTexture(const char *filename) {
    if (!instance) {
        instance = new Resources;
    }

    auto itr = instance->textureDataMap.find(std::string(filename));
    if (itr != instance->textureDataMap.end()) {
        itr->second.first++;
        return itr->second.second;
    }

    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        if (strcasecmp(filename, RecourceList[i].filename) == 0) {
            const uint8_t *buff = RecourceList[i].CustomFile ? RecourceList[i].CustomFile : RecourceList[i].DefaultFile;
            const uint32_t size = RecourceList[i].CustomFile ? RecourceList[i].CustomFileSize : RecourceList[i].DefaultFileSize;

            if (buff == nullptr) {
                return nullptr;
            }

            auto *image = new GuiTextureData((void *) buff, size, false);
            instance->textureDataMap[std::string(filename)].first = 1;
            instance->textureDataMap[std::string(filename)].second = image;

            return image;
        }
    }

    return nullptr;
}

bool Resources::RemoveTexture(GuiTextureData *image) {
    std::map<std::string, std::pair<uint32_t, GuiTextureData *> >::iterator itr;

    for (itr = instance->textureDataMap.begin(); itr != instance->textureDataMap.end(); itr++) {
        if (itr->second.second == image) {
            itr->second.first--;

            if (itr->second.first == 0) {
                delete itr->second.second;
                // AsyncExecutor::pushForDelete(itr->second.second);

                instance->textureDataMap.erase(itr);
            }
            return true;
        }
    }
    return false;
}

GuiSound *Resources::GetSound(const char *filename) {
    if (!instance) {
        instance = new Resources;
    }

    auto itr = instance->soundDataMap.find(std::string(filename));
    if (itr != instance->soundDataMap.end()) {
        itr->second.first++;
        return itr->second.second;
    }

    for (int32_t i = 0; RecourceList[i].filename != nullptr; ++i) {
        if (strcasecmp(filename, RecourceList[i].filename) == 0) {
            const uint8_t *buff = RecourceList[i].CustomFile ? RecourceList[i].CustomFile : RecourceList[i].DefaultFile;
            const uint32_t size = RecourceList[i].CustomFile ? RecourceList[i].CustomFileSize : RecourceList[i].DefaultFileSize;

            if (buff == nullptr) {
                return nullptr;
            }

            auto *sound = new GuiSound((void *) buff, size);
            instance->soundDataMap[std::string(filename)].first = 1;
            instance->soundDataMap[std::string(filename)].second = sound;

            return sound;
        }
    }

    return nullptr;
}

void Resources::RemoveSound(GuiSound *sound) {
    std::map<std::string, std::pair<uint32_t, GuiSound *> >::iterator itr;

    for (itr = instance->soundDataMap.begin(); itr != instance->soundDataMap.end(); itr++) {
        if (itr->second.second == sound) {
            itr->second.first--;

            if (itr->second.first == 0) {
                // AsyncExecutor::pushForDelete(itr->second.second);
                delete itr->second.second;
                instance->soundDataMap.erase(itr);
            }
            break;
        }
    }
}
