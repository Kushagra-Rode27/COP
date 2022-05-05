FLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0  -lSDL2_image -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lm 
SRC_FILES = auxFunctions.h auxFunctions.cpp Button.h Button.cpp timer.h timer.cpp enemy.h enemy.cpp Player.h Player.cpp point.h point.cpp powerup.h powerup.cpp PlayerPaddle.cpp PlayerPaddle.h BaseEntity.cpp BaseEntity.h Ball.cpp Ball.h AiPaddle.cpp AiPaddle.h GameManager.cpp GameManager.h tasks.h tasks.cpp texture.h texture.cpp tile.h tile.cpp 
server : lazy.map
	g++ -o yourserv.out ${SRC_FILES} main.cpp ${FLAGS} 

client :
	g++ -o yourcli.out ${SRC_FILES} main_client.cpp ${FLAGS}

clean:
	rm -rf *o ./yourcode.out