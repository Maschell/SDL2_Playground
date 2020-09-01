#pragma once

#include <SDL2/SDL_render.h>

class Renderer {
public:
    Renderer(SDL_Renderer *renderer, uint32_t pixelFormat) : sdl_renderer(renderer), pixelFormat(pixelFormat){

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

private:
    SDL_Renderer *sdl_renderer = NULL;
    uint32_t pixelFormat = SDL_PIXELFORMAT_RGBA8888;
};