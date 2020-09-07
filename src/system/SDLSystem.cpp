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
#ifdef __WIIU__
#include <gx2/display.h>
#endif

SDLSystem::SDLSystem() {
    SDL_Init(SDL_INIT_EVERYTHING);

    int width = 1280;
    int height = 720;

    auto SDLFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

#ifdef __WIIU__
    window_tv = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_WIIU_TV_ONLY);
#else
    window_tv = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
#endif

    //Setup window
    if (!window_tv) {
        DEBUG_FUNCTION_LINE("Failed to create window");
        return;
    }
    auto sdl_renderer_tv = SDL_CreateRenderer(window_tv, -1, SDLFlags);
    if (!sdl_renderer_tv) {
        DEBUG_FUNCTION_LINE("Failed to init sdl renderer");
        return;
    }
    SDL_SetRenderTarget(sdl_renderer_tv, nullptr);
    this->renderer_tv = new Renderer(sdl_renderer_tv, SDL_GetWindowPixelFormat(window_tv), Renderer::TARGET_TV);
    if (!renderer_tv) {
        DEBUG_FUNCTION_LINE("Failed to init renderer_tv");
        return;
    }

#ifdef __WIIU__
    window_drc = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_WIIU_GAMEPAD_ONLY );
#else
    window_drc = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
#endif

    //Setup window
    if (!window_drc) {
        DEBUG_FUNCTION_LINE("Failed to create window");
        return;
    }
    auto sdl_renderer_drc = SDL_CreateRenderer(window_drc, -1, SDLFlags);
    if (!sdl_renderer_drc) {
        DEBUG_FUNCTION_LINE("Failed to init sdl renderer");
        return;
    }
    SDL_SetRenderTarget(sdl_renderer_drc, nullptr);
    this->renderer_drc = new Renderer(sdl_renderer_drc, SDL_GetWindowPixelFormat(window_drc), Renderer::TARGET_DRC);
    if (!renderer_drc) {
        DEBUG_FUNCTION_LINE("Failed to init renderer_tv");
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
}

SDLSystem::~SDLSystem() {
    SDL_DestroyWindow(window_tv);
    SDL_DestroyWindow(window_drc);
    delete renderer_tv;
    delete renderer_drc;
    SDL_Quit();
}

float SDLSystem::getHeight() {
    int h = 0;
    SDL_GetWindowSize(window_tv, nullptr, &h);
    return h;
}

float SDLSystem::getWidth() {
    int w = 0;
    SDL_GetWindowSize(window_tv, &w, nullptr);
    return w;
}

Renderer *SDLSystem::getRendererTV() {
    return renderer_tv;
}

Renderer *SDLSystem::getRendererDRC() {
    return renderer_drc;
}
