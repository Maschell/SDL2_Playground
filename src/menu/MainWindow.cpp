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
#include <string>
#include "MainWindow.h"
#include "../gui/GuiImage.h"
#include "MainWindowTV.h"
#include "../resources/Resources.h"
#include "MainWindowDRC.h"

MainWindow::MainWindow(SDLSystem* sdlSystem):
    sdlSystem(sdlSystem){

    if(TTF_Init() < 0){
        DEBUG_FUNCTION_LINE("Failed to init TTF");
    }

    currentTvFrame = new MainWindowTV(sdlSystem->getWidth(), sdlSystem->getHeight(), sdlSystem->getRendererTV());
    currentDrcFrame = new MainWindowDRC(sdlSystem->getWidth(), sdlSystem->getHeight(), sdlSystem->getRendererDRC());

    auto bgMusic_path = "bgMusic.ogg";

    bgMusic = Resources::GetSound(Renderer::TARGET_TV, bgMusic_path);
    if(!bgMusic){
        DEBUG_FUNCTION_LINE("Failed to load %s", bgMusic_path);
        return;
    }
    bgMusic->SetLoop(true);
    bgMusic->Play();

}

MainWindow::~MainWindow() {
    delete currentTvFrame;
    delete currentDrcFrame;
    Resources::RemoveSound(Renderer::TARGET_TV, bgMusic);
}

void MainWindow::updateEffects() {
    currentTvFrame->updateEffects();
    currentDrcFrame->updateEffects();
}

void MainWindow::process() {
    currentTvFrame->process();
    currentDrcFrame->process();
}

void MainWindow::update(GuiController *controller) {
    currentTvFrame->update(controller);
    currentDrcFrame->update(controller);
}

void MainWindow::draw() {
    SDL_RenderClear(sdlSystem->getRendererTV()->getRenderer());
    currentTvFrame->draw(sdlSystem->getRendererTV());
    SDL_RenderPresent(sdlSystem->getRendererTV()->getRenderer());

    SDL_RenderClear(sdlSystem->getRendererDRC()->getRenderer());
    currentDrcFrame->draw(sdlSystem->getRendererDRC());
    SDL_RenderPresent(sdlSystem->getRendererDRC()->getRenderer());
}