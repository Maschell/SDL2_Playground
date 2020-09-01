#pragma once

#include "SDLController.h"

static GuiTrigger::eButtons xbox_button_map[] =
        {
                GuiTrigger::BUTTON_A,
                GuiTrigger::BUTTON_B,
                GuiTrigger::BUTTON_X,
                GuiTrigger::BUTTON_Y,
                GuiTrigger::BUTTON_L,
                GuiTrigger::BUTTON_R,
                GuiTrigger::BUTTON_MINUS,
                GuiTrigger::BUTTON_PLUS,
                GuiTrigger::BUTTON_STICK_L,
                GuiTrigger::BUTTON_STICK_R,
        };

#define getDigitalAxis(axis, targetAxis, value, hold, first, second) \
if(axis == targetAxis){ \
    if (value < 0x4000 && value > -0x4000){ \
        hold &= ~first; \
        hold &= ~second; \
    }else if(value < -0x4000){ \
        hold |= first; \
        hold &= ~second; \
    }else if(value > 0x4000){ \
        hold |= second; \
        hold &= ~first; \
    } \
}                                                                    \

#define getDigitalTrigger(axis, targetAxis, value, hold, first) \
if(axis == targetAxis){ \
    if(value > 0){ \
        hold |= first; \
    }else{ \
        hold &= ~first; \
    } \
} \


class SDLControllerXboxOne : public SDLController {
public:
    explicit SDLControllerXboxOne(int32_t channel) : SDLController(channel) {

    }

    bool update(SDL_Event *e, int32_t screenWidth, int32_t screenHeight) override {
        if (e->type == SDL_JOYBUTTONDOWN) {
            data.buttons_h |= xbox_button_map[e->jbutton.button];
        } else if (e->type == SDL_JOYBUTTONUP) {
            data.buttons_h &= ~xbox_button_map[e->jbutton.button];
        } else if (e->type == SDL_JOYHATMOTION) {
            auto val = e->jhat.value;

            auto hatMask = (GuiTrigger::BUTTON_LEFT | GuiTrigger::BUTTON_UP | GuiTrigger::BUTTON_DOWN | GuiTrigger::BUTTON_RIGHT);

            // Remove hat values so we can add the new values.
            data.buttons_h &= ~hatMask;

            switch (val) {
                case SDL_HAT_LEFTUP:
                    data.buttons_h |= GuiTrigger::BUTTON_LEFT;
                    data.buttons_h |= GuiTrigger::BUTTON_UP;
                    break;
                case SDL_HAT_LEFT:
                    data.buttons_h |= GuiTrigger::BUTTON_LEFT;
                    break;
                case SDL_HAT_LEFTDOWN:
                    data.buttons_h |= GuiTrigger::BUTTON_LEFT;
                    data.buttons_h |= GuiTrigger::BUTTON_DOWN;
                    break;
                case SDL_HAT_UP:
                    data.buttons_h |= GuiTrigger::BUTTON_UP;
                    break;
                case SDL_HAT_DOWN:
                    data.buttons_h |= GuiTrigger::BUTTON_DOWN;
                    break;
                case SDL_HAT_RIGHTUP:
                    data.buttons_h |= GuiTrigger::BUTTON_RIGHT;
                    data.buttons_h |= GuiTrigger::BUTTON_UP;
                    break;
                case SDL_HAT_RIGHT:
                    data.buttons_h |= GuiTrigger::BUTTON_RIGHT;
                    break;
                case SDL_HAT_RIGHTDOWN:
                    data.buttons_h |= GuiTrigger::BUTTON_RIGHT;
                    data.buttons_h |= GuiTrigger::BUTTON_DOWN;
                    break;
            }
        } else if (e->type == SDL_JOYAXISMOTION) {
            getDigitalTrigger(e->jaxis.axis, 2, e->jaxis.value, data.buttons_h, GuiTrigger::BUTTON_ZL);
            getDigitalTrigger(e->jaxis.axis, 5, e->jaxis.value, data.buttons_h, GuiTrigger::BUTTON_ZR);
            getDigitalAxis(e->jaxis.axis, 0, e->jaxis.value, data.buttons_h, GuiTrigger::STICK_L_LEFT, GuiTrigger::STICK_L_RIGHT);
            getDigitalAxis(e->jaxis.axis, 1, e->jaxis.value, data.buttons_h, GuiTrigger::STICK_L_UP, GuiTrigger::STICK_L_DOWN);
            getDigitalAxis(e->jaxis.axis, 3, e->jaxis.value, data.buttons_h, GuiTrigger::STICK_R_LEFT, GuiTrigger::STICK_R_RIGHT);
            getDigitalAxis(e->jaxis.axis, 4, e->jaxis.value, data.buttons_h, GuiTrigger::STICK_R_UP, GuiTrigger::STICK_R_DOWN);
        } else {
            DEBUG_FUNCTION_LINE("Unknown event");
            return false;
        }
        return true;
    }
};

