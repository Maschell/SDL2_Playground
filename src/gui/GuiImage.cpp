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
#include <SDL2/SDL_image.h>
#include <iostream>
#include "GuiImage.h"
#include "../CVideo.h"
#include "../logger.h"

GuiImage::GuiImage(const std::string& path) {
    imgSurface = IMG_Load( path.c_str() );

    this->width = imgSurface->w;
    this->height = imgSurface->h;
}

/**
 * Destructor for the GuiImage class.
 */
GuiImage::~GuiImage() {
    if(imgSurface){
        SDL_FreeSurface(imgSurface);
        imgSurface = NULL;
    }
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void GuiImage::process(){
    auto res = this->getAngle() + 1;
    if(res > 360){
        res  =0;
    }

    setAngle(res);

}

void GuiImage::draw(CVideo *pVideo) {
    if (!this->isVisible()) {
        return;
    }

    if(texture == NULL){
        SDL_Surface * optimizedSurface = SDL_ConvertSurfaceFormat( imgSurface, pVideo->getPixelFormat(), 0 );
        if(optimizedSurface != NULL){
            SDL_FreeSurface(imgSurface);
            imgSurface = optimizedSurface;
            DEBUG_FUNCTION_LINE("Optimized surface");
        }
        texture = SDL_CreateTextureFromSurface(pVideo->getRenderer(), imgSurface);
    }

    float currScaleX = getScaleX();
    float currScaleY = getScaleY();

    SDL_Rect rect;
    rect.x = getLeft();
    rect.y = getTop();
    rect.w =  currScaleX * getWidth();
    rect.h = currScaleY * getHeight();


    // copy the texture to the rendering context
    if(getAngle() == 0){
         SDL_RenderCopy(pVideo->getRenderer(), texture, NULL, &rect);
    }else{
        SDL_RenderCopyEx(pVideo->getRenderer(), texture, NULL, &rect, getAngle(), NULL, SDL_FLIP_NONE);
    }


}
