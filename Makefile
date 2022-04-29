FLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lm 
SRC_FILES = auxFunctions.h auxFunctions.cpp enemy.h enemy.cpp Player.h Player.cpp Player2.h Player2.cpp point.h point.cpp powerup.h powerup.cpp tasks.h tasks.cpp texture.h texture.cpp tile.h tile.cpp 
test : lazy.map
	g++ -o yourcode.out ${SRC_FILES} main.cpp ${FLAGS} 

clean:
	rm -rf *o ./yourcode.out