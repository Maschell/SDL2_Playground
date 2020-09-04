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
#include <SDL2/SDL_image.h>
#include "GuiImage.h"
#include "../utils/logger.h"

GuiImage::GuiImage(GuiTextureData *texture) {
    setTexture(texture);
}

GuiImage::~GuiImage() {
    if(this->texture && freeTextureData){
        delete this->texture;
    }
}

void GuiImage::draw(Renderer *renderer) {
    if (!this->isVisible()) {
        return;
    }

    if (texture) {
        SDL_Rect rect;
        rect.x = (int) getLeft();
        rect.y = (int) getTop();
        rect.w = (int) (getScaleX() * getWidth());
        rect.h = (int) (getScaleY() * getHeight());
        texture->draw(renderer, rect, getAngle());
    }
}

void GuiImage::setTexture(GuiTextureData *tex) {
    if (tex) {
        if(this->texture && freeTextureData){
            delete this->texture;
        }
        this->texture = tex;
        this->setSize(tex->getWidth(), tex->getHeight());
    }
}
