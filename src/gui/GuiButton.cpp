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
#include <iostream>
#include "GuiButton.h"
#include "GuiController.h"

/**
 * Constructor for the GuiButton class.
 */

GuiButton::GuiButton(float w, float h) {
    width = w;
    height = h;
    image = nullptr;
    imageOver = nullptr;
    imageHold = nullptr;
    imageClick = nullptr;
    icon = nullptr;
    iconOver = nullptr;

    for (int32_t i = 0; i < 4; i++) {
        label[i] = nullptr;
        labelOver[i] = nullptr;
        labelHold[i] = nullptr;
        labelClick[i] = nullptr;
    }
    for (auto &i : trigger) {
        i = nullptr;
    }

    soundOver = nullptr;
    soundHold = nullptr;
    soundClick = nullptr;
    clickedTrigger = nullptr;
    heldTrigger = nullptr;
    selectable = true;
    holdable = false;
    clickable = true;
}

/**
 * Destructor for the GuiButton class.
 */
GuiButton::~GuiButton() = default;

void GuiButton::setImage(GuiImage *img) {
    image = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setImageOver(GuiImage *img) {
    imageOver = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setImageHold(GuiImage *img) {
    imageHold = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setImageClick(GuiImage *img) {
    imageClick = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setIcon(GuiImage *img) {
    icon = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setIconOver(GuiImage *img) {
    iconOver = img;
    if (img) { img->setParent(this); }
}

void GuiButton::setLabel(GuiText *txt, int32_t n) {
    label[n] = txt;
    if (txt) { txt->setParent(this); }
}

void GuiButton::setLabelOver(GuiText *txt, int32_t n) {
    labelOver[n] = txt;
    if (txt) { txt->setParent(this); }
}

void GuiButton::setLabelHold(GuiText *txt, int32_t n) {
    labelHold[n] = txt;
    if (txt) { txt->setParent(this); }
}

void GuiButton::setLabelClick(GuiText *txt, int32_t n) {
    labelClick[n] = txt;
    if (txt) { txt->setParent(this); }
}

void GuiButton::setSoundOver(GuiSound *snd) {
    soundOver = snd;
}

void GuiButton::setSoundHold(GuiSound *snd) {
    soundHold = snd;
}

void GuiButton::setSoundClick(GuiSound *snd) {
    soundClick = snd;
}

void GuiButton::setTrigger(GuiTrigger *t, int32_t idx) {
    if (idx >= 0 && idx < iMaxGuiTriggers) {
        trigger[idx] = t;
    } else {
        for (auto &i : trigger) {
            if (!i) {
                i = t;
                break;
            }
        }
    }
}

void GuiButton::resetState() {
    clickedTrigger = nullptr;
    heldTrigger = nullptr;
    GuiElement::resetState();
}

/**
 * Draw the button on screen
 */
void GuiButton::draw(Renderer *v) {
    if (!this->isVisible()) {
        return;
    }

    // draw image
    if ((isDrawOverOnlyWhenSelected() && (isStateSet(STATE_SELECTED) && imageOver)) ||
        (!isDrawOverOnlyWhenSelected() && (isStateSet(STATE_OVER | STATE_SELECTED | STATE_CLICKED | STATE_HELD) && imageOver))) {
        imageOver->draw(v);
    } else if (image) {
        image->draw(v);
    }

    if ((isDrawOverOnlyWhenSelected() && (isStateSet(STATE_SELECTED) && iconOver)) ||
        (!isDrawOverOnlyWhenSelected() && (isStateSet(STATE_OVER | STATE_SELECTED | STATE_CLICKED | STATE_HELD) && iconOver))) {
        iconOver->draw(v);
    } else if (icon) {
        icon->draw(v);
    }

    // draw text
    for (int32_t i = 0; i < 4; i++) {
        if (isStateSet(STATE_OVER | STATE_SELECTED | STATE_CLICKED | STATE_HELD) && labelOver[i]) {
            labelOver[i]->draw(v);
        } else if (label[i]) {
            label[i]->draw(v);
        }
    }
}

void GuiButton::update(GuiController *c) {
    if (!c || isStateSet(STATE_DISABLED | STATE_HIDDEN | STATE_DISABLE_INPUT, c->chanIdx)) {
        return;
    } else if (parentElement && (parentElement->isStateSet(STATE_DISABLED | STATE_HIDDEN | STATE_DISABLE_INPUT, c->chanIdx))) {
        return;
    }

    if (selectable) {
        if (c->data.validPointer && this->isInside(c->data.x, c->data.y)) {
            if (!isStateSet(STATE_OVER, c->chanIdx)) {
                setState(STATE_OVER, c->chanIdx);

                //if(this->isRumbleActive())
                //	this->rumble(t->chan);

                if (soundOver) {
                    soundOver->Play();
                }

                if (effectsOver && !effects) {
                    // initiate effects
                    effects = effectsOver;
                    effectAmount = effectAmountOver;
                    effectTarget = effectTargetOver;
                }

                pointedOn(this, c);
            }
        } else if (isStateSet(STATE_OVER, c->chanIdx)) {
            this->clearState(STATE_OVER, c->chanIdx);
            pointedOff(this, c);

            if (effectTarget == effectTargetOver && effectAmount == effectAmountOver) {
                // initiate effects (in reverse)
                effects = effectsOver;
                effectAmount = -effectAmountOver;
                effectTarget = 100;
            }
        }
    }

    for (auto & i : trigger) {
        if (!i) {
            continue;
        }

        // button triggers
        if (clickable) {
            int32_t isClicked = i->clicked(c);
            if (!clickedTrigger && (isClicked != GuiTrigger::CLICKED_NONE)
                && (i->isClickEverywhere() || (isStateSet(STATE_SELECTED | STATE_OVER, c->chanIdx) && i->isSelectionClickEverywhere()) || this->isInside(c->data.x, c->data.y))) {
                if (soundClick) {
                    soundClick->Play();
                }

                clickedTrigger = i;

                if (!isStateSet(STATE_CLICKED, c->chanIdx)) {
                    if (isClicked == GuiTrigger::CLICKED_TOUCH) {
                        setState(STATE_CLICKED_TOUCH, c->chanIdx);
                    } else {
                        setState(STATE_CLICKED, c->chanIdx);
                    }
                }

                clicked(this, c, i);
            } else if ((isStateSet(STATE_CLICKED, c->chanIdx) || isStateSet(STATE_CLICKED_TOUCH, c->chanIdx)) && (clickedTrigger == i) && !isStateSet(STATE_HELD, c->chanIdx) && !i->held(c) &&
                       ((isClicked == GuiTrigger::CLICKED_NONE) || i->released(c))) {
                if ((isStateSet(STATE_CLICKED_TOUCH, c->chanIdx) && this->isInside(c->data.x, c->data.y)) || (isStateSet(STATE_CLICKED, c->chanIdx))) {
                    clickedTrigger = nullptr;
                    clearState(STATE_CLICKED, c->chanIdx);
                    released(this, c, i);
                }
            }
        }

        if (holdable) {
            bool isHeld = i->held(c);

            if ((!heldTrigger || heldTrigger == i) && isHeld
                && (i->isHoldEverywhere() || (isStateSet(STATE_SELECTED | STATE_OVER, c->chanIdx) && i->isSelectionClickEverywhere()) || this->isInside(c->data.x, c->data.y))) {
                heldTrigger = i;

                if (!isStateSet(STATE_HELD, c->chanIdx)) {
                    setState(STATE_HELD, c->chanIdx);
                }

                held(this, c, i);
            } else if (isStateSet(STATE_HELD, c->chanIdx) && (heldTrigger == i) && (!isHeld || i->released(c))) {
                //! click is removed at this point and converted to held
                if (clickedTrigger == i) {
                    clickedTrigger = nullptr;
                    clearState(STATE_CLICKED, c->chanIdx);
                }
                heldTrigger = nullptr;
                clearState(STATE_HELD, c->chanIdx);
                released(this, c, i);
            }
        }
    }
}

void GuiButton::process() {
    GuiElement::process();

    if(image) { image->process(); }
    if(imageOver) { imageOver->process(); }
    if(imageHold) { imageHold->process(); }
    if(imageClick) { imageClick->process(); }
    if(icon) { icon->process(); }
    if(iconOver) { iconOver->process(); }
    if(soundOver) { soundOver->process(); }
    if(soundHold) { soundHold->process(); }
    if(soundClick) { soundClick->process(); }

    for(int i = 0;i<4;i++){
        if(label[i]) { label[i]->process(); }
        if(labelOver[i]) { labelOver[i]->process(); }
        if(labelHold[i]) { labelHold[i]->process(); }
        if(labelClick[i]) { labelClick[i]->process(); }
    }
}
