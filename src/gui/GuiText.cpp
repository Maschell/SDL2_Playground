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
   this->doUpdateTexture = true;
   this->texture.setParent(this);
}

GuiText::~GuiText() {
    delete textureData;
}

void GuiText::draw(Renderer *renderer) {
    if (!this->isVisible()) {
        return;
    }

    updateTexture(renderer);

    texture.draw(renderer);
}

void GuiText::process() {
    GuiElement::process();
}

void GuiText::setMaxWidth(float width) {
    this->maxWidth = width;

    // Rebuild the texture cache on next draw
    doUpdateTexture = true;
}

void GuiText::updateSize() {
    auto height = FC_GetColumnHeight(fc_font, maxWidth, text.c_str());
    auto width = FC_GetWidth(fc_font, text.c_str());
    width = width > maxWidth ? maxWidth : width;
    this->setSize(width, height);
}

void GuiText::updateTexture(Renderer *renderer) {
    if(doUpdateTexture) {
        updateSize();
        int tex_width = tex_width = width == 0 ? 1 : (int) width;
        int tex_height = tex_height = height == 0 ? 1 : (int)height;

        SDL_Texture *temp = SDL_CreateTexture(renderer->getRenderer(), renderer->getPixelFormat(), SDL_TEXTUREACCESS_TARGET, tex_width, tex_height);
        if (temp) {
            texture.setTexture(nullptr);
            delete textureData;
            textureData = new GuiTextureData(temp);
            textureData->setBlendMode(SDL_BLENDMODE_BLEND);
            texture.setTexture(textureData);

            // Set render target to texture
            SDL_SetRenderTarget(renderer->getRenderer(), temp);

            // Clear texture.
            SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 0);
            SDL_RenderClear(renderer->getRenderer());

            // Draw text to texture
            FC_DrawColumn(fc_font, renderer->getRenderer(), 0, 0, maxWidth, text.c_str());

            // Restore render target
            SDL_SetRenderTarget(renderer->getRenderer(), nullptr);
        } else {
            DEBUG_FUNCTION_LINE("Failed to create texture");
        }
        doUpdateTexture = false;
    }
}
