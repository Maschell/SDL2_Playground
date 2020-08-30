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
make -f .\Makefile.pc-win
```

## Wii U

Install these libs from [wiiu-fling](https://gitlab.com/QuarkTheAwesome/wiiu-fling#installing):
- `pacman -S wiiu-fling/wiiu-sdl2 wiiu-fling/wiiu-sdl2_gfx wiiu-fling/wiiu-sdl2_image wiiu-fling/wiiu-sdl2_ttf`
And these from [dkp-libs](https://devkitpro.org/wiki/devkitPro_pacman):
- `pacman -S devkitPPC wut-tools wut wiiu-portlibs dkp-libs/wiiu-sdl2_mixer`

Build via:
`make -f Makefile.wiiu`