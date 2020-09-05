# Building

## With CMake
Make sure you have installed `build-essential make git cmake libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-dev`. Then you can do:
```
# Build the filelist.h
bash ./filelist.sh 
#
mkdir build && cd build && cmake .. && make
```

Via docker: 
```
# Build the docker image
docker build . -f .\Dockerfile.pc  -t sdl2_playground-builder-pc

# Build filelist.h
docker run -it --rm -v ${PWD}:/project sdl2_playground-builder-pc bash -c "cd .. && bash filelist.sh"

# Generate the makefile
docker run -it --rm -v ${PWD}:/project sdl2_playground-builder-pc cmake ..

# build!
docker run -it --rm -v ${PWD}:/project sdl2_playground-builder-pc make

# The result will be in ${PWD}/cmake-build
```

## Windows binaries

### Windows with devkitPros version of msys2
Setup mingw:
1. Add the mingw64 repository to `/etc/pacman.conf`.
```
[mingw64]
Server = https://repo.msys2.org/mingw/x86_64
```
2. Install packages (List taken from [here](https://gist.github.com/thales17/fb2e4cff60890a51d9dddd4c6e832ad2))
```
pacman -Syu
pacman -S git mingw-w64-x86_64-toolchain mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_mixer mingw64/mingw-w64-x86_64-SDL2_image mingw64/mingw-w64-x86_64-SDL2_ttf mingw64/mingw-w64-x86_64-SDL2_net mingw64/mingw-w64-x86_64-cmake make
```
3. Set the environment variable `MINGW64_PREFIX` to `C:/devkitPro/msys2/mingw64/bin/`

4. Build!
```
make -f .\Makefile.pc-win
```

### Windows with docker

```
docker build . -f .\Dockerfile.pc-win  -t sdl2_playground-builder-pc-win
docker run -it --rm -v ${PWD}:/project sdl2_playground-builder-pc-win make -f .\Makefile.pc-win -j16
```

## Wii U binaries

### With docker 

```
docker build . -f .\Dockerfile.wiiu  -t sdl2_playground-builder-wiiu

docker run -it --rm -v ${PWD}:/project sdl2_playground-builder-wiiu make -f .\Makefile.wiiu -j16
```

### With local installation

Install the following packages via [devkitPros pacman](https://devkitpro.org/wiki/devkitPro_pacman):
```
(dkp)pacman -S devkitPPC wut-tools wut wiiu-portlibs wiiu-sdl2-libs
```

Build via:
```
make -f Makefile.wiiu
```