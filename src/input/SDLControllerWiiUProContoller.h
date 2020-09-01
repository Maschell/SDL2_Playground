#pragma once

#include "SDLControllerWiiUGamepad.h"

class SDLControllerWiiUProContoller : public SDLControllerWiiUGamepad {
public:
    explicit SDLControllerWiiUProContoller(int32_t channel) : SDLControllerWiiUGamepad(channel){

    }
};

