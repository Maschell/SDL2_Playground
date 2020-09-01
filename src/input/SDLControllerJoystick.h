#pragma once

class SDLControllerJoystick : public SDLController {
public:
    SDLControllerJoystick(int32_t channel, SDL_JoystickID joystickId) : SDLController(channel) {

    }

    bool update(SDL_Event *e, int32_t screenWidth, int32_t screenHeight) override {
        if (e->type == SDL_JOYBUTTONDOWN) {
            data.buttons_h |= (1 << e->jbutton.button);
        } else if (e->type == SDL_JOYBUTTONUP) {
            data.buttons_h &= ~(1 << e->jbutton.button);
        } else if (e->type == SDL_JOYHATMOTION) {
            auto val = e->jhat.value;

            auto hatMask = (GuiTrigger::BUTTON_LEFT | GuiTrigger::BUTTON_UP | GuiTrigger::BUTTON_DOWN | GuiTrigger::BUTTON_RIGHT);

            // Remove hat values so we can add the new value.
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
            //
        }
        return true;
    }
};

