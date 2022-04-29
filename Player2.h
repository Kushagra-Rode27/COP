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
#include <SDL2/SDL_mixer.h>
#include "auxFunctions.h"
class Dot2
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


		bool touchesWall( SDL_Rect box, Tile* tiles[] );

		LTexture gDot2Texture;
		LTexture gTextTexture;
		TTF_Font *gFont = NULL;
		SDL_Renderer* gRenderer; 
		Mix_Chunk *gHigh = NULL;
		Mix_Chunk *gMedium = NULL;
		Mix_Chunk *gLow = NULL;

		string score_text2;

		int score=0;
		int tasksComp = 0;

		//Collision box of the dot
		SDL_Rect mBox2;
		bool speed2;

		functions myfunctions  ;
    private:

		//The velocity of the dot
		int mVelX2, mVelY2;
};
#endif