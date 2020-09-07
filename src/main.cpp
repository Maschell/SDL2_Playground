#include <SDL2/SDL.h>
#include "system/SDLSystem.h"
#include "gui/GuiFrame.h"
#include "gui/GuiButton.h"
#include "gui/GuiController.h"
#include "menu/MainWindowTV.h"
#include "input/SDLController.h"
#include "input/SDLControllerMouse.h"
#include "input/ControllerManager.h"
#include "menu/MainWindow.h"

#include <cstdio>
#include <fcntl.h>


#if defined _WIN32
#include <windows.h>
#endif

#ifdef __WIIU__
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>  
#include <proc_ui/procui.h>
bool CheckRunning(){
    switch(ProcUIProcessMessages(true))
    {
        case PROCUI_STATUS_EXITING:
        {
            return false;
        }
        case PROCUI_STATUS_RELEASE_FOREGROUND:
        {
            ProcUIDrawDoneRelease();
            break;
        }
        case PROCUI_STATUS_IN_FOREGROUND:
        {
            break;
        }
        case PROCUI_STATUS_IN_BACKGROUND:
        default:
            break;
    }
    return true;
}
#endif


int main(int argc, char *args[]) {
    auto *system = new SDLSystem();
#if defined _WIN32
    // Create the Console
    AllocConsole();

    // Create Console Output Handle
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((intptr_t) handle_out, _O_TEXT);
    FILE *hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    // Create Console Input Handle
    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((intptr_t) handle_in, _O_TEXT);
    FILE *hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);

    *stdin = *hf_in;
#elif __WIIU__
    WHBLogUdpInit();
#endif

    DEBUG_FUNCTION_LINE("%0.1f %0.1f", system->getWidth(), system->getHeight());

    auto * frame = new MainWindow(system);

    auto * controllerM = new ControllerManager(system->getWidth(), system->getHeight());


#ifndef __WIIU__
    // On non-Wii-U devices we expect a mouse.
    controllerM->attachController(GuiTrigger::CHANNEL_1, new SDLControllerMouse(GuiTrigger::CHANNEL_1));
    DEBUG_FUNCTION_LINE("Added mouse");
#endif

    while (true) {
#ifdef __WIIU__
        if(!CheckRunning()){
            exit(0);
            break;
        }
#endif
        // Prepare to process new events.
        controllerM->prepare();

        bool quit = false;
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            int32_t channel = -1;
            SDL_JoystickID jId = -1;
            if(e.type == SDL_JOYDEVICEADDED) {
                controllerM->attachJoystick(e.jdevice.which);
                continue;
            }else if(e.type ==  SDL_JOYDEVICEREMOVED) {
                auto j = SDL_JoystickFromInstanceID(e.jdevice.which);
                if (j) {
                    controllerM->detachJoystick(e.jdevice.which);
                    SDL_JoystickClose(j);
                    continue;
                }
            }else if (e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION ||
                e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION){
                channel = GuiTrigger::CHANNEL_1;
            } else if (e.type == SDL_JOYAXISMOTION) {
                jId = e.jaxis.which;
            } else if (e.type == SDL_JOYHATMOTION) {
                jId = e.jhat.which;
            }else if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_JOYBUTTONUP) {
                jId = e.jbutton.which;
            } else if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
                break;
            }
            controllerM->processEvent(jId, channel, &e);
        }

        if(quit){ break; }

        // Finish controller inputs
        controllerM->finish();

        // Update gui elements based on controller inputs
        controllerM->callPerController([frame](GuiController* controller) { frame->update(controller);});

        frame->process();

        frame->draw();

        frame->updateEffects();
    }

    delete frame;

    return 0;
}
