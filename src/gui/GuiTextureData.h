#pragma once

#include <SDL2/SDL_render.h>
#include "GuiElement.h"

class GuiTextureData {
public:
    GuiTextureData(void *buffer, uint32_t filesize, bool freesrc = false);

    explicit GuiTextureData(SDL_Texture *texture);

    explicit GuiTextureData(const std::string &path);

    //!Destructor
    ~GuiTextureData();

    void draw(Renderer *pVideo, const SDL_Rect &rect, float angle);

    int setBlendMode(SDL_BlendMode blendMode);

    [[nodiscard]] int32_t getWidth() const {
        return width;
    }

    [[nodiscard]] int32_t getHeight() const {
        return height;
    }


protected:
    void loadSurface(SDL_Surface *pSurface);

    SDL_Surface *imgSurface = nullptr;

    void cleanUp();

    SDL_Texture *texture = nullptr;
    int32_t width = 0;
    int32_t height = 0;
    SDL_BlendMode blendMode;
};
