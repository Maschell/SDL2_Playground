#pragma once
#include <SDL2/SDL_render.h>
#include "GuiElement.h"

class GuiTexture : public GuiElement {
public:
    explicit GuiTexture(const std::string &path);

    GuiTexture(SDL_Surface *pSurface);

//!Destructor
    ~GuiTexture() override;

    //!Constantly called to draw the image
    void draw(CVideo *pVideo) override;
protected:
    SDL_Surface *imgSurface = nullptr;
    SDL_Texture *texture = nullptr;
};
