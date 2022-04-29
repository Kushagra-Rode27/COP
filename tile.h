#ifndef TILE_H
#define TILE_H 

using namespace std;   


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "texture.h"
#include "auxFunctions.h"
class Tile
{
    public:
        const int SCREEN_WIDTH = 1400;
        const int SCREEN_HEIGHT = 700;
        const int TILE_WIDTH = 32;
        const int TILE_HEIGHT = 32;
        const int TOTAL_TILES = 50*100;
        const int TOTAL_TILE_SPRITES = 100;
		//Initializes position and type
		Tile( int x, int y, int tileType );

		//Shows the tile
		void render( SDL_Renderer* gRenderer ,SDL_Rect &camera, LTexture gTileTexture ,SDL_Rect gTileClips[]);

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();

		bool SetPoint=false;
		bool SetPowerUp=false;
		bool SetTask = false;

        functions myfunctions  ;
    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};
#endif