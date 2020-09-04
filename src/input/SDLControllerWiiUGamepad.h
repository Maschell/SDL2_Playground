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
    explicit SDLControllerWiiUGamepad(int32_t channel) : SDLController(channel) {

    }

    bool update(SDL_Event *e, int32_t screenWidth, int32_t screenHeight) override {
        if (e->type == SDL_FINGERMOTION || e->type == SDL_FINGERUP || e->type == SDL_FINGERDOWN) {
            data.y = e->tfinger.y * screenHeight;
            data.x = e->tfinger.x * screenWidth;
            if (e->type == SDL_FINGERUP) {
                data.touched = false;
            } else if (e->type == SDL_FINGERDOWN) {
                data.touched = true;
            }
        } else if (e->type == SDL_JOYBUTTONDOWN) {
            data.buttons_h |= vpad_button_map[e->jbutton.button];
        } else if (e->type == SDL_JOYBUTTONUP) {
            data.buttons_h &= ~vpad_button_map[e->jbutton.button];
        } else {
            DEBUG_FUNCTION_LINE("Unknown event");
            return false;
        }
        return true;
    }

    void after() override {
        data.validPointer = data.touched;
        SDLController::after();
    }
};

