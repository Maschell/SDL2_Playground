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
#include "../CVideo.h"
#include "../logger.h"
#include "SDL_FontCache.h"


/**
 * Constructor for the GuiText class.
 */

GuiText::GuiText(const std::string& text, int32_t s, SDL_Color c, TTF_Font* gFont) {
   this->text = text;
   this->size = s;
   this->color = c;
   this->ttf_font = gFont;
   this->invalid = true;
   this->updateText = true;
   this->maxWidth = 200;
}

GuiText::~GuiText(){
    if(fc_font){
        FC_FreeFont(fc_font);
        fc_font = nullptr;
    }
    delete texture;
}

void GuiText::draw(CVideo *pVideo) {
    if (!this->isVisible()) {
        return;
    }
    if(invalid){
        if(fc_font){
            FC_FreeFont(fc_font);
            fc_font = nullptr;
        }
        fc_font = FC_CreateFont();
        invalid = !FC_LoadFontFromTTF(fc_font, pVideo->getRenderer(), this->ttf_font, color);
        DEBUG_FUNCTION_LINE("FC_CACHE init done");
    }

    if(updateText || !texture){
        delete texture;
        // Create the intermediate texture target
        SDL_Texture* temp = SDL_CreateTexture(pVideo->getRenderer(), pVideo->getPixelFormat(), SDL_TEXTUREACCESS_TARGET, width, height);
        if(temp){
            texture = new GuiTexture(temp);
            texture->setParent(this);
            texture->setBlend(SDL_BLENDMODE_BLEND);

            // Draw the text onto it
            SDL_SetRenderTarget(pVideo->getRenderer(), temp);
            SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);
            FC_DrawColumn(fc_font, pVideo->getRenderer(), 0, 0, maxWidth, text.c_str());
            SDL_SetRenderTarget(pVideo->getRenderer(), NULL);

            updateText = false;
        }else{
            DEBUG_FUNCTION_LINE("Failed to create texture");
        }

    }

    if(texture){
        texture->draw(pVideo);
    }
}

void GuiText::process() {
    GuiElement::process();

    if(updateText && fc_font){
        auto height = FC_GetColumnHeight(fc_font, maxWidth, text.c_str());
        auto width = FC_GetWidth(fc_font, text.c_str());
        width = width > maxWidth ? maxWidth : width;
        this->setSize(width, height);
    }
}

void GuiText::setMaxWidth(float width) {
    this->maxWidth = width;
    // Rebuild the texture cache.
    updateText = true;
}
