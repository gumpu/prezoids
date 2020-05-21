AM_CPPFLAGS=`sdl2-config --cflags`
AM_CXXFLAGS=-Weffc++ -Wfatal-errors -Wall -O0
AM_LDFLAGS=

bin_PROGRAMS = freezoids

freezoids_SOURCES=main.cpp game_limits.cpp game_limits.h \
				  game_textures.cpp game_textures.h \
				  mobs.cpp mobs.h \
				  tiles.cpp tiles.h \
				  game_positions.cpp game_positions.h \
				  camera.cpp camera.h \
				  globals.cpp globals.h

freezoids_LDADD=-lSDL2 -lSDL2_image -lSDL2_ttf

