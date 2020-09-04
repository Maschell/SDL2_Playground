#pragma once

#include <map>
#include <string>
#include <cstdint>

//! forward declaration
class GuiTextureData;

class GuiSound;

typedef struct RecourceFile
{
    const char          *filename;
    const unsigned char *DefaultFile;
    const unsigned int  &DefaultFileSize;
    unsigned char	    *CustomFile;
    unsigned int        CustomFileSize;
} RecourceFile;

class Resources {
public:
    static void Clear();

    static bool LoadFiles(const char *path);

    static const uint8_t *GetFile(const char *filename);

    static uint32_t GetFileSize(const char *filename);

    static GuiTextureData *GetTexture(const char *filename);

    static bool RemoveTexture(GuiTextureData *image);

    static GuiSound *GetSound(const char *filename);

    static void RemoveSound(GuiSound *sound);

private:
    static Resources *instance;

    Resources() {}

    ~Resources() {}

    std::map<std::string, std::pair<uint32_t, GuiTextureData *> > textureDataMap;
    std::map<std::string, std::pair<uint32_t, GuiSound *> > soundDataMap;
};