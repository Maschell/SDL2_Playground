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
#include "CVideo.h"
#include "logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

CVideo::CVideo() {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto SDLFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    //Setup window
    window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    if (!window) { return; }
    renderer = SDL_CreateRenderer(window, -1, SDLFlags);
    if (!renderer) { return; }
    SDL_SetRenderTarget(renderer, NULL);

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        DEBUG_FUNCTION_LINE("SDL init error: %s\n", SDL_GetError());
        return;
    }

    int flags = 0;
    int result = 0;
    if (flags != (result = Mix_Init(flags))) {
        DEBUG_FUNCTION_LINE("Could not initialize mixer (result: %d).\n", result);
        DEBUG_FUNCTION_LINE("Mix_Init: %s\n", Mix_GetError());
    }

    auto dev = Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    SDL_PauseAudioDevice(dev, 0);
}

CVideo::~CVideo() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer *CVideo::getRenderer() {
    return renderer;
}

float CVideo::getHeight() {
    int h = 0;
    SDL_GetWindowSize(window, NULL, &h);
    return h;
}

float CVideo::getWidth() {
    int w = 0;
    SDL_GetWindowSize(window, &w, NULL);
    return w;
}

unsigned int CVideo::getPixelFormat() {
    return SDL_GetWindowPixelFormat(window);
}
