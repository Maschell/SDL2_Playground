cmake_minimum_required(VERSION 3.17)
project(SDL2_Playground)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/gui/GuiElement.h
        src/gui/GuiFrame.cpp
        src/gui/GuiFrame.h
        src/gui/GuiImage.cpp
        src/gui/GuiImage.h
        src/gui/sigslot.h
        src/CVideo.cpp
        src/CVideo.h
        src/gui/GuiElement.cpp
        src/gui/GuiText.cpp
        src/gui/GuiText.h
        src/gui/GuiSound.cpp
        src/gui/GuiSound.h
        src/gui/GuiTrigger.cpp
        src/gui/GuiTrigger.h
        src/gui/GuiController.h
        src/gui/GuiButton.cpp
        src/gui/GuiButton.h


        src/gui/SDLController.h src/MainWindow.cpp src/MainWindow.h src/gui/SDLControllerJoystick.h src/gui/SDLControllerMouse.h
        src/gui/SDLControllerWiiUGamepad.h
        src/gui/SDLControllerWiiUProContoller.h
        src/gui/GuiTexture.cpp src/gui/GuiTexture.h
        src/gui/SDL_FontCache.h src/gui/SDL_FontCache.c

        )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer)
