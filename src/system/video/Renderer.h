#pragma once

#include <SDL2/SDL_render.h>

class Renderer {
public:
    enum RendererTarget {
        TARGET_TV   = 0x00,
        TARGET_DRC  = 0x01,
    };

    Renderer(SDL_Renderer *renderer, uint32_t pixelFormat, RendererTarget renderTarget) :
    sdl_renderer(renderer),
    pixelFormat(pixelFormat),
    renderTarget(renderTarget)
    {

    }

    virtual ~Renderer() {
        if(sdl_renderer){
            SDL_DestroyRenderer(sdl_renderer);
        }
    }

    SDL_Renderer *getRenderer(){
        return sdl_renderer;
    }

    uint32_t getPixelFormat(){
        return pixelFormat;
    }

    RendererTarget getTarget(){
        return renderTarget;
    }

private:
    SDL_Renderer *sdl_renderer = NULL;
    uint32_t pixelFormat = SDL_PIXELFORMAT_RGBA8888;
    RendererTarget renderTarget = TARGET_TV;
};