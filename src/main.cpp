#include <SDL2/SDL.h>
#include "CVideo.h"
#include "gui/GuiFrame.h"
#include "gui/GuiImage.h"
#include "gui/GuiButton.h"
#include "gui/GuiController.h"
#include "gui/SDLController.h"
#include "MainWindow.h"
#include "logger.h"
#include "gui/SDLControllerJoystick.h"
#include "gui/SDLControllerMouse.h"
#include "gui/SDLControllerWiiUGamepad.h"
#include "gui/SDLControllerXboxOne.h"
#include "gui/SDLControllerWiiUProContoller.h"

#include <stdio.h>
#include <fcntl.h>

#include <map>

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

void proccessEvents();

bool addJoystick(int deviceId, std::map<GuiTrigger::eChannels, SDLController *> &controllerList, std::map<int32_t, GuiTrigger::eChannels>& map);

GuiTrigger::eChannels increaseChannel(GuiTrigger::eChannels channel);

void removeJoystick(int32_t which, std::map<GuiTrigger::eChannels, SDLController *> &controllerList, std::map<int32_t, GuiTrigger::eChannels>& joystickToChannel);

int main(int argc, char *args[]) {
    CVideo *video = new CVideo();

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

    GuiFrame *frame = new MainWindow(video->getWidth(), video->getHeight());

    std::map<GuiTrigger::eChannels, SDLController*> controllerList;
    std::map<int32_t , GuiTrigger::eChannels> joystickToChannel;

#if defined _WIN32
    controllerList[GuiTrigger::CHANNEL_1] = new SDLControllerMouse(GuiTrigger::CHANNEL_1);
    DEBUG_FUNCTION_LINE("Add mouse");
#endif

    while (true) {
#ifdef __WIIU__
        if(!CheckRunning()){
            exit(0);
            break;
        }
#endif

        //! Read out inputs
        for( auto const& [channel, controller] : controllerList ){
            controller->before();
        }

        bool quit = false;
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_JoystickID jId = -1;
            if(e.type == SDL_JOYDEVICEADDED) {
                addJoystick(e.jdevice.which, controllerList, joystickToChannel);
            }else if(e.type ==  SDL_JOYDEVICEREMOVED) {
                auto j = SDL_JoystickFromInstanceID(e.jdevice.which);
                if (j) {
                    removeJoystick(e.jdevice.which, controllerList, joystickToChannel);
                    SDL_JoystickClose(j);
                }
            }else if (e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION){
                controllerList[GuiTrigger::CHANNEL_1]->update(&e);
            } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION){
                controllerList[GuiTrigger::CHANNEL_1]->update(&e);
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

            if(jId != -1){
                if(joystickToChannel.find(jId) != joystickToChannel.end()){
                    controllerList[joystickToChannel[jId]]->update(&e);
                }
            }
        }
        if(quit){
            break;
        }

        for( auto const& [joypad, controller] : controllerList ){
            controller->after();

            frame->update(controller);
        }

        frame->process();

        // clear the screen
        SDL_RenderClear(video->getRenderer());

        frame->draw(video);

        frame->updateEffects();

        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(video->getRenderer());

    }

    delete frame;

    return 0;
}

void removeJoystick(int32_t instanceId, std::map<GuiTrigger::eChannels, SDLController *> &controllerList, std::map<int32_t, GuiTrigger::eChannels>& joystickToChannel) {
    auto channel = joystickToChannel[instanceId];
    delete controllerList[channel];
    controllerList.erase(channel);
    joystickToChannel.erase(instanceId);
    DEBUG_FUNCTION_LINE("Removed joystick: %d", instanceId);
}

bool addJoystick(int deviceId, std::map<GuiTrigger::eChannels, SDLController *> &controllerList, std::map<int32_t, GuiTrigger::eChannels>& joystickToChannel) {
    auto joystick = SDL_JoystickOpen(deviceId);
    if (joystick == NULL){
        DEBUG_FUNCTION_LINE("SDL_JoystickOpen failed: %s\n", SDL_GetError());
        return false;
    }
    auto instanceId = SDL_JoystickInstanceID(joystick);
    if(std::string("WiiU Gamepad").compare(SDL_JoystickName(joystick)) == 0){
        controllerList[GuiTrigger::CHANNEL_1] = new SDLControllerWiiUGamepad(GuiTrigger::CHANNEL_1);
        joystickToChannel[instanceId] = GuiTrigger::CHANNEL_1;
    }else {
        bool successfully_added = false;
        auto channel = GuiTrigger::CHANNEL_2;
        while(channel != GuiTrigger::CHANNEL_ALL){
            if(controllerList.find(channel) == controllerList.end()) {
                if (std::string(SDL_JoystickName(joystick)).find("Xbox") != std::string::npos){
                    controllerList[channel] = new SDLControllerXboxOne(channel);
                }else if(std::string(SDL_JoystickName(joystick)).find("WiiU Pro Controller") != std::string::npos) {
                    controllerList[channel] = new SDLControllerWiiUProContoller(channel);
                }else{
                    controllerList[channel] = new SDLControllerJoystick(channel, instanceId);
                }
                joystickToChannel[instanceId] = channel;
                successfully_added = true;
                break;
            }
            channel = increaseChannel(channel);
        }
        if(!successfully_added){
            DEBUG_FUNCTION_LINE("Failed to add joystick. Closing it now");
            SDL_JoystickClose(joystick);
            return false;
        }
    }
    DEBUG_FUNCTION_LINE("Added joystick %s", SDL_JoystickName(joystick));
    return true;
}

GuiTrigger::eChannels increaseChannel(GuiTrigger::eChannels channel) {
    switch(channel){
        case GuiTrigger::CHANNEL_1:
            return GuiTrigger::CHANNEL_2;
        case GuiTrigger::CHANNEL_2:
            return GuiTrigger::CHANNEL_3;
        case GuiTrigger::CHANNEL_3:
            return GuiTrigger::CHANNEL_4;
        case GuiTrigger::CHANNEL_4:
            return GuiTrigger::CHANNEL_5;
    }
    return GuiTrigger::CHANNEL_ALL;
}

void proccessEvents() {

    int res = 0;

}
