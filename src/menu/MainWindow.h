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

#include <vector>
#include <queue>
#include "../gui/sigslot.h"
#include "../gui/GuiElement.h"
#include "../gui/GuiFrame.h"
#include "../gui/GuiSound.h"

class Renderer;

class MainWindow : public sigslot::has_slots<> {
public:
    explicit MainWindow(SDLSystem* sdlSystem);
    ~MainWindow() override;

    void draw();

    void update(GuiController *controller);
    void updateEffects();
    void process();

private:
    int32_t width, height;

    GuiFrame * currentTvFrame;
    GuiFrame * currentDrcFrame;
    SDLSystem* sdlSystem;
    GuiSound* bgMusic;
};