#pragma once

#include <map>
#include <functional>
#include "../gui/GuiTrigger.h"
#include "SDLController.h"
#include "SDLControllerMouse.h"

class ControllerManager {
public:
    ControllerManager(int32_t screenWidth, int32_t screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight){

    }

    void attachController(GuiTrigger::eChannels channels, SDLController *controller);

    void prepare();

    bool attachJoystick(int32_t deviceId);

    void detachJoystick(int32_t deviceId);

    void processEvent(SDL_JoystickID joystickId, int32_t channel, SDL_Event *event);

    void finish();


    void callPerController(std::function<void(GuiController*)> func);

private:
    GuiTrigger::eChannels increaseChannel(GuiTrigger::eChannels channel);

    std::map<GuiTrigger::eChannels, SDLController *> controllerList;
    std::map<int32_t, GuiTrigger::eChannels> joystickToChannel;
    int32_t screenWidth;
    int32_t screenHeight;
};
