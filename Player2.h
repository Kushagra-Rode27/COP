#ifndef PLAYER2_H
#define PLAYER2_H 

using namespace std;   


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "tile.h"
class Dot2
{
    public:
		//The dimensions of the dot
		static const int DOT2_WIDTH = 20;
		static const int DOT2_HEIGHT = 20;

		//Maximum axis velocity of the dot
		int DOT2_VEL = 16;

		//Initializes the variables
		Dot2();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent2( SDL_Event& e );

		void handle(const Uint8* currentKeyStates);

		//Moves the dot and check collision against tiles
		void move2( Tile *tiles[] );

		//Centers the camera over the dot
		void setCamera2( SDL_Rect& camera );

		//Shows the dot on the screen
		void render2( SDL_Rect& camera );

		int score=0;
		int tasksComp = 0;

		//Collision box of the dot
		SDL_Rect mBox2;

    private:

		//The velocity of the dot
		int mVelX2, mVelY2;
};
#endif