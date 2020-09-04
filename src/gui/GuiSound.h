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
#pragma once

#include "GuiElement.h"
#include <SDL2/SDL_mixer.h>

//!Sound conversion and playback. A wrapper for other sound libraries - ASND, libmad, ltremor, etc
class GuiSound : public GuiElement {
public:
    explicit GuiSound(const char *filepath);

    //!Constructor
    //!\param sound Pointer to the sound data
    //!\param filesize Length of sound data
    GuiSound(void *buffer, uint32_t filesize, bool freeSrc = false);

    //!Destructor
    ~GuiSound() override;

    //!Load a file and replace the old one
    bool Load(const char *filepath);

    //!Start sound playback
    void Play();

    //!Stop sound playback
    void Stop() const;

    //!Pause sound playback
    void Pause() const;

    //!Resume sound playback
    void Resume();

    //!Checks if the sound is currently playing
    //!\return true if sound is playing, false otherwise
    [[nodiscard]] bool IsPlaying() const;

    //!Rewind the music
    void Rewind() const;

    //!Set sound volume
    //!\param v Sound volume (0-100)
    void SetVolume(uint32_t v) const;

    //!\param l Loop (true to loop)
    void SetLoop(bool l);

    Mix_Chunk *music = nullptr;
    int32_t loops = 0;
    int32_t playedOn = -1;
};