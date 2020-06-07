# Prezoids


## Based on

<http://lazyfoo.net/tutorials/SDL/index.php>

## Dependencies

    sudo apt install libsdl2-dev
    sudo apt install libsdl2-image-dev
    sudo apt install libsdl2-ttf-dev

## Build

    mkdir build
    cd build
    ../configure
    make

## Start
    cd build
    ./src/prezoids

## Regenerating autotools files

    autoreconf

## Ctags

Best way to update the ctags file

    ctags -R /usr/include/SDL2/ .

## Background

<https://elinux.org/images/4/43/Petazzoni.pdf>

<https://autotools.io/>   Autotools Mythbuster

<http://pcgbook.com/>  Procedural Content Generation in Games

<https://www.youtube.com/watch?v=7Ik2vowGcU0>  Convex Polygon Collisions #1
<https://github.com/OneLoneCoder/olcPixelGameEngine>

<https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>

