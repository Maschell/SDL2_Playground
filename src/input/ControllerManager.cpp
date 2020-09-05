#include <functional>
#include "ControllerManager.h"
#include "SDLControllerWiiUGamepad.h"
#include "SDLControllerXboxOne.h"
#include "SDLControllerWiiUProContoller.h"
#include "SDLControllerJoystick.h"

GuiTrigger::eChannels ControllerManager::increaseChannel(GuiTrigger::eChannels channel) {
    switch (channel) {
        case GuiTrigger::CHANNEL_1:
            return GuiTrigger::CHANNEL_2;
        case GuiTrigger::CHANNEL_2:
            return GuiTrigger::CHANNEL_3;
        case GuiTrigger::CHANNEL_3:
            return GuiTrigger::CHANNEL_4;
        case GuiTrigger::CHANNEL_4:
            return GuiTrigger::CHANNEL_5;
        case GuiTrigger::CHANNEL_5:
        case GuiTrigger::CHANNEL_ALL:
            return GuiTrigger::CHANNEL_ALL;
    }
    return GuiTrigger::CHANNEL_ALL;
}

void ControllerManager::attachController(GuiTrigger::eChannels channel, SDLController *controller) {
    controllerList[channel] = controller;
}

void ControllerManager::prepare() {
    //! Read out inputs
    for (auto const&[channel, controller] : controllerList) {
        controller->before();
    }
}

bool ControllerManager::attachJoystick(int32_t deviceId) {
    auto joystick = SDL_JoystickOpen(deviceId);
    if (joystick == nullptr) {
        DEBUG_FUNCTION_LINE("SDL_JoystickOpen failed: %s\n", SDL_GetError());
        return false;
    }
    auto instanceId = SDL_JoystickInstanceID(joystick);
    if (std::string("WiiU Gamepad") == SDL_JoystickName(joystick)) {
        controllerList[GuiTrigger::CHANNEL_1] = new SDLControllerWiiUGamepad(GuiTrigger::CHANNEL_1);
        joystickToChannel[instanceId] = GuiTrigger::CHANNEL_1;
    } else {
        bool successfully_added = false;
        auto channel = GuiTrigger::CHANNEL_2;
        while (channel != GuiTrigger::CHANNEL_ALL) {
            if (controllerList.find(channel) == controllerList.end()) {
                if (std::string(SDL_JoystickName(joystick)).find("Xbox") != std::string::npos
                 || std::string(SDL_JoystickName(joystick)).find("X-Box") != std::string::npos) {
                    controllerList[channel] = new SDLControllerXboxOne(channel);
                } else if (std::string(SDL_JoystickName(joystick)).find("WiiU Pro Controller") != std::string::npos) {
                    controllerList[channel] = new SDLControllerWiiUProContoller(channel);
                } else {
                    controllerList[channel] = new SDLControllerJoystick(channel, instanceId);
                }
                joystickToChannel[instanceId] = channel;
                successfully_added = true;
                break;
            }
            channel = increaseChannel(channel);
        }
        if (!successfully_added) {
            DEBUG_FUNCTION_LINE("Failed to add joystick. Closing it now");
            SDL_JoystickClose(joystick);
            return false;
        }
    }
    DEBUG_FUNCTION_LINE("Added joystick %s", SDL_JoystickName(joystick));
    return true;
}

void ControllerManager::detachJoystick(int32_t instanceId) {
    auto channel = joystickToChannel[instanceId];
    delete controllerList[channel];
    controllerList.erase(channel);
    joystickToChannel.erase(instanceId);
    DEBUG_FUNCTION_LINE("Removed joystick: %d", instanceId);
}

void ControllerManager::processEvent(SDL_JoystickID joystickId, int32_t channel, SDL_Event *e) {
    if (joystickId != -1) {
        if (joystickToChannel.find(joystickId) != joystickToChannel.end()) {
            channel = joystickToChannel[joystickId];
        }
    }
    if (channel != -1 && controllerList.count(static_cast<const GuiTrigger::eChannels>(channel)) > 0) {
        controllerList[static_cast<GuiTrigger::eChannels>(channel)]->update(e, screenWidth, screenHeight);
    }
}

void ControllerManager::finish() {
    for (auto const&[joypad, controller] : controllerList) {
        controller->after();
    }
}

void ControllerManager::callPerController(std::function<void(GuiController*)> func) {
    for (auto const&[joypad, controller] : controllerList) {
        func(controller);
    }
}
