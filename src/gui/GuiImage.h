/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#pragma once

#include <SDL2/SDL_render.h>
#include "GuiElement.h"
#include "GuiTextureData.h"

//!Display, manage, and manipulate images in the GUI
class GuiImage : public GuiElement {
public:

    GuiImage() = default;

    //! Draws an image from an existing texture
    //!\param texture Pointer to GuiTextureData element
    explicit GuiImage(GuiTextureData *texture);

    //! Draws a colored rectangle
    //!\param texture Pointer to GuiTextureData element
    explicit GuiImage(SDL_Color color, float width, float height);

    //!Destructor
    ~GuiImage() override;

    void draw(Renderer *r) override;

    void setTexture(GuiTextureData *tex);

private:
    GuiTextureData *texture = nullptr;
    bool freeTextureData = false;

    // Color of the rect that's drawn if the picture has no texture.
    SDL_Color color = {0, 0, 0, 0};
};
