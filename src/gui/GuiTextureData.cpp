#include <SDL2/SDL_image.h>
#include "GuiTextureData.h"
#include "../system/SDLSystem.h"
#include "../utils/logger.h"

GuiTextureData::GuiTextureData(const std::string& path) {
    SDL_Surface *surface = IMG_Load_RW(SDL_RWFromFile(path.c_str(), "rb"), 1);
    loadSurface(surface);
}

GuiTextureData::GuiTextureData(void *buffer, const uint32_t filesize, bool freesrc)  {
    SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
    SDL_Surface *surface = IMG_Load_RW(rw, freesrc);
    loadSurface(surface);
}

GuiTextureData::GuiTextureData(SDL_Texture *texture) {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
    this->texture = texture;
    int w, h;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &w, &h);
    this->width = w;
    this->height = h;
}

void GuiTextureData::loadSurface(SDL_Surface *pSurface) {
    if(!pSurface){
        return;
    }

    cleanUp();

    imgSurface = pSurface;

    this->width = imgSurface->w;
    this->height = imgSurface->h;
}

void GuiTextureData::cleanUp() {
    if (imgSurface) {
        SDL_FreeSurface(imgSurface);
        imgSurface = nullptr;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

/**
 * Destructor for the GuiImage class.
 */
GuiTextureData::~GuiTextureData() {
    cleanUp();
}

void GuiTextureData::draw(Renderer *renderer, const SDL_Rect& dest, float angle) {
    if (texture == nullptr && imgSurface) {
        texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), imgSurface);
    }
    if (!texture) {
        DEBUG_FUNCTION_LINE("no texture!");
        return;
    }

    // copy the texture to the rendering context
    SDL_BlendMode mode;
    SDL_GetRenderDrawBlendMode(renderer->getRenderer(), &mode);

    // adjust blend mode
    if(blendMode != mode){
        SDL_SetRenderDrawBlendMode(renderer->getRenderer(), blendMode);
    }

    if (angle == 0) {
        SDL_RenderCopy(renderer->getRenderer(), texture, nullptr, &dest);
    } else {
        SDL_RenderCopyEx(renderer->getRenderer(), texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
    }

    if(blendMode != mode){
        SDL_SetRenderDrawBlendMode(renderer->getRenderer(), mode);
    }
}

int GuiTextureData::setBlendMode(SDL_BlendMode blendMode) {
    this->blendMode = blendMode;
    if(texture){ return SDL_SetTextureBlendMode(texture, blendMode); }
    return SDL_BLENDMODE_INVALID;
}