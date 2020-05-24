AM_CPPFLAGS=`sdl2-config --cflags`
AM_CXXFLAGS=-Weffc++ -Wfatal-errors -Wall
AM_LDFLAGS=

bin_PROGRAMS = prezoids prut

prezoids_SOURCES=main.cpp game_limits.cpp game_limits.h \
				  underworld_state.cpp underworld_state.h \
				  overworld_state.cpp overworld_state.h \
				  start_screen_state.cpp start_screen_state.h \
				  game_textures.cpp game_textures.h \
				  mobs.cpp mobs.h \
				  tiles.cpp tiles.h \
				  game_positions.cpp game_positions.h \
				  camera.cpp camera.h \
				  globals.cpp globals.h

prut_SOURCES=ut.cpp ut.h test_tiles.cpp test_tiles.h

prezoids_LDADD=-lSDL2 -lSDL2_image -lSDL2_ttf

