#pragma once


#pragma once

#include "SDLController.h"

static GuiTrigger::eButtons vpad_button_map[] = {
        GuiTrigger::BUTTON_A,
        GuiTrigger::BUTTON_B,
        GuiTrigger::BUTTON_X,
        GuiTrigger::BUTTON_Y,
        GuiTrigger::BUTTON_STICK_L, GuiTrigger::BUTTON_STICK_R,
        GuiTrigger::BUTTON_L, GuiTrigger::BUTTON_R,
        GuiTrigger::BUTTON_ZL, GuiTrigger::BUTTON_ZR,
        GuiTrigger::BUTTON_PLUS, GuiTrigger::BUTTON_MINUS,
        GuiTrigger::BUTTON_LEFT, GuiTrigger::BUTTON_UP, GuiTrigger::BUTTON_RIGHT, GuiTrigger::BUTTON_DOWN,
        GuiTrigger::STICK_L_LEFT, GuiTrigger::STICK_L_UP, GuiTrigger::STICK_L_RIGHT, GuiTrigger::STICK_L_DOWN,
        GuiTrigger::STICK_R_LEFT, GuiTrigger::STICK_R_UP, GuiTrigger::STICK_R_RIGHT, GuiTrigger::STICK_R_DOWN,
};

class SDLControllerWiiUGamepad : public SDLController {
public:
    SDLControllerWiiUGamepad(int32_t channel) : SDLController(channel) {

    }

    virtual bool update(SDL_Event *e) override {
        if (e->type == SDL_FINGERMOTION) {
            data.y = e->tfinger.y * 720;
            data.x = e->tfinger.x * 1280;;
            data.validPointer = true;
        } else if (e->type == SDL_FINGERUP) {
            data.validPointer = false;
            data.buttons_h &= ~GuiTrigger::TOUCHED;
        } else if (e->type == SDL_FINGERDOWN) {
            data.validPointer = true;
            data.buttons_h |= GuiTrigger::TOUCHED;
        }
        if (e->type == SDL_JOYBUTTONDOWN) {
            data.buttons_h |= vpad_button_map[e->jbutton.button];
        } else if (e->type == SDL_JOYBUTTONUP) {
            data.buttons_h &= ~vpad_button_map[e->jbutton.button];
        } else {
            DEBUG_FUNCTION_LINE("Unknown event");
            return false;
        }
        return true;
    }
};

