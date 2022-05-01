#ifndef PLAYER_H
#define PLAYER_H 

using namespace std;   

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "tile.h"
#include <SDL2/SDL_mixer.h>
#include "auxFunctions.h"
class Dot
{
    public:
		const int SCREEN_WIDTH = 1400;
        const int SCREEN_HEIGHT = 700;
        const int TILE_WIDTH = 32;
        const int TILE_HEIGHT = 32;
		const int TOTAL_TILES = 50*100;
		const int LEVEL_WIDTH = 3200;
		const int LEVEL_HEIGHT = 1600;
		const int TILE_NONE = 0;
		const int TILE_GREEN = 1;
		const int TILE_ROAD = 13;
		const int TILE_HOSTEL = 46;
		const int TILE_STORE = 65;
		const int TILE_ANOTHER = 74;
		const int TILE_SOME=43;
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		int DOT_VEL = 16;

		//Initializes the variables
		Dot();
		//Dot(LTexture gDotTexture,LTexture gTextTexture,TTF_Font *gFont,SDL_Renderer* gRenderer,Mix_Chunk *gHigh,Mix_Chunk *gMedium,Mix_Chunk *gLow);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		void handle(const Uint8* currentKeyStates);

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[],Mix_Chunk *gHigh,Mix_Chunk *gMedium,Mix_Chunk *gLow);

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera,LTexture TextTexture,TTF_Font *gFont ,SDL_Renderer* gRenderer);

		// touchesWall check
		bool touchesWall( SDL_Rect box, Tile* tiles[] );


		LTexture gDotTexture;
		string Sprite;
		int Xcycle;
		int Ycycle;
		int Spriteheight;
		int Spritewidth;
		int Renderwidth;
		int Renderheight;
		int stayState;

		string score_text;
		int score=0;
		int tasksComp = 0;
		//Collision box of the dot
		SDL_Rect mBox;
		bool speed1;

		functions myfunctions  ;

    private:

		//The velocity of the dot
		int mVelX, mVelY;
};
#endif