#include <SDL2/SDL_image.h>
#include "GuiTexture.h"
#include "../CVideo.h"
#include "../logger.h"

GuiTexture::GuiTexture(const std::string& path) {
    imgSurface = IMG_Load( path.c_str() );

    if(!imgSurface){
        return;
    }
    this->width = imgSurface->w;
    this->height = imgSurface->h;
}


GuiTexture::GuiTexture(SDL_Surface *pSurface) {
    if(!pSurface){
        return;
    }
    imgSurface = pSurface;

    this->width = imgSurface->w;
    this->height = imgSurface->h;
}

/**
 * Destructor for the GuiImage class.
 */
GuiTexture::~GuiTexture() {
    if(imgSurface){
        SDL_FreeSurface(imgSurface);
        imgSurface = NULL;
    }
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void GuiTexture::draw(CVideo *pVideo) {
    if (!this->isVisible()) {
        return;
    }

    if(texture == NULL){
        SDL_Surface * optimizedSurface = SDL_ConvertSurfaceFormat(imgSurface, pVideo->getPixelFormat(), 0 );
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
