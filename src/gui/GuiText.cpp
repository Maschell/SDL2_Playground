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


/**
 * Constructor for the GuiText class.
 */

GuiText::GuiText(const std::string& text, int32_t s, SDL_Color c, TTF_Font* gFont) {
    //Render text surface
    textSurface = TTF_RenderText_Solid( gFont, text.c_str(), c );
    if( textSurface == NULL )    {
        DEBUG_FUNCTION_LINE( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

}

GuiText::~GuiText(){
    if(textSurface){
        SDL_FreeSurface( textSurface );
        textSurface = nullptr;

    }

    if(textTexture){
        SDL_DestroyTexture( textTexture );
        textTexture = nullptr;
    }
}

/**
 * Draw the text on screen
 */
void GuiText::draw(CVideo *pVideo) {
    if (!this->isVisible()) {
        return;
    }

    if(textTexture == NULL){
    //Create texture from surface pixels
    textTexture = SDL_CreateTextureFromSurface( pVideo->getRenderer(), textSurface );
    if( textTexture == NULL ) {
        DEBUG_FUNCTION_LINE( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }else{
        width = textSurface->w;
        height = textSurface->h;
    }

    if(textSurface){
        SDL_FreeSurface( textSurface );
        textSurface = nullptr;
        }
    }

    if(!textTexture){
        return;
    }

    SDL_Rect rect;
    rect.x = getLeft();
    rect.y = getTop();
    rect.w =  getScaleX() * getWidth();
    rect.h = getScaleY() * getHeight();

    // copy the texture to the rendering context
    if(getAngle() == 0){
        SDL_RenderCopy(pVideo->getRenderer(), textTexture, NULL, &rect);
    }else{
        SDL_RenderCopyEx(pVideo->getRenderer(), textTexture, NULL, &rect, getAngle(), NULL, SDL_FLIP_NONE);
    }
}