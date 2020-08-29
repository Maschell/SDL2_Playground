#pragma once

#include "SDLControllerWiiUGamepad.h"

class SDLControllerWiiUProContoller : public SDLControllerWiiUGamepad {
public:
    SDLControllerWiiUProContoller(int32_t channel) : SDLControllerWiiUGamepad(channel){

    }
};

