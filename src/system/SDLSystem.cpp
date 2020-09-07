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
#include "SDLSystem.h"
#include "../utils/logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

SDLSystem::SDLSystem() {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto SDLFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    //Setup window
    window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    if (!window) {
        DEBUG_FUNCTION_LINE("Failed to create window");
        return;
    }
    auto sdl_renderer = SDL_CreateRenderer(window, -1, SDLFlags);
    if (!sdl_renderer) {
        DEBUG_FUNCTION_LINE("Failed to init sdl renderer");
        return;
    }
    SDL_SetRenderTarget(sdl_renderer, nullptr);
    this->renderer = new Renderer(sdl_renderer, SDL_GetWindowPixelFormat(window));
    if (!renderer) {
        DEBUG_FUNCTION_LINE("Failed to init renderer");
        return;
    }

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

    TTF_Init();
}

SDLSystem::~SDLSystem() {
    SDL_DestroyWindow(window);
    delete renderer;
    SDL_Quit();
}

float SDLSystem::getHeight() {
    int h = 0;
    SDL_GetWindowSize(window, nullptr, &h);
    return h;
}

float SDLSystem::getWidth() {
    int w = 0;
    SDL_GetWindowSize(window, &w, nullptr);
    return w;
}

Renderer *SDLSystem::getRenderer() {
    return renderer;
}
