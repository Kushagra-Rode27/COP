FLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lm 
test : lazy.map
	g++ -o yourcode.out game.cpp ${FLAGS} 

clean:
	rm -rf *o ./yourcode.out