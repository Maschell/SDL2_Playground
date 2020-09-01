#pragma once

#include <SDL2/SDL_mouse.h>
#include <iostream>
#include <SDL2/SDL_events.h>
#include "../gui/GuiController.h"
#include "../utils/logger.h"

#define printButton(chan, x)  if(data.buttons_d & x) DEBUG_FUNCTION_LINE("Controller #%d %s", chan, #x)

class SDLController : public GuiController {
public:
    explicit SDLController(int32_t channel) : GuiController(channel) {

    }

    virtual bool update(SDL_Event *e, int32_t screenWidth, int32_t screenHeight) = 0;


    virtual void before() {
        lastData = data;

        data.buttons_d = 0;
        data.buttons_r = 0;
    }

    virtual void after() {
        data.buttons_d |= (data.buttons_h & (~(lastData.buttons_h)));
        data.buttons_r |= ((lastData.buttons_h) & (~data.buttons_h));
        if (data.buttons_h != 0 || data.buttons_d != 0 || data.buttons_r != 0) {
            // DEBUG_FUNCTION_LINE("Controller #%d: h %08X d %08X r %08X", chanIdx, data.buttons_h, data.buttons_d, data.buttons_r);

            printButton(chanIdx, GuiTrigger::BUTTON_A);
            printButton(chanIdx, GuiTrigger::BUTTON_B);
            printButton(chanIdx, GuiTrigger::BUTTON_X);
            printButton(chanIdx, GuiTrigger::BUTTON_Y);
            printButton(chanIdx, GuiTrigger::BUTTON_STICK_L);
            printButton(chanIdx, GuiTrigger::BUTTON_STICK_R);
            printButton(chanIdx, GuiTrigger::BUTTON_L);
            printButton(chanIdx, GuiTrigger::BUTTON_R);
            printButton(chanIdx, GuiTrigger::BUTTON_ZL);
            printButton(chanIdx, GuiTrigger::BUTTON_ZR);
            printButton(chanIdx, GuiTrigger::BUTTON_PLUS);
            printButton(chanIdx, GuiTrigger::BUTTON_MINUS);
            printButton(chanIdx, GuiTrigger::BUTTON_LEFT);
            printButton(chanIdx, GuiTrigger::BUTTON_UP);
            printButton(chanIdx, GuiTrigger::BUTTON_RIGHT);
            printButton(chanIdx, GuiTrigger::BUTTON_DOWN);
            printButton(chanIdx, GuiTrigger::STICK_L_LEFT);
            printButton(chanIdx, GuiTrigger::STICK_L_UP);
            printButton(chanIdx, GuiTrigger::STICK_L_RIGHT);
            printButton(chanIdx, GuiTrigger::STICK_L_DOWN);
            printButton(chanIdx, GuiTrigger::STICK_R_LEFT);
            printButton(chanIdx, GuiTrigger::STICK_R_UP);
            printButton(chanIdx, GuiTrigger::STICK_R_RIGHT);
            printButton(chanIdx, GuiTrigger::STICK_R_DOWN);
            printButton(chanIdx, GuiTrigger::TOUCHED);
        }
    }
};
