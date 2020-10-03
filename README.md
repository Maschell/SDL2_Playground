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

### With docker 

```
docker build . -f .\Dockerfile.wiiu  -t sdl2_playground-use-lib-builder-wiiu

docker run --rm -v ${PWD}:/project sdl2_playground-use-lib-builder-wiiu make -f Makefile.wiiu -j16
```

### With local installation

Install the following packages via [devkitPros pacman](https://devkitpro.org/wiki/devkitPro_pacman):
```
(dkp)pacman -S devkitPPC wut-tools wut wiiu-portlibs wiiu-sdl2-libs
```

Also install [libgui-sdl](https://github.com/Maschell/libgui-sdl) according to the README.

Build via:
```
make -f Makefile.wiiu
```