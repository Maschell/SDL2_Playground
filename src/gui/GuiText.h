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

#include "GuiElement.h"
#include "GuiTextureData.h"
#include "../system/video/SDL_FontCache.h"
#include "GuiImage.h"
#include <mutex>
#include <SDL2/SDL_ttf.h>

//!Display, manage, and manipulate text in the GUI
class GuiText : public GuiElement {
public:

    //!\param t Text
    //!\param s Font size
    //!\param c Font color
    GuiText(const std::string &t, SDL_Color c, FC_Font *font);
    ~GuiText() override;

    void draw(Renderer *pVideo) override;

    void process() override;

    void setMaxWidth(float width);

protected:
    GuiImage texture;
    GuiTextureData* textureData = nullptr;

    std::string text;
    SDL_Color color;
    FC_Font *fc_font = nullptr;
    bool doUpdateTexture = true;

    uint16_t maxWidth = 0xFFFF;

    void updateSize();

    void updateTexture(Renderer *renderer);
};
