//Using SDL, SDL_image, standard IO, strings, and file streams
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
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sstream>
#include <stdlib.h>
#include <sstream>
#define PORT 8080
#include "GameManager.h"
#include "PlayerPaddle.h"
#include "Ball.h"
#include "AiPaddle.h"
#include <vector>
#include "Board.h"
#include "Bot.h"
#include "Vector2D.h"

using namespace std;

int GameManager::screenH = 850;
int GameManager::screenW = 1700;

static int playerSpeed = 300;
static int aiSpeed = 350;
static int initialBallXSpeed = 250;
static int initialBallYSpeed = 40;

enum BOARD_PIECE {PIECE_EMPTY, PIECE_X, PIECE_O};

// when set to true, two a.i. player will play
// when set to false, the player can control the left paddle
static bool playerDisabled = false;
SDL_Texture *gBall;

void print_init_flags(int flags);
//sudo apt install libsdl2-mixer-dev

//38,25
//47,23
//63,24
//6,5
//10,14 yulu
//5,19
//6,28
//lib 49,17
//57,13
//51,6

int emote=0;
int emotetimer=0;
LTexture HappyTexture;
LTexture AngryTexture;
LTexture TeaseTexture;
LTexture CoolTexture;
int scorep1;
int scorep2;
bool speed1;
bool speed2;

//g++ 39_tiling.cpp `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_net -lm 
//sudo apt install libsdl2-ttf-2

SDL_Renderer* rend1;
SDL_Renderer* rende;
SDL_Texture* tex;
//Screen dimension constants

const int SCREEN_FPS = 10;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 850;
const int AREA=SCREEN_HEIGHT*SCREEN_WIDTH;
const int SIZE = 11;

SDL_Scancode keypressed = SDL_SCANCODE_UNKNOWN;
bool pauseGame;
SDL_Event event;

// const int SCREEN_WIDTH = 3200;
// const int SCREEN_HEIGHT = 1600;

//The dimensions of the level
const int LEVEL_WIDTH = 4800;
const int LEVEL_HEIGHT = 2400;


//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 75*150;
const int TOTAL_TILE_SPRITES = 48*48;

//The different tile sprites
const int TILE_NONE = 0;
const int TILE_GREEN = 1;
const int TILE_ROAD = 13;
const int TILE_HOSTEL = 46;
const int TILE_STORE = 65;
const int TILE_ANOTHER = 74;
const int TILE_SOME=43;

//Texture wrapper class

// till here in texture.h


// from here in tile.h slight change in render function
//The tile

// in Player1.h
//The dot that will move around on the screen

// till here





Point n1;
Point n2;
Point n3;
Point n4;
Point n5;
Point n6;
Point n7;
Point n8;
Point n9;
Point n10;
Point arr[10];


struct Info
{
    int stateFirst;
    int stateSecond;
    int X;
    int Y;
    int myState;
    int health;
    int CG;
    int money;
	int tusk;
	int time;
	int emoji;
	//Point* pointarr;
};

void toNetwork(char *buffer, struct Info *mydata)
{
    // 32 byte buffer required
    // test bit
    buffer[0] = '*';
    // storing X of player
    std::sprintf(buffer + 1, "%02d", mydata->stateFirst);
    std::sprintf(buffer + 4, "%02d", mydata->stateSecond);
    std::sprintf(buffer + 7, "%04d", mydata->X);
    std::sprintf(buffer + 12, "%04d", mydata->Y);
    std::sprintf(buffer + 17, "%01d", mydata->myState);
    std::sprintf(buffer + 19, "%03d", mydata->health);
    std::sprintf(buffer + 23, "%03d", mydata->CG);
    std::sprintf(buffer + 27, "%03d", mydata->money);
	std::sprintf(buffer+31,"%06d",mydata->tusk);
	std::sprintf(buffer+38,"%01d",mydata->time);
	std::sprintf(buffer+40,"%03d",mydata->emoji);
    buffer[44] = '#';
}

bool fromNetwork(char *buffer, struct Info *indata)
{
    if (buffer[0] != '*' || buffer[44] != '#')
        return false;
    indata->stateFirst = atoi(buffer + 1);
    indata->stateSecond = atoi(buffer + 4);
    indata->X = atoi(buffer + 7);
    indata->Y = atoi(buffer + 12);
    indata->myState = atoi(buffer + 17);
    indata->health = atoi(buffer + 19);
    indata->CG = atoi(buffer + 23);
    indata->money = atoi(buffer + 27);
	indata->tusk=atoi(buffer+31);
	indata->time=atoi(buffer+38);
	indata->emoji=atoi(buffer+40);
    return true;
}

void print_data(struct Info *indata)
{

    cout << indata->stateFirst << "\n";
    cout << indata->stateSecond << "\n";
    cout << indata->X << "\n";
    cout << indata->Y << "\n";
    cout << indata->myState << "\n";
    cout << indata->health << "\n";
    cout << indata->CG << "\n";
    cout << indata->money << "\n";
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );



//Sets tiles from tile map
bool setTiles( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *myFont = NULL;
//Rendered texture
LTexture gTextTexture;

//LTexture pointTexture;
LTexture powerUpTexture;
LTexture tasksTexture;
LTexture gTileTexture1;
LTexture gTileTexture2;
LTexture gTileTexture3;
LTexture gTileTexture4;
LTexture MinimapTexture;

LTexture InfoScreenTexture; 
LTexture StartScreenTexture;
LTexture EndScreenTexture;
LTexture HostelTexture;

LTexture Win;
LTexture Lose;
//SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

//The music that will be played
Mix_Music *gMusic = NULL;
Mix_Music *BgMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

std::string score_text;
std::string score_text2;


int curr_state = 0;
int curr_stateP2 = 0;

Tile* tileSet1[ TOTAL_TILES ];
Tile* tileSet2[ TOTAL_TILES ];
Tile* tileSet3[ TOTAL_TILES ];
Tile* tileSet4[ TOTAL_TILES ];
Dot dot(6,2,78,127,32,32,1);
Dot dot2(6,2,78,127,32,32,1);
enemyDot enemy1(16);
enemyDot enemy2(42);
enemyDot enemy3(81);


typedef struct{

	SDL_Texture *segmentTexture;
	SDL_Surface *segmentImage;
	SDL_Rect segmento[AREA];
	SDL_Rect sprite[2];
	int frame;
	
	char dir;
	int totalSegmento;
	int dimensao;

} Snake;

typedef struct{

	SDL_Texture *foodTexture;
	SDL_Surface *foodImage;
	SDL_Rect foodPos;

} Food;
SDL_Texture *background = NULL;
SDL_Texture *pauses = NULL;
SDL_Surface *backgroundImage = NULL;
SDL_Surface *pauseImage = NULL;

Snake snake;
Food food;

bool InitWindow();
void Close();
void InitSnake();
void NewRound();
//from here texture.cpp

// LTexture in texture.cpp some change has been done in function definition of loadfromfile. grenderer has been passed as parameter




// in tile.cpp with some modifications




// in Player.cpp



int ti = 180;
int lastTime1 = 0,currentTime1;
void timerRender(){
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(std::to_string(ti) + " seconds",textColor,gFont,gRenderer);
	gTextTexture.render( gRenderer,0, 0,0,0);
}


// in point.cpp


// Powerup in powerup.cpp


// Tasks



bool init()
{
	//Initialization flag
	bool success = true;

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
		gWindow = SDL_CreateWindow( "IITD Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			

			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
			 //Initialize SDL_ttf
			if( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				success = false;
			}

			 //Initialize SDL_mixer
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			{
				printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				success = false;
			}

		}
	}

	return success;
}

bool loadMedia( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
    
	if( !dot.gDotTexture.loadFromFile( "assets/Player2Sprite1.png",gRenderer) )
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

	if( !dot2.gDotTexture.loadFromFile( "assets/Player1Sprite.png" ,gRenderer) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	for (int i = 0; i < 10; i++)
	{
		if( !arr[i].pointTexture.loadFromFile( "assets/task.png",gRenderer ))
		{
			printf( "Failed to load dot texture!\n" );
			success = false;
		}
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
	if( !gTileTexture1.loadFromFile( "assets/AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture2.loadFromFile( "assets/AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture3.loadFromFile( "assets/AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture4.loadFromFile( "assets/AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	if(!StartScreenTexture.loadFromFile("assets/start screen.png",gRenderer)){
		printf("Failed to load start screen texture\n");
		success = false;
	}

	if(!HostelTexture.loadFromFile("assets/hostel.png",gRenderer)){
		printf("Failed to load start screen texture\n");
		success = false;
	}

	if(!InfoScreenTexture.loadFromFile("assets/INFO sheet.png",gRenderer)){
		printf("Failed to load start screen texture\n");
		success = false;
	}

	if(!EndScreenTexture.loadFromFile("assets/EndScreen.png",gRenderer)){
		printf("Failed to load start screen texture\n");
		success = false;
	}

	if(!HappyTexture.loadFromFile("assets/laugh_small.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	if(!TeaseTexture.loadFromFile("assets/tease_small.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	if(!AngryTexture.loadFromFile("assets/angry_small.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	if(!CoolTexture.loadFromFile("assets/cool_small.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	if(!MinimapTexture.loadFromFile("assets/untitled.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	if(!Win.loadFromFile("assets/winning.png",gRenderer)){
		printf("Failed to load winner texture\n");
		success = false;
	}
	if(!Lose.loadFromFile("assets/loser.png",gRenderer)){
		printf("Failed to load loser texture\n");
		success = false;
	}
	if ((backgroundImage = IMG_Load("assets/start screen.png")) == NULL) printf("ERRO %s", SDL_GetError());
	background = SDL_CreateTextureFromSurface(gRenderer, backgroundImage);

	if ((snake.segmentImage = IMG_Load("assets/CG1.png")) == NULL) printf("ERRO %s", SDL_GetError());
	snake.segmentTexture = SDL_CreateTextureFromSurface(gRenderer, snake.segmentImage);

	if ((food.foodImage = IMG_Load("assets/CG1.png")) == NULL) printf("ERRO %s", SDL_GetError());
	food.foodTexture = SDL_CreateTextureFromSurface(gRenderer, food.foodImage);

	if((pauseImage = IMG_Load("assets/GIRNAR.png")) == NULL) printf("ERRO %s", IMG_GetError());
	pauses = SDL_CreateTextureFromSurface(gRenderer, pauseImage);
	
	score_text="score: "+std::to_string(scorep1);
	gFont = TTF_OpenFont( "metal lord.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedText( score_text, textColor ,gFont,gRenderer) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
	myFont = TTF_OpenFont( "assets/US101.TTF", 26 );
    if( myFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
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

	//Load tile map
	if( !setTiles(tileslayer1, tileslayer2, tileslayer3,tileslayer4))
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tileslayer1[ i ] != NULL )
		 {
			delete tileslayer1[ i ];
			tileslayer1[ i ] = NULL;
		 }
	}
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tileslayer2[ i ] != NULL )
		 {
			delete tileslayer2[ i ];
			tileslayer2[ i ] = NULL;
		 }
	}
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tileslayer3[ i ] != NULL )
		 {
			delete tileslayer3[ i ];
			tileslayer3[ i ] = NULL;
		 }
	}
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tileslayer4[ i ] != NULL )
		 {
			delete tileslayer4[ i ];
			tileslayer4[ i ] = NULL;
		 }
	}

	//Free loaded images
	dot.gDotTexture.free();
	enemy1.genemyDotTexture.free();
	enemy2.genemyDotTexture.free();
	enemy3.genemyDotTexture.free();
	dot2.gDotTexture.free();
	gTileTexture1.free();
	HappyTexture.free();
	AngryTexture.free();
	CoolTexture.free();
	TeaseTexture.free();
	gTileTexture2.free();
	gTileTexture3.free();
	gTileTexture4.free();
	for (int i = 0; i < 10; i++)
	{
		arr[i].pointTexture.free();
	}
	
	
	//Free loaded images
    gTextTexture.free();
	MinimapTexture.free();
	powerUpTexture.free();
	tasksTexture.free();
	StartScreenTexture.free();
	HostelTexture.free();
	InfoScreenTexture.free();
	EndScreenTexture.free();
	 HappyTexture.free();
	AngryTexture.free();
	CoolTexture.free();
	TeaseTexture.free();
	SDL_DestroyTexture(background);
	SDL_FreeSurface(backgroundImage);

	SDL_DestroyTexture(pauses);
	SDL_FreeSurface(pauseImage);

	SDL_DestroyTexture(snake.segmentTexture);
	SDL_FreeSurface(snake.segmentImage);

	SDL_DestroyTexture(food.foodTexture);
	SDL_FreeSurface(food.foodImage);
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

	TTF_CloseFont( myFont );
    myFont = NULL;

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

	//Destroy window	
	//SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//functions.cpp and .h

// till here

bool setTiles( Tile* tileslayer1[],Tile* tileslayer2[],Tile* tileslayer3[],Tile* tileslayer4[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map1( "./layer1.txt" );

    //If the map couldn't be loaded
    if( map1.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;
			//Read tile from map file
			map1 >> tileType;

			//If the was a problem in reading the map
			if( map1.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number && ( tileType < TOTAL_TILE_SPRITES )
			if( ( tileType >= 0 ) )
			{
				tileslayer1[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
	}

    //Close the file
    map1.close();

	// The tile offsets
    x = 0;
    y = 0;

    // Open the map
    std::ifstream map2("./layer2.txt");

    // If the map couldn't be loaded
    if (map2.fail())
    {
        printf("Unable to load map2 file!\n");
        tilesLoaded = false;
    }
    else
    {
        // Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; i++)
        {
            // Determines what kind of tile will be made
            long long tileType = -1;

            // Read tile from map file
            map2 >> tileType;
            

            // If the was a problem in reading the map
            if (map2.fail())
            {
                // Stop loading map
                std::cout << "Error loading map: Unexpected end of file 2 !\n " << i;
                tilesLoaded = false;
                break;
            }

            // If the number is a valid tile number
            if ((tileType >= 0)) // originally there was tileType< TotalTileSPrites
            {
                if (tileType>5000) tileslayer2[i] = new Tile(x, y, 835);
                else tileslayer2[i] = new Tile(x, y, tileType);
            }
            // If we don't recognize the tile type
            else
            {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= LEVEL_WIDTH)
            {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }
    }

    // Close the file
    map2.close();

    // The tile offsets
    x = 0;
    y = 0;

    // Open the map
    std::ifstream map3("./layer3.txt");

    // If the map couldn't be loaded
    if (map3.fail())
    {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else
    {
        // Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; i++)
        {
            // Determines what kind of tile will be made
            long long tileType = -1;

            // Read tile from map file
            map3 >> tileType;
            

            // If the was a problem in reading the map
            if (map3.fail())
            {
                // Stop loading map
                std::cout << "Error loading map: Unexpected end of file 3 !\n " << i;
                tilesLoaded = false;
                break;
            }

            // If the number is a valid tile number
            if ((tileType >= 0)) // originally there was tileType< TotalTileSPrites
            {
				if (tileType>5000) tileslayer3[i] = new Tile(x, y, 835);
                else tileslayer3[i] = new Tile(x, y, tileType);
            }
            // If we don't recognize the tile type
            else
            {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= LEVEL_WIDTH)
            {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }
	}
    map3.close();



	// The tile offsets
    x = 0;
    y = 0;

    // Open the map
    std::ifstream map4("./layer4.txt");

    // If the map couldn't be loaded
    if (map4.fail())
    {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else
    {
        // Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; i++)
        {
            // Determines what kind of tile will be made
            int tileType = -1;

            // Read tile from map file
            map4 >> tileType;
            

            // If the was a problem in reading the map
            if (map4.fail())
            {
                // Stop loading map
                std::cout << "Error loading map: Unexpected end of file 4 !\n " << i;
                tilesLoaded = false;
                break;
            }

            // If the number is a valid tile number
            if ((tileType >= 0)) // originally there was tileType< TotalTileSPrites
            {
                tileslayer4[i] = new Tile(x, y, tileType);
            }
            // If we don't recognize the tile type
            else
            {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= LEVEL_WIDTH)
            {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }
	
    map4.close();

		  //If the map was loaded fine
    
	}
	return tilesLoaded;
}



Point TilePLace(Tile* tiles[]){
	srand(time(0));
	for ( int i = 0; i < TOTAL_TILES; 	i++ ){
		int j=rand()%5000;
		if (tiles[j]->getType() != 0 && !tiles[j]->SetPoint){
			
			return Point(tiles[j]);
		}
		
	}
	return Point(tiles[0]);
}

void mainLoop(GameManager &manager)
{
	// main loop
	bool quit = false;
	Uint32 lastFrame = SDL_GetTicks();
	do
	{
		Uint32 current = SDL_GetTicks();
		Uint32 tpf = current - lastFrame;
		lastFrame = current;

		// check for key presses / exit
		quit = manager.handleInput();

		// update player paddle position
		manager.update(tpf);

		// render scene
		manager.render();

		while (tpf < 10) {
			// limit to max 100 fps
			SDL_Delay(10);
			current = SDL_GetTicks();
			tpf = current - lastFrame;
		}

	} while (!quit);
}

void renderBoard()
{
    // vertical lines
    SDL_RenderDrawLine( gRenderer,
         SCREEN_WIDTH/3, 0,
         SCREEN_WIDTH/3,  SCREEN_HEIGHT);

    SDL_RenderDrawLine( gRenderer,
         SCREEN_WIDTH/3*2, 0,
         SCREEN_WIDTH/3*2,  SCREEN_HEIGHT);

    // horizontal lines
    SDL_RenderDrawLine( gRenderer,
        0,  SCREEN_HEIGHT/3,
         SCREEN_WIDTH,  SCREEN_HEIGHT/3);

    SDL_RenderDrawLine( gRenderer,
        0,  SCREEN_HEIGHT/3*2,
         SCREEN_WIDTH,  SCREEN_HEIGHT/3*2);
}

void drawCross(int row, int col)
{
    int fieldW =  SCREEN_WIDTH/3;
    int fieldH =  SCREEN_HEIGHT/3;

    // top left to bottom right
    SDL_RenderDrawLine( gRenderer,
        col*fieldW, row*fieldH,
        col*fieldW+fieldW, row*fieldH+fieldH);

    // top right to bottom left
    SDL_RenderDrawLine( gRenderer,
        col*fieldW, row*fieldH+fieldH,
        col*fieldW+fieldW, row*fieldH);
}

// render circle on board field (boardX, boardY)
void drawCircle(int row, int col)
{
    int fieldW =  SCREEN_WIDTH/3;
    int fieldH =  SCREEN_HEIGHT/3;

    // calculate circle center
    int centerX = col*fieldW+(fieldW/2);
    int centerY = row*fieldH+(fieldH/2);

    int r = fieldW/2;

    double step = 2*M_PI/30;
    int endX = centerX + r;
    int endY = centerY;

    // draw circle.. Multiple straight lines between consecutive
    // points of the desired circle
    for(double angle=0; angle<2*M_PI; angle+=step)
    {
        int startX = endX;
        int startY = endY;
        endX = r * cos(angle) + centerX;
        endY = r * sin(angle) + centerY;
        SDL_RenderDrawLine( gRenderer, startX, startY, endX, endY);
    }
}

void renderPieces(Board board)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            switch(board.m[i][j])
            {
                case PIECE_X:
                    drawCross(i, j); break;
                case PIECE_O:
                    drawCircle(i, j); break;
                default:
                    break;
            }
        }
}

void InitSprite(){

	snake.sprite[0].x = snake.sprite[0].y = 0;
	snake.sprite[0].h = snake.sprite[0].w = SIZE;

	snake.sprite[1].x = SIZE;
	snake.sprite[1].y = 0;
	snake.sprite[1].w = snake.sprite[1].h = SIZE;

}

bool Pressed(SDL_Scancode key){

	return (keypressed == key);

}

bool GetKeys(){

	while (SDL_PollEvent(&event) != 0){

		if (event.type == SDL_QUIT){
			return 1;
		}
		if (event.type == SDL_KEYDOWN){

			keypressed = event.key.keysym.scancode;

			switch (keypressed){
				case SDL_SCANCODE_P: pauseGame = !pauseGame; break;
				case SDL_SCANCODE_ESCAPE: return 1;
			}
		}
	}

	if (!pauseGame){

		if (Pressed(SDL_SCANCODE_UP) || Pressed(SDL_SCANCODE_W)){
			if (snake.dir != 'D')
				snake.dir = 'U';
		}
		if (Pressed(SDL_SCANCODE_DOWN) || Pressed(SDL_SCANCODE_S)){
			if (snake.dir != 'U')
				snake.dir = 'D';
		}
		if (Pressed(SDL_SCANCODE_LEFT) || Pressed(SDL_SCANCODE_A)){
			if (snake.dir != 'R')
				snake.dir = 'L';
		}
		if (Pressed(SDL_SCANCODE_RIGHT) || Pressed(SDL_SCANCODE_D)){
			if (snake.dir != 'L')
				snake.dir = 'R'; 
		}
		if (Pressed(SDL_SCANCODE_R)){
			
		}

	}

	return 0;
}

bool BodyCollision(int x, int y){

	for (int i = 0; i < snake.totalSegmento; i++)
		if ((snake.segmento[i].x == x) && (snake.segmento[i].y == y))
			return true;

	return false;
}

bool CheckCollision(int x, int y){

	if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT && !BodyCollision(x, y))
		return false;

	return true;
}

SDL_Rect CreateFood(){

	SDL_Rect *posLivre = new SDL_Rect[AREA];
	int posLivreCont = 0;
	int contX, contY;
	int posSorteada = 0;

	for (contX = 0; contX < SCREEN_WIDTH; contX += SIZE){
		for (contY = 0; contY < SCREEN_HEIGHT; contY += SIZE){
			if (!BodyCollision(contX, contY)){
				posLivreCont++;
				posLivre[posLivreCont].x = contX;
				posLivre[posLivreCont].y = contY;
			}
		}
	}

	srand(SDL_GetTicks());

	posSorteada = rand() % posLivreCont + 1;

	posLivre[posSorteada].w = posLivre[posSorteada].h = SIZE;

	return posLivre[posSorteada];
}

void PrintSnake(){

	SDL_RenderCopy(gRenderer, snake.segmentTexture, &snake.sprite[0], &snake.segmento[0]);

	for (int i = snake.totalSegmento; i > 0; i--){
		SDL_RenderCopy(gRenderer, snake.segmentTexture, &snake.sprite[0], &snake.segmento[i]);
	}

}

void PauseScreen(){

	SDL_Rect pauseRect = { SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 188, 48 };

	PrintSnake();

	SDL_RenderCopy(gRenderer, pauses, NULL, &pauseRect);

}
const int TAXA_CRESCIMENTO = 4;
bool MoveSnake(){

	SDL_Rect newpos;
	
	newpos = snake.segmento[0];

	switch (snake.dir){
		case 'R': newpos.x += SIZE; break;
		case 'L': newpos.x -= SIZE; break;
		case 'U': newpos.y -= SIZE; break;
		case 'D': newpos.y += SIZE; break;
	}

	if (!CheckCollision(newpos.x, newpos.y)){
		if (snake.totalSegmento < snake.dimensao){
			snake.totalSegmento++;
		}
			
		snake.segmento[0] = newpos;

		for (int i = snake.totalSegmento; i > 0; i--){
			snake.segmento[i] = snake.segmento[i - 1];
		}

		if ((snake.segmento[0].x == food.foodPos.x) && (snake.segmento[0].y == food.foodPos.y) && (snake.totalSegmento != AREA)){
			food.foodPos = CreateFood();
			snake.dimensao += TAXA_CRESCIMENTO;
		}

	}
	else{
		
	}

	return true;
}

void InitSnake(){

	snake.frame = 0;
	snake.segmento[0] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SIZE, SIZE };
	snake.dir = 'R';
	snake.dimensao = TAXA_CRESCIMENTO;
	snake.totalSegmento = 1;

}

void InitFood(){

	food.foodPos = CreateFood();
	food.foodPos.h = food.foodPos.w = SIZE;

}

void NewRound(){

	InitSprite();
	InitSnake();
	InitFood();
	pauseGame = false;

}

void GameLoop(bool &quit){

	quit = GetKeys();

	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, background, NULL, NULL);

	if (!pauseGame)
		MoveSnake();
	else
		PauseScreen();

	PrintSnake();

	SDL_RenderCopy(gRenderer, food.foodTexture, NULL, &food.foodPos);

	SDL_RenderPresent(gRenderer);


}


int main( int argc, char* argv[] )
{
	//starting sockets for client
	//  Client connecting to server

	int cli_fd, bytes_sent, bytes_recvd;
	int port_no = PORT;
	char in_buffer[45], out_buffer[45], sname[16], cname[16];

	struct Info indata;
	struct Info mydata = {42, 5, 6, 7, 8, 9, 1, 4,0,0,0};
	bool validate_data;

	// IP address of server
	//char serv_ip[INET_ADDRSTRLEN] = "192.168.43.130";
	char serv_ip[INET_ADDRSTRLEN]= "127.0.0.1";

	struct sockaddr_in serv_addr;

	// if (argc != 2)
	//{
	//	perror("Incomplete arguments!");
	//	return 1;
	// }

	if ((cli_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Sorry. Socket could not be created!");
		return 1;
	}
	int opt = 1;

	if (setsockopt(cli_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);

	// Convert IPv4 addresses from text to binary form
	if (inet_pton(AF_INET, serv_ip, &serv_addr.sin_addr) <= 0)
	{
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}
	cout << "Socket created and trying to connect\n";

	if (connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Sorry. Could not connect to server.");
		return 1;
	}
	//fcntl(cli_fd, F_SETFL, fcntl(cli_fd, F_GETFL, 0) | O_NONBLOCK);

	cout << "Connected (hopefully)\n";



	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		
		//Load media
		if( !loadMedia( tileSet1,tileSet2,tileSet3,tileSet4 ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			bool fullScreen =false;

			//The dot that will be moving around on the screen
			
			
			for ( int k=0;k<10;k++){
			 	arr[k]=TilePLace(tileSet2);
			}

			// YULU
			// 54,35
			// 63,14
			// 102,32
			//145,44
			//145,15
			//12,51
			//6,10

				// Zanskar -> 34,18
			//Shiwalik -> 35,25
			// OCS -> 121,34
			//
			Powerup p1(tileSet3[150*34 + 55]);
			Powerup p2(tileSet3[150*15 + 64]);
			Powerup p3(tileSet3[150*33 + 105]);
			Powerup p4(tileSet3[150*46 + 146]);
			Powerup p5(tileSet3[150*18 + 146]);
			Powerup p6(tileSet3[150*50 + 14]);
			Powerup p7(tileSet3[150*11 + 7]);

			Powerup arr1[7] = {p1,p2,p3,p4,p5,p6,p7};

			//hostel tasks
			Tasks t1(tileSet3[150*12 + 12],"Do debating in jwala",0,1); // jwala
			Tasks t2(tileSet3[150*20 + 12],"Take part in dance competition in Aravali",0,2); // aravali
			Tasks t3(tileSet3[150*27 + 12],"Take part in PFC Workshop in Nilgiri",0,3); // nilgiri
 			Tasks t4(tileSet3[150*37 + 12],"Play snooker in Karakoram",0,4); //kara
			Tasks t5(tileSet3[150*6 + 23],"Take part in Drama Workshop in Kumaon",0,5); //kumaon
			Tasks t6(tileSet3[150*8 + 79],"Do Quizzing in Udaigiri",0,6); //Udai
			Tasks t7(tileSet3[150*6 + 42],"Play BasketBall with your friends in Vindy",0,7); //vindy
			Tasks t8(tileSet3[150*5 + 64],"Participate in Kavi Sammelan in Satpura",0,8); //satpura
			Tasks t9(tileSet3[150*12 + 76],"Participate in a hackathon in Girnar",0,9); // girnar
			Tasks t10(tileSet3[150*12 + 121],"Take part in Singing Competition",0,10); //himadri
			Tasks t11(tileSet3[150*8 + 126],"Attend a painting workshop in Kailash",0,11); //kailash
			// ta


			//money tasks
			Tasks t12(tileSet3[150*48 + 148],"Do an off-campus internship",1,12); // main gate

			Tasks t13(tileSet3[150*19 + 148],"Do a research internship with a Professor",1,13); // gate 6
			Tasks t14(tileSet3[150*1 + 16],"Do an off-campus internship",1,14); //gate 3
			// task regarding OCS pending

			//cg
			Tasks t15(tileSet3[150*15 + 98],"Go to CSC and complete your assignment",2,15); //main building
			Tasks t16(tileSet3[150*37 + 105],"Attend a Class in LHC",2,16); //lhc
			Tasks t17(tileSet3[150*26 + 78],"Meet Prof. Rijurekha and discuss regarding a project idea",2,17);  // bharti
			Tasks t18(tileSet3[150*23 + 102],"Issue a book on Computer Vision and read it",2,18); // library

			//health
			Tasks t19(tileSet3[150*43 + 71],"Play Cricket Match or do practice",3,19); //cricket
			Tasks t20(tileSet3[150*43 + 95],"Play Football Match or do practice",3,20); //football
			Tasks t21(tileSet3[150*22 + 25],"Play a Lawn-Tennis Match or do practice",3,21); //tennis
			Tasks t22(tileSet3[150*14 + 25],"Play a VolleyBall Match or do practice",3,22); //volleyball
			Tasks t23(tileSet3[150*44 + 41],"Play a Table-Tennis Match or do practice",3,23); //table tennis

			Tasks t24(tileSet3[150*43 + 47],"Take part in Group Dance Competition",3,24); //OAT


			Tasks t25(tileSet3[150*23 + 18],"Have food at Delhi 16",4,25); //delhi 16
			Tasks t26(tileSet3[150*26 + 48],"Have food at Rajdhani",4,26); //rajdhani
			Tasks t27(tileSet3[150*29 + 55],"Have food at Masala Mix",4,27); //masala mix
			Tasks t28(tileSet3[150*16 + 69],"Have food at Night Mess",4,28); // night mess
			Tasks t29(tileSet3[150*19 + 91],"Have Ice-Cream at Amul",4,29); //amul
			Tasks t30(tileSet3[150*23 + 96],"Have a juice at Shiru Cafe",4,30); //shiru

			Tasks t31(tileSet3[150*28 + 69],"Get a CheckUp done at the IITD Hospital",5,31); //hospital
			
			Tasks t32(tileSet3[150*34 + 121],"Do an On-campus Internship through OCS",6,32); //OCS
			Tasks t33(tileSet3[150*18 + 34],"Meet your friends in Zanskar and have a chat with them",0,33); //Zanskar
			Tasks t34(tileSet3[150*25 + 35],"Do gymming in Shivalik",0,34); //hospital





			

			// // int location[9] = {100*24 + 38,100*22 + 47,100*23 + 64,100*4 + 8,100*16 + 49};
			Tasks task[34] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28,t29,t30,t31,t32,t33,t34};
			// for (int i=0;i<9;i++){
			// 	task[i].type=0; //hostel
			// 	task[i].msg="hostel task";
			// }

			// Tasks finaltask[4];
			// srand(time(0));
			// for (int i = 0; i < 4; i++)
			// {
			// 	int k = rand() % 9;
			// 	finaltask[i] = task[k];
				
			// }	
			// Point p2(tileSet[1]);

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			bool done = false;


			LTimer Timerframe;

			LTimer gameTimer;

			LButton gameStartButton; 
			gameStartButton.InitialiseButton(1,&gameTimer,&curr_state,0.4,0.25,0.2,0.25,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/start-up.png","assets/start-down.png");
			
			LButton InfoButton; 
			InfoButton.InitialiseButton(1,&gameTimer,&curr_state,0.01,0.92,0.04,0.06,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/infobutton.png","");

			LButton ResumeButton; 
			ResumeButton.InitialiseButton(1,&gameTimer,&curr_state,0.01,0.92,0.06,0.08,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/resume1.png","");
			
			LButton RetryButton; 
			RetryButton.InitialiseButton(1,&gameTimer,&curr_state,0.45,0.65,0.09,0.12,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/restart1.png","");

			LButton ExitButton; 
			ExitButton.InitialiseButton(1,&gameTimer,&curr_state,0.45,0.85,0.09,0.12,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/exit1.png","");
			
			
			LButton girnar; 
			girnar.InitialiseButton(1,&gameTimer,&curr_state,0.05,0.25,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/GIRNAR.png","");
			
			LButton udaigiri; 
			udaigiri.InitialiseButton(1,&gameTimer,&curr_state,0.30,0.25,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/UDAIGIRI.png","");
			
			LButton satpura; 
			satpura.InitialiseButton(1,&gameTimer,&curr_state,0.55,0.25,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/SATPURA.png","");
			
			LButton kumaon; 
			kumaon.InitialiseButton(1,&gameTimer,&curr_state,0.80,0.25,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/KUMAON.png","");
			
			
			
			LButton nilgiri; 
			nilgiri.InitialiseButton(1,&gameTimer,&curr_state,0.05,0.40,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/NILGIRI.png","");
			
			LButton karakoram; 
			karakoram.InitialiseButton(1,&gameTimer,&curr_state,0.30,0.40,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/KARAKORAM.png","");

			LButton himadri; 
			himadri.InitialiseButton(1,&gameTimer,&curr_state,0.55,0.40,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/HIMADRI.png","");
			
			LButton kailash; 
			kailash.InitialiseButton(1,&gameTimer,&curr_state,0.80,0.40,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/KAILASH.png","");
			
			
			
			LButton aravali; 
			aravali.InitialiseButton(1,&gameTimer,&curr_state,0.05,0.55,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/ARAVALI.png","");
			
			LButton vindyanchal; 
			vindyanchal.InitialiseButton(1,&gameTimer,&curr_state,0.30,0.55,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/VINDY.png","");
			
			LButton zanskar; 
			zanskar.InitialiseButton(1,&gameTimer,&curr_state,0.55,0.55,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/ZANSKAR.png","");
			
			LButton shiwalik; 
			shiwalik.InitialiseButton(1,&gameTimer,&curr_state,0.80,0.55,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/SHIWALIK.png","");
			
			
			LButton jwalamukhi; 
			jwalamukhi.InitialiseButton(1,&gameTimer,&curr_state,0.05,0.70,0.1,0.1,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/JWALA.png","");
			
			LButton laughEmote; 
			laughEmote.InitialiseButton(1,&gameTimer,&curr_state,0.1,0.01,0.04,0.06,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/laughing emote.png","");
			

			LButton angryEmote; 
			angryEmote.InitialiseButton(1,&gameTimer,&curr_state,0.15,0.01,0.04,0.05,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/angry_emote1.png","");
			
			
			LButton coolEmote; 
			coolEmote.InitialiseButton(1,&gameTimer,&curr_state,0.20,0.01,0.04,0.06,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/cool emoji1.png","");

			LButton teaseEmote; 
			teaseEmote.InitialiseButton(1,&gameTimer,&curr_state,0.25,0.01,0.04,0.06,"sounds/mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/tease1.png","");
			//int lastTime = 0,currentTime;
			//While application is running
			int countedFrames = 0;

			// random seed
			srand(time(NULL));

			// create entities
			PlayerPaddle pp(gRenderer, "res/paddle_r.png", 20, GameManager::screenH/2, playerSpeed);
			pp.init();
			pp.setDisabled(playerDisabled);

			// left ai
			AiPaddle aiLeft(gRenderer, "res/paddle_r.png", 20, GameManager::screenH/2, aiSpeed, true,
				GameManager::screenW/2);
			aiLeft.init();
			aiLeft.setDisabled(!playerDisabled);

			// right ai
			AiPaddle aiRight(gRenderer, "res/paddle_r.png", GameManager::screenW-20, GameManager::screenH/2, aiSpeed, false,
				GameManager::screenW/2);
			aiRight.init();

			// ball
			Ball ball(gRenderer, "res/ball.png", GameManager::screenW/2, GameManager::screenH/2,
					initialBallXSpeed, initialBallYSpeed);
			ball.init();

			GameManager manager(gRenderer, ball, pp, aiLeft, aiRight);
			manager.init(GameManager::screenW, GameManager::screenH);

			// set initial positions
			manager.restartRound();

			int state=1;
			bool humanTurn=true;
			Bot bot=Bot();
    		Board board=Board();


			while( !quit )
			{

				Timerframe.start();
				if(curr_state == 0)
				{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle key press
                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            //Play high sound effect
                            case SDLK_1:
                            Mix_PlayChannel( -1, gHigh, 0 );
                            break;
                            
                            //Play medium sound effect
                            case SDLK_2:
                            Mix_PlayChannel( -1, gMedium, 0 );
                            break;
                            
                            //Play low sound effect
                            case SDLK_3:
                            Mix_PlayChannel( -1, gLow, 0 );
                            break;
                            
                            //Play scratch sound effect
                            case SDLK_4:
                            Mix_PlayChannel( -1, gScratch, 0 );
                            break;

							case SDLK_9:
                            //If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            //If music is being played
                            else
                            {
                                //If the music is paused
                                if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
                            break;
                            
                            case SDLK_0:
                            //Stop the music
                            Mix_HaltMusic();
                            break;
                        }
                    }

					
					//Handle input for the dot
					gameStartButton.handleEvent(&e , 1);

					
				}

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
            	SDL_RenderClear(gRenderer);
				StartScreenTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

				gameStartButton.render();
				SDL_RenderPresent(gRenderer);
			}
			else if(curr_state==1)
			{
				
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle key press
                    girnar.handleEvent(&e,2);
					if(curr_state==2){dot.mBox.x=32*75;dot.mBox.y = 32*12;curr_state = 5;};
					udaigiri.handleEvent(&e,3);
					if(curr_state==3){dot.mBox.x=32*78;dot.mBox.y = 32*5;curr_state=5;};
					satpura.handleEvent(&e,4);
					if(curr_state==4){dot.mBox.x=32*63;dot.mBox.y = 32*5;curr_state=5;};
					kumaon.handleEvent(&e,9);
					if(curr_state==9){dot.mBox.x=32*23;dot.mBox.y = 32*6;curr_state = 5;};
					nilgiri.handleEvent(&e,10);
					if(curr_state==10){dot.mBox.x=32*11;dot.mBox.y = 32*27;curr_state=5;};
					karakoram.handleEvent(&e,11);
					if(curr_state==11){dot.mBox.x=32*11;dot.mBox.y = 32*37;curr_state=5;};

					himadri.handleEvent(&e,12);
					if(curr_state==12){dot.mBox.x=32*120;dot.mBox.y = 32*12;curr_state=5;};
					kailash.handleEvent(&e,13);
					if(curr_state==13){dot.mBox.x=32*125;dot.mBox.y = 32*8;curr_state=5;};

					shiwalik.handleEvent(&e,14);
					if(curr_state==14){dot.mBox.x=32*8;dot.mBox.y = 32*0;curr_state=5;};
					zanskar.handleEvent(&e,15);
					if(curr_state==15){dot.mBox.x=32*8;dot.mBox.y = 32*0;curr_state=5;};
					aravali.handleEvent(&e,16);
					if(curr_state==16){dot.mBox.x=32*11;dot.mBox.y = 32*20;curr_state=5;};
					vindyanchal.handleEvent(&e,17);
					if(curr_state==17){dot.mBox.x=32*42;dot.mBox.y = 32*6;curr_state=5;};

					jwalamukhi.handleEvent(&e,18);
					if(curr_state==18){dot.mBox.x=32*11;dot.mBox.y = 32*12;curr_state=5;};
				}
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
            	SDL_RenderClear(gRenderer);
				HostelTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

				girnar.render();
				udaigiri.render();
				satpura.render();
				kumaon.render();

				nilgiri.render();
				karakoram.render();
				himadri.render();
				kailash.render();

				shiwalik.render();
				aravali.render();
				zanskar.render();
				vindyanchal.render();

				jwalamukhi.render();
				SDL_RenderPresent(gRenderer);

					
			}
			else if(curr_state == 5 && curr_stateP2==5){
				//if (emotetimer==0) emote=0;
				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
							case SDLK_9:
                            //If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            //If music is being played
                            else
                            {
                                //If the music is paused
                                if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
                            break;
                            
                            case SDLK_0:
                            //Stop the music
                            Mix_HaltMusic();
                            break;
                        }
                    }
					else if (e.type== SDL_SYSWMEVENT ){
						fullScreen = !fullScreen;
						if(fullScreen){
							SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
						}
						else{
							SDL_SetWindowFullscreen(gWindow, 0);
						}
					}

					//dot.handleEvent( e );
					dot.handleEvent( e );
					//if(ti == 0){curr_state=7;}
					//dot2.handleEvent( e );
					laughEmote.handleEvent(&e,25);
					if(curr_state ==25){emote = 1; emotetimer=5; curr_state = 5;}
					angryEmote.handleEvent(&e,26);
					if(curr_state ==26){emote = 2;emotetimer=5;curr_state = 5;}
					coolEmote.handleEvent(&e,27);
					if(curr_state ==27){emote = 3;emotetimer=5;curr_state = 5;}
					teaseEmote.handleEvent(&e,28);
					if(curr_state ==28){emote = 4;emotetimer=5;curr_state = 5;}
					InfoButton.handleEvent(&e , 6); 
					//dot2.handleEvent( e );
					
				}
				// const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				//dot.handle(currentKeyStates);
				// dot2.handle(currentKeyStates);

				//Move the dot
				
				SDL_Color textColor = { 0, 0, 0 };
				//Move the dot
				if (dot.waitime==0) dot.move( tileSet2,tileSet3,gHigh,gMedium,gLow );
				else {
					gTextTexture.loadFromRenderedText("Wait for : "+to_string(dot.waitime),textColor,myFont,gRenderer);
					gTextTexture.render(gRenderer,SCREEN_WIDTH/2,0,0,0);
				}
				dot.setCamera( camera );



				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet1[ i ]->render( gRenderer,camera,&gTileTexture1);
				}

				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					if (tileSet2[i]->getType()!=0) tileSet2[ i ]->render( gRenderer,camera,&gTileTexture2);
					//std::cout<<tileSet2[i]->getType()<<"\n";
				}
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					if (tileSet3[i]->getType()!=0) tileSet3[ i ]->render( gRenderer,camera,&gTileTexture3);
				}
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
				 	if (tileSet4[i]->getType()!=0) tileSet4[ i ]->render( gRenderer,camera,&gTileTexture4);
				}

				dot.render(camera,gTextTexture,myFont,gRenderer);
				
				enemy1.move(tileSet2);
				enemy2.move(tileSet2);
				enemy3.move(tileSet2);
				// Render Names
				gTextTexture.loadFromRenderedText("Tennis",textColor,gFont,gRenderer);
				gTextTexture.render(gRenderer,1100-camera.x,480-camera.y,0,0);
				gTextTexture.loadFromRenderedText("SAC",textColor,gFont,gRenderer);
				gTextTexture.render(gRenderer,1280-camera.x,1280-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Main",textColor,gFont,gRenderer); //98,14
				gTextTexture.render(gRenderer,3136-camera.x,448-camera.y,0,0);
				gTextTexture.loadFromRenderedText("LHC",textColor,gFont,gRenderer);//110,34
				gTextTexture.render(gRenderer,3520-camera.x,1088-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Library",textColor,gFont,gRenderer);//102,27
				gTextTexture.render(gRenderer,3264-camera.x,864-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Bharti",textColor,gFont,gRenderer);//76,26
				gTextTexture.render(gRenderer,2432-camera.x,842-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Himadri",textColor,gFont,gRenderer);//119,15
				gTextTexture.render(gRenderer,3808-camera.x,480-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Kailash",textColor,gFont,gRenderer);//124,6
				gTextTexture.render(gRenderer,3968-camera.x,192-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Udaigiri",textColor,gFont,gRenderer);//77,4
				gTextTexture.render(gRenderer,2464-camera.x,128-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Girnar",textColor,gFont,gRenderer);//74,11
				gTextTexture.render(gRenderer,2368-camera.x,352-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Satpura",textColor,gFont,gRenderer);//64,4
				gTextTexture.render(gRenderer,2048-camera.x,128-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Kumaon",textColor,gFont,gRenderer);//22,4
				gTextTexture.render(gRenderer,704-camera.x,128-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Hospital",textColor,gFont,gRenderer);//65,25
				gTextTexture.render(gRenderer,2080-camera.x,800-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Jwala",textColor,gFont,gRenderer);//10,10
				gTextTexture.render(gRenderer,320-camera.x,320-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Aravali",textColor,gFont,gRenderer);//10,20
				gTextTexture.render(gRenderer,320-camera.x,640-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Food",textColor,gFont,gRenderer);//69,15
				gTextTexture.render(gRenderer,2208-camera.x,480-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Residency",textColor,gFont,gRenderer);//32,66
				gTextTexture.render(gRenderer,1024-camera.x,2112-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Nalanda",textColor,gFont,gRenderer);//20,34
				gTextTexture.render(gRenderer,640-camera.x,1088-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Nilgiri",textColor,gFont,gRenderer);//10,25
				gTextTexture.render(gRenderer,320-camera.x,800-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Karakoram",textColor,gFont,gRenderer);//9,35
				gTextTexture.render(gRenderer,288-camera.x,1120-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Cricket",textColor,gFont,gRenderer);//68,38
				gTextTexture.render(gRenderer,2176-camera.x,1216-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Football",textColor,gFont,gRenderer);//88,38
				gTextTexture.render(gRenderer,2816-camera.x,1216-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Amul",textColor,gFont,gRenderer);//90,18
				gTextTexture.render(gRenderer,2880-camera.x,576-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Visitor",textColor,gFont,gRenderer);//133,25
				gTextTexture.render(gRenderer,4256-camera.x,800-camera.y,0,0);
				gTextTexture.loadFromRenderedText("OAT",textColor,gFont,gRenderer);//46,42
				gTextTexture.render(gRenderer,1472-camera.x,1344-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Delhi16",textColor,gFont,gRenderer);//17,19
				gTextTexture.render(gRenderer,544-camera.x,608-camera.y,0,0);
				gTextTexture.loadFromRenderedText("Vindy",textColor,gFont,gRenderer);//41,4
				gTextTexture.render(gRenderer,41*32-camera.x,4*32-camera.y,0,0);
				
				MinimapTexture.render(gRenderer,1500,0,0,0);
				dot2.renderPlayer2(camera,gTextTexture,myFont,gRenderer);

				if (emotetimer!=0){
					if (emote==1){
						HappyTexture.render(gRenderer,SCREEN_WIDTH-150,SCREEN_HEIGHT-150,0);
					}
					if (emote==2){
						AngryTexture.render(gRenderer,SCREEN_WIDTH-150,SCREEN_HEIGHT-150,0);
					}
					if (emote==4){
						TeaseTexture.render(gRenderer,SCREEN_WIDTH-150,SCREEN_HEIGHT-150,0);
					}
					if (emote==3){
						CoolTexture.render(gRenderer,SCREEN_WIDTH-150,SCREEN_HEIGHT-150,0);
					}
				}
				//dot2.move(tileSet2,gHigh,gMedium,gLow);
				//dot2.setCamera( camera);
				//Clear screen
				
				//Render dot
				//dot.render( camera,gTextTexture,gFont,gRenderer);
				enemy1.render(camera,gRenderer);
				enemy2.render(camera,gRenderer);
				enemy3.render(camera,gRenderer);

				

				if (dot.myfunctions.checkCollision(dot.mBox,enemy1.mBox)) {
					if(dot.health > 40){
						dot.health -= 40;
					}
					else {}
				}
				if(dot.myfunctions.checkCollision(dot.mBox,dot2.mBox) && !dot.isPowerUpEnabled && dot2.isPowerUpEnabled) {dot.health-= 50;dot2.isPowerUpEnabled=false;}
				if(dot.myfunctions.checkCollision(dot.mBox,dot2.mBox) && dot.isPowerUpEnabled && !dot2.isPowerUpEnabled) {dot.isPowerUpEnabled=false;}
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy1.mBox)) quit=true;
				if (dot.myfunctions.checkCollision(dot.mBox,enemy2.mBox)) quit=true;
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy2.mBox)) quit=true;
				if (dot.myfunctions.checkCollision(dot.mBox,enemy3.mBox)) quit=true;
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy3.mBox)) quit=true;

				for (int i=0;i<TOTAL_TILES;i++){
					if (dot2.myfunctions.checkCollision(dot2.mBox,tileSet3[i]->getBox())){
						tileSet3[i]->SetTask=NULL;
					}
					if (dot2.myfunctions.checkCollision(dot2.mBox,tileSet3[i]->getBox())){
						if (tileSet3[i]->SetPowerUp==true){
							dot2.isPowerUpEnabled=true;
						}
					}
				}

				currentTime1 = SDL_GetTicks();
				if(currentTime1 > lastTime1 + 1000) //ms to wait before change angle
				{
					if (ti>0){
						ti -= 1;
						if (emotetimer!=0) emotetimer-=1;
						if (dot.waitime!=0) dot.waitime-=1;
						if(ti%3 == 0 && dot.money > 0){
							dot.money-=1;
						}
						else if(ti%2 == 0 && dot.health > 0 ){
							dot.health-=1;
						}
						else if(ti%60 == 0 && dot.CG > 0){
							dot.CG -= 1;
						}
						lastTime1 = currentTime1;
					}
					else {
						currentTime1 = 0;
					}
				}
				timerRender();
				// currentTime = SDL_GetTicks();

				// if(currentTime > lastTime + 20000) //ms to wait before change angle
				// {
				// 	for (int k=0;k<5;k++){
				// 		arr1[k].GetTile()->SetPowerUp =true; 
				// 	}
				// 	dot.speed1=false;
				// 	dot2.speed1=false;
				// 	lastTime = currentTime;
				// }
			
				// p1.Render(camera);
				// p2.Render(camera);
				// p3.Render(camera);
				// p4.Render(camera);
				// p5.Render(camera);
				// p6.Render(camera);
				
				

				for (int k=0;k<10;k++){

					if (arr[k].GetTile()->SetPoint==true ) {
						
						arr[k].Render(camera,gRenderer);
					}
				}


				for (int k=0;k<7;k++){
				 	if (arr1[k].GetTile()->SetPowerUp==true) arr1[k].Render(camera,gRenderer);
				}

				for (int k=0;k<34;k++){
					if (task[k].GetTile()->SetTask==true) task[k].Render(camera,gRenderer);
				}
				//Update screen
				InfoButton.render();
				laughEmote.render();
				angryEmote.render();
				coolEmote.render();
				teaseEmote.render();
				SDL_RenderPresent( gRenderer );
			}
			else if (curr_state==6)
			{
				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//dot.handleEvent( e );
					ResumeButton.handleEvent(&e,5);
					
				}

				InfoScreenTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				SDL_Color textcolor1 = {255,255,255};
				vector<Tasks> taskLeft;
				for (int i = 0; i < 34; i++)
				{
					if(task[i].GetTile()->SetTask){
						taskLeft.push_back(task[i]);
					}
				}
				
				for (int i = 0; i < taskLeft.size() - 1; i++)
				{
					gTextTexture.loadFromRenderedText(taskLeft[i].msg,textcolor1,myFont,gRenderer);//41,4
					if(i < 17){
						gTextTexture.render(gRenderer,100,150 + 35*i,0,0);
					}
					else {
						gTextTexture.render(gRenderer,1000,150 + 35*(i-17),0,0);
					}
					
				}
				ResumeButton.render();
				SDL_RenderPresent( gRenderer );
			}
			else if (curr_state == 7 ) 
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						curr_state=8;
						//quit = true;
					}

					//dot.handleEvent( e );
					RetryButton.handleEvent(&e,0);
					ExitButton.handleEvent(&e,8);
				}
				EndScreenTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				RetryButton.render();
				ExitButton.render();
				double calc1=(double)log((int)dot.CG/10+1)+log((double)dot.health/100+1)+log((double)dot.money/170+1);
				double calc2=(double)log((int)dot2.CG/10+1)+log((double)dot2.health/100+1)+log((double)dot2.money/170+1);
				SDL_Color textColor = { 0, 0, 0 };
				if (calc1>calc2+0.0005){
					Win.render(gRenderer,SCREEN_WIDTH/2 - 125,100);
					gTextTexture.loadFromRenderedText("Hurray! You won the game",textColor,gFont,gRenderer);//41,4
					gTextTexture.render(gRenderer,SCREEN_WIDTH/2-100,375,0,0);
				}
				else if (calc2>calc1+0.0005){
					Lose.render(gRenderer,SCREEN_WIDTH/2 - 125,100);
					gTextTexture.loadFromRenderedText("You lost the game, Better Luck Next Time",textColor,gFont,gRenderer);//41,4
					gTextTexture.render(gRenderer,SCREEN_WIDTH/2-125,375,0,0);
				}
				else{
					gTextTexture.loadFromRenderedText("Looks like you and your opponent played with the same skill, It's a Stalemate!!!",textColor,gFont,gRenderer);//41,4
					gTextTexture.render(gRenderer,SCREEN_WIDTH/2-150,375,0,0);
				}
				SDL_RenderPresent( gRenderer );
				SDL_Delay(10);
			}
			else if (curr_state==8){
				// game logic
				mainLoop(manager);
				cout<<"hao\n";
				quit=true;
			}
			else if (curr_state==9){
				while(SDL_PollEvent(&e))
				{
					if(e.type == SDL_QUIT)
						quit = true;
				}
				if(state == 0)
					curr_state=7;
				else
				{
					bool successfulPlay = false; // to handle change of player turn

					// process human or pc turn
					if(!humanTurn)
					{
						bot.play(board);
						successfulPlay = true;
					}
					else
					{
						// did the human play?
						if(e.type == SDL_MOUSEBUTTONDOWN)
						{
							// get mouse coordinates and normalize to row/col
							int x, y;
							SDL_GetMouseState(&x, &y);
							int row = y/(SCREEN_HEIGHT/3);
							int col = x/(SCREEN_WIDTH/3);

							// try to validate the move
							if(board.isFieldEmpty(row,col))
							{
								board.place(row,col);
								successfulPlay = true;
							}
						}
					}

					// change turns
					if(successfulPlay)
					{
						humanTurn = !humanTurn;
						SDL_Delay(100); // delay between turns
					}
				}
				// bg
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// game objects
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

				renderBoard();
				renderPieces(board);

				// render
				SDL_RenderPresent(gRenderer);
				if(board.hasWinner() || board.isDraw())
        			state = 0; // so the game loop knows the end of the current game
			}
			else if (curr_state==10){
				NewRound();
				while(!quit){
					GameLoop(quit);
				}

				
			}

			if ((curr_state != 0 && curr_state!=7 &&curr_state!=8) )
		{
			// sending
			int var=0;
			if (ti==0) {
				var=1;
				curr_state=7;
			}
			int var2=0;
					if (emotetimer>1){
						var2=emote;
					}
					else var2=0;
			mydata = {dot.myState.first, dot.myState.second, dot.mBox.x, dot.mBox.y, curr_state, (int)dot.health, (int)dot.CG, (int)dot.money,dot.tasksComp,var,var2};

			toNetwork(out_buffer, &mydata);
			bytes_sent = send(cli_fd, &out_buffer, sizeof(out_buffer), 0);
			if (bytes_sent == -1) {
				// cout << "Frame data not sent"
				// 	 << "\n";
				cout<<"hello"<<"\n";
				curr_state=7;
			}
			else if (bytes_sent != 45){
				cout << "complete data not sent, what is going on???????\n";
				curr_state=7;
			}

			// receiving
			bytes_recvd = recv(cli_fd, &in_buffer, sizeof(in_buffer), 0);
			if (bytes_recvd == -1){
				curr_state=7;
				cout << "Frame data not received!"
					 << "\n";
			    dot2.myState.first = 0;
				dot2.myState.second = 1;
				dot2.mBox.x = 0;
				dot2.mBox.y = 0;
				curr_stateP2 = curr_state;
				dot2.health = 0;
				dot2.CG = 0;
				dot2.money = 0;
			}

			else if (bytes_recvd != 45){
				curr_state=7;
				cout << "complete data not received, what is going on!!!\n"<<bytes_recvd<<"\n";
				dot2.myState.first = 0;
				dot2.myState.second = 1;
				dot2.mBox.x = 0;
				dot2.mBox.y = 0;
				curr_stateP2 = curr_state;
				dot2.health = 0;
				dot2.CG = 0;
				dot2.money = 0;
			}
			else
			{
				validate_data = fromNetwork(in_buffer, &indata);
				if (!validate_data)
					cout << "Wrong data received\n";

				else
				{
					dot2.myState.first = indata.stateFirst;
					dot2.myState.second = indata.stateSecond;
					dot2.mBox.x = indata.X;
					dot2.mBox.y = indata.Y;
					curr_stateP2 = indata.myState;
					dot2.health = indata.health;
					dot2.CG = indata.CG;
					dot2.money = indata.money;
					dot2.tasksComp=indata.tusk;
					if (indata.time==1) curr_state=7;
					if (emote!=indata.emoji && indata.emoji!=0) emotetimer=5;
					emote=indata.emoji;
				}
			}
		}
			// If frame finished early
            	int frameTicks = Timerframe.getTicks();
                if (frameTicks < SCREEN_TICK_PER_FRAME)
                {
                        // Wait remaining time
                    SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
                }

				//SDL_Delay(100);
			}

			SDL_DestroyRenderer( gRenderer );
				gameStartButton.close();
				girnar.close();
				udaigiri.close();
				satpura.close();
				kumaon.close();
				nilgiri.close();
				karakoram.close();
				himadri.close();
				kailash.close();

				shiwalik.close();
				aravali.close();
				zanskar.close();
				vindyanchal.close();

				jwalamukhi.close();
				InfoButton.close();
				ResumeButton.close();
				RetryButton.close();
				ExitButton.close();
		}
		//SDLNet_Quit();
		//Free resources and close SDL
		
		close( tileSet1,tileSet2,tileSet3,tileSet4 );
	}

	return 0;
}