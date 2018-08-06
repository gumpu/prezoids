
SDL2FLAGS = `sdl2-config --cflags`
SDL2LIBFLAGS = `sdl2-config --libs`

LINKER_FLAGS = -lSDL2_image

all : main
	make -C Images

main.o : main.cpp
	g++ -c $(SDL2FLAGS) main.cpp -o main.o

main : main.o
	g++ main.o  $(SDL2LIBFLAGS) $(LINKER_FLAGS) -o main

tags :
	ctags -R /usr/include/SDL2/ .

clean :
	-rm tags
	-rm -f main
	-rm -f main.o
	make -C Images clean


