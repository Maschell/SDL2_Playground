cmake_minimum_required(VERSION 3.17)
project(SDL2_Playground)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/resources/Resources.cpp
        src/resources/Resources.h
        src/fs/CFile.cpp
        src/fs/CFile.hpp
        src/fs/FSUtils.cpp
        src/fs/FSUtils.h
        src/menu/MainWindow.cpp
        src/menu/MainWindow.h )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

enable_language(ASM)

include(ExternalProject)
ExternalProject_Add(libgui-sdl_git
        PREFIX vendor/
        GIT_REPOSITORY https://github.com/Maschell/libgui-sdl
        GIT_TAG master
        GIT_SUBMODULES
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        BUILD_COMMAND ""
        CMAKE_ARGS
        "-DCMAKE_BUILD_TYPE=Release"
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
        INSTALL_COMMAND
        "${CMAKE_COMMAND}"
        --build .
        --target install
        --config Release)

add_library (libgui-sdl STATIC IMPORTED GLOBAL)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vendor/include/gui-sdl/)
set_target_properties (libgui-sdl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/vendor/lib/libgui-sdl.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/vendor/include/gui-sdl/
      )
add_dependencies(libgui-sdl libgui-sdl_git)

ExternalProject_Add(bin2s_git
        PREFIX vendor/
        GIT_REPOSITORY https://github.com/Maschell/bin2s
        GIT_TAG master
        GIT_SUBMODULES
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        BUILD_COMMAND ""
        CMAKE_ARGS
        "-DCMAKE_BUILD_TYPE=Release"
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
        INSTALL_COMMAND
        "${CMAKE_COMMAND}"
        --build .
        --target install
        --config Release)

add_executable(bin2s IMPORTED GLOBAL)
set_target_properties(bin2s PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/vendor/bin/bin2s)
add_dependencies(bin2s bin2s_git)

function(add_binfile_library target_name)
    if (NOT ${ARGC} GREATER 1)
        message(FATAL_ERROR "add_binfile_library : Argument error (no input files)")
    endif()

    get_cmake_property(_enabled_languages ENABLED_LANGUAGES)
    if (NOT _enabled_languages MATCHES ".*ASM.*")
        message(FATAL_ERROR "add_binfile_library : ASM language needs to be enabled")
    endif()

    set(_output_dir ${CMAKE_CURRENT_BINARY_DIR}/binfile_asm)
    set(_output_file ${_output_dir}/${target_name}.s)

    file(MAKE_DIRECTORY ${_output_dir})

    add_custom_command(OUTPUT ${_output_file}
            COMMAND bin2s -o "${_output_file}" ${ARGN}
            DEPENDS ${ARGN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

    add_library(${target_name} ${_output_file})
endfunction()

add_binfile_library(resources
        data/fonts/FreeSans.ttf
        data/sounds/bgMusic.ogg
        data/sounds/button_click.mp3
        data/images/button.png
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CMAKE_BUILD_")

target_link_libraries(${PROJECT_NAME} libgui-sdl SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer resources)
