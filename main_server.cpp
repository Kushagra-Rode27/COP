#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "texture.h"
#include "tile.h"
#include "auxFunctions.h"
#include "Player.h"
#include "Player2.h"
#include "point.h"
#include "powerup.h"
#include "tasks.h"
#include "enemy.h"
#include "Button.h"
#include "timer.h"
#include "Window.h"
#include<vector>

#define PORT 8080
// Screen dimension constants

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;

const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//The dimensions of the level
const int LEVEL_WIDTH = 4800;
const int LEVEL_HEIGHT = 2400;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 75*150;
const int TOTAL_TILE_SPRITES = 48*48;

LWindow gWindow;

std::string initString = " Hello ";

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] );

int curr_state = 0;
int curr_stateP2 = 0;


vector<LTexture> Textures(2);
vector<std::string> Images{"SmallImage.png", "BigImage.png"}; // some images for pause screen look at this later 
// The window renderer
SDL_Renderer *gRenderer = NULL;


Tile* tileSet[ TOTAL_TILES ];
Dot dot;
Dot dot2;
enemyDot enemy1(8);
enemyDot enemy2(42);
enemyDot enemy3(81);
Point arr[10];

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture gTextTexture;

LTexture pointTexture;
LTexture powerUpTexture;
LTexture tasksTexture;
LTexture gTileTexture;
LTexture StartTextureSmall;
LTexture StartTextureLarge;

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

bool P1Won = true;

bool init()
{
	//Initialization flag
	bool success = true;

    curr_state = 0;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}


		//Create window
		//gWindow = SDL_CreateWindow( "IITD Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( !gWindow.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
        {
            // Create renderer for window
            gRenderer = gWindow.createRenderer();
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading

                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }

				//Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 16384) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }

                // player1.Constructor(gRenderer, &gWindow.mWidth, &gWindow.mHeight, &message, 12, 4, 95, 159, 80, 48, "SpritePlayer1.png", 4, " ","EvilEmpire-4BBVK.ttf");
                // player2.Constructor(gRenderer, &gWindow.mWidth, &gWindow.mHeight, &message, 9, 4, 64, 64, 64, 64, "player2.png", 4, " ","EvilEmpire-4BBVK.ttf");
                // player1.mBox.x=1500;
                // player1.mBox.y=100;
                
                // player2.mBox.x = 1600;

                // player2.mBox.y = 100;
                // SDL_StartTextInput();
            }
			 
			
        }
			

		
	}

	return success;
}

TTF_Font *textFont = NULL;


bool loadMedia( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] ){
	// Loading success flag
    bool success = true;

    textFont = TTF_OpenFont("EvilEmpire-4BBVK.ttf", 35);
    if (textFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

	//Load dot texture
	if( !dot.gDotTexture.loadFromFile( "assets/character1.png",gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !enemy1.genemyDotTexture.loadFromFile( "assets/dog3.png" ,gRenderer))
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !enemy2.genemyDotTexture.loadFromFile( "assets/dog3.png" ,gRenderer))
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !enemy3.genemyDotTexture.loadFromFile( "assets/dog3.png" ,gRenderer))
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !dot2.gDotTexture.loadFromFile( "assets/character2.png" ,gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	
		if( !pointTexture.loadFromFile( "assets/point.bmp",gRenderer ))
		{
			printf( "Failed to load dot texture!\n" );
			success = false;
		}
	
	
	

	if( !powerUpTexture.loadFromFile( "assets/powerup.png" ,gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !tasksTexture.loadFromFile( "assets/task.png" ,gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "./tile.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	// Load tile map
    if (!setTiles(tileslayer1, tileslayer2, tileslayer3,tileslayer4))
    {
        printf("Failed to load tile set!\n");
        success = false;
    }

	//Load music
    gMusic = Mix_LoadMUS( "sounds/beat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gScratch = Mix_LoadWAV( "sounds/scratch.wav" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gHigh = Mix_LoadWAV( "sounds/high.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( "sounds/medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gLow = Mix_LoadWAV( "sounds/low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;


}

