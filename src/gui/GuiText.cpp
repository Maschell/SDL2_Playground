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
#include <cstdarg>
#include <SDL2/SDL_surface.h>
#include "GuiText.h"

/**
 * Constructor for the GuiText class.
 */

GuiText::GuiText(const std::string& text, SDL_Color c, FC_Font* gFont) {
   this->text = text;
   this->color = c;
   this->fc_font = gFont;
   updateSize();
   this->doUpdateTexture = true;
}

GuiText::~GuiText(){
    if(fc_font){
        FC_FreeFont(fc_font);
        fc_font = nullptr;
    }
    delete texture;
}

void GuiText::draw(Renderer *renderer) {
    if (!this->isVisible()) {
        return;
    }

    updateTexture(renderer);

    if(texture){
        texture->draw(renderer);
    }
}

void GuiText::process() {
    GuiElement::process();
}

void GuiText::setMaxWidth(float width) {
    this->maxWidth = width;

    // Rebuild the texture cache.
    doUpdateTexture = true;
}

void GuiText::updateSize() {
    auto height = FC_GetColumnHeight(fc_font, maxWidth, text.c_str());
    auto width = FC_GetWidth(fc_font, text.c_str());
    width = width > maxWidth ? maxWidth : width;
    this->setSize(width, height);
}

void GuiText::updateTexture(Renderer *renderer) {
    if(!texture || doUpdateTexture) {
        updateSize();

        SDL_Texture *temp = SDL_CreateTexture(renderer->getRenderer(), renderer->getPixelFormat(), SDL_TEXTUREACCESS_TARGET, (int) width, (int) height);
        if (temp) {
            delete texture;
            texture = new GuiTexture(temp);
            texture->setParent(this);
            texture->setBlendMode(SDL_BLENDMODE_BLEND);

            FC_DrawColumnToTexture(fc_font, temp, 0, 0, maxWidth, text.c_str());
            doUpdateTexture = false;
        } else {
            DEBUG_FUNCTION_LINE("Failed to create texture");
        }
    }
}
