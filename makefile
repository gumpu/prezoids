
SDL2FLAGS = `sdl2-config --cflags`
SDL2LIBFLAGS = `sdl2-config --libs`

LINKER_FLAGS = -lSDL2_image
all : main

main.o : main.cpp
	g++ -c $(SDL2FLAGS) main.cpp -o main.o

main : main.o
	g++ main.o  $(SDL2LIBFLAGS) $(LINKER_FLAGS) -o main

tags :
	ctags -R /usr/include/SDL2/ .

