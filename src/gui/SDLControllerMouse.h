
#pragma once

class SDLControllerMouse: public SDLController {
public:
    SDLControllerMouse(int32_t channel) : SDLController(channel) {

    }

    virtual bool update(SDL_Event *e) override {
        if (e->type == SDL_MOUSEMOTION) {
            data.y = e->motion.y;
            data.x = e->motion.x;
            data.validPointer = true;
        } else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
            data.buttons_h |= GuiTrigger::TOUCHED;
        } else if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT) {
            data.buttons_h &= ~GuiTrigger::TOUCHED;
        }else{
            DEBUG_FUNCTION_LINE("Unknown event");
            return false;
        }
        return true;
    }
};

