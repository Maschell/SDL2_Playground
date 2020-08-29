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
#include "GuiSound.h"
#include "../logger.h"

GuiSound::GuiSound(const char *filepath) {
    Load(filepath);
}

GuiSound::~GuiSound() {
    if(music){
        Mix_FreeChunk(music);
    }
}


bool GuiSound::Load(const char *filepath) {
    music = Mix_LoadWAV(filepath);
    DEBUG_FUNCTION_LINE("load %s %d", filepath, music);
    return music != nullptr;
}



void GuiSound::Play() {
    playedOn = Mix_PlayChannel(-1,music, loops);
}

void GuiSound::Stop() {
    Pause();
}

void GuiSound::Pause() {
    Mix_HaltChannel(playedOn);
}

void GuiSound::Resume() {
    Play();
}

bool GuiSound::IsPlaying() {
    if(playedOn == -1){
        return false;
    }
    return Mix_Playing(playedOn);
}

void GuiSound::SetVolume(uint32_t vol) {
    if(music != nullptr){
        Mix_VolumeChunk(music, vol);
    }
}

void GuiSound::SetLoop(bool l) {
    if(l){
        loops = -1;
    }else{
        loops = 1;
    }
}

void GuiSound::Rewind() {
    Stop();
}
