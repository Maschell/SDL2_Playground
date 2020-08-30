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

GuiTexture::GuiTexture(SDL_Texture *texture) {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    this->texture = texture;
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    this->setSize(w, h);

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
    if (this->imgSurface) {
        SDL_FreeSurface(this->imgSurface);
        this->imgSurface = nullptr;
    }
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

void GuiTexture::draw(CVideo *pVideo) {
    if (!this->isVisible()) {
        DEBUG_FUNCTION_LINE("not visible!");
        return;
    }

    if (texture == NULL && imgSurface) {
        SDL_Surface *optimizedSurface = SDL_ConvertSurfaceFormat(imgSurface, pVideo->getPixelFormat(), 0);
        if (optimizedSurface != NULL) {
            SDL_FreeSurface(imgSurface);
            imgSurface = optimizedSurface;
            DEBUG_FUNCTION_LINE("Optimized surface");
        }
        texture = SDL_CreateTextureFromSurface(pVideo->getRenderer(), imgSurface);
    }
    if (!texture) {
        DEBUG_FUNCTION_LINE("no texture!");
        return;
    }

    float currScaleX = getScaleX();
    float currScaleY = getScaleY();

    SDL_Rect rect;
    rect.x = getLeft();
    rect.y = getTop();
    rect.w = currScaleX * getWidth();
    rect.h = currScaleY * getHeight();

    if (getAngle() == 0) {
        SDL_RenderCopy(pVideo->getRenderer(), texture, nullptr, &rect);
    } else {
        SDL_RenderCopyEx(pVideo->getRenderer(), texture, nullptr, &rect, getAngle(), nullptr, SDL_FLIP_NONE);
    }
}

int GuiTexture::setBlendMode(SDL_BlendMode) {
    if(texture){
        return SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
    return SDL_BLENDMODE_INVALID;
}
