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
#include "glm/glm.hpp"

//!Display, manage, and manipulate images in the GUI
class GuiImage : public GuiElement {
public:
    //!\overload
    //!\param img Pointer to GuiImageData element
    explicit GuiImage(const std::string &path);

    //!Destructor
    ~GuiImage() override;

    //!Constantly called to draw the image
    void draw(CVideo *pVideo) override;
protected:
    SDL_Surface *imgSurface = nullptr;
    SDL_Texture *texture = nullptr;

    void process() override;
};
