#ifndef ENEMY_H
#define ENEMY_H 

using namespace std;   


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "tile.h"
#include <SDL2/SDL_mixer.h>

class enemyDot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 16;

		//Initializes the variables
		enemyDot(int pos);

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Shows the dot on the screen
		void render(SDL_Rect& camera,SDL_Renderer* gRenderer);

		//Collision box of the dot
		SDL_Rect mBox;
		
		LTexture genemyDotTexture;

    private:
		

		//The velocity of the dot
		int mVelX;
		int mVelY=16;
};
#endif