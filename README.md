# Building

## Windows with devkitPros version of msys2
Setup mingw:
1. Add the mingw64 repository to `/etc/pacman.conf`.
```
[mingw64]
Server = https://repo.msys2.org/mingw/x86_64
```
2. Install packages (List taken from [here](https://gist.github.com/thales17/fb2e4cff60890a51d9dddd4c6e832ad2))
```
pacman -Syu
pacman -S git mingw-w64-x86_64-toolchain mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_mixer mingw64/mingw-w64-x86_64-SDL2_image mingw64/mingw-w64-x86_64-SDL2_ttf mingw64/mingw-w64-x86_64-SDL2_net mingw64/mingw-w64-x86_64-cmake mingw-w64-x86_64-glm make
```

```
mkdir build && cd build
C:\devkitPro\msys2\mingw64\bin\cmake.exe -DSDL2_PATH=C:/devkitPro/msys2/mingw64 -Wno-dev -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=C:/devkitPro/msys2/mingw64/bin/g++.exe DCMAKE_C_COMPILER=C:/devkitPro/msys2/mingw64/bin/gcc.exe ../
make
```