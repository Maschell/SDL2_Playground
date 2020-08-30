#pragma once
#include <SDL2/SDL_render.h>
#include "GuiElement.h"

class GuiTexture : public GuiElement {
public:
    explicit GuiTexture(const std::string &path);
    explicit GuiTexture(SDL_Texture * texture);
    explicit GuiTexture(SDL_Surface *pSurface);

//!Destructor
    ~GuiTexture() override;

    //!Constantly called to draw the image
    void draw(CVideo *pVideo) override;

    int setBlendMode(SDL_BlendMode blendMode);

protected:
    SDL_Surface *imgSurface = nullptr;
    SDL_Texture *texture = nullptr;
};
