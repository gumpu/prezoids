AM_CPPFLAGS=`sdl2-config --cflags`
AM_CXXFLAGS=-Weffc++ -Wfatal-errors -Wall
AM_LDFLAGS=

bin_PROGRAMS = prezoids prut

prezoids_SOURCES=main.cpp \
				 utils.cpp utils.h \
				 game_limits.cpp game_limits.h \
				 camera.cpp camera.h \
				 game_positions.cpp game_positions.h \
				 game_textures.cpp game_textures.h \
				 mobs.cpp mobs.h \
				 overworld_state.cpp overworld_state.h \
				 testworld_state.cpp testworld_state.h \
				 polygons.cpp polygons.h \
				 start_screen_state.cpp start_screen_state.h \
				 tiles.cpp tiles.h \
				 underworld_state.cpp underworld_state.h \
				 globals.cpp globals.h

prut_SOURCES=ut.cpp ut.h \
			 test_tiles.cpp test_tiles.h \
			 test_polygons.cpp test_polygons.h \
			 testworld_state.cpp testworld_state.h \
			 test_mobs.cpp test_mobs.h \
			 game_limits.cpp game_limits.h \
			 camera.cpp camera.h \
			 game_positions.cpp game_positions.h \
			 game_textures.cpp game_textures.h \
			 mobs.cpp mobs.h \
			 overworld_state.cpp overworld_state.h \
			 polygons.cpp polygons.h \
			 start_screen_state.cpp start_screen_state.h \
			 tiles.cpp tiles.h \
			 underworld_state.cpp underworld_state.h \
			 globals.cpp globals.h

prezoids_LDADD=-lSDL2 -lSDL2_image -lSDL2_ttf

prut_LDADD=-lSDL2 -lSDL2_image -lSDL2_ttf

