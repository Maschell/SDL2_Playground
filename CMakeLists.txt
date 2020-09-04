cmake_minimum_required(VERSION 3.17)
project(SDL2_Playground)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/gui/GuiElement.h
        src/gui/GuiFrame.cpp
        src/gui/GuiFrame.h
        src/gui/sigslot.h
        src/system/SDLSystem.cpp
        src/system/SDLSystem.h
        src/gui/GuiElement.cpp
        src/gui/GuiText.cpp
        src/gui/GuiText.h
        src/gui/GuiImage.cpp
        src/gui/GuiImage.h
        src/gui/GuiSound.cpp
        src/gui/GuiSound.h
        src/gui/GuiTrigger.cpp
        src/gui/GuiTrigger.h
        src/gui/GuiController.h
        src/gui/GuiButton.cpp
        src/gui/GuiButton.h
        src/resources/Resources.cpp
        src/resources/Resources.h
        src/fs/CFile.cpp
        src/fs/CFile.hpp
        src/fs/FSUtils.cpp
        src/fs/FSUtils.h
        src/input/SDLController.h src/menu/MainWindow.cpp src/menu/MainWindow.h src/input/SDLControllerJoystick.h src/input/SDLControllerMouse.h
        src/input/SDLControllerWiiUGamepad.h
        src/input/SDLControllerWiiUProContoller.h
        src/gui/GuiTextureData.cpp src/gui/GuiTextureData.h
        src/system/video/SDL_FontCache.h
        src/system/video/SDL_FontCache.cpp

        src/system/video/Renderer.h src/input/ControllerManager.cpp src/input/ControllerManager.h)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer)
