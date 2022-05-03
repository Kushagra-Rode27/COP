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

const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 850;

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
	if( !dot.gDotTexture.loadFromFile( "assets/Player1Sprite.png",gRenderer) )
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

	if( !dot2.gDotTexture.loadFromFile( "assets/Player2Sprite1.png" ,gRenderer) )
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
	if( !gTileTexture1.loadFromFile( "./AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture2.loadFromFile( "./AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture3.loadFromFile( "./AtruXd.png" ,gRenderer) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	//Load tile texture
	if( !gTileTexture4.loadFromFile( "./AtruXd.png" ,gRenderer) )
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

	if(!MinimapTexture.loadFromFile("assets/untitled.png",gRenderer)){
		printf("Failed to load mini map texture\n");
		success = false;
	}
	
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

int main( int argc, char* argv[] )
{
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
			
			if (SDLNet_Init() == -1) {
				printf("SDLNet_Init: %s\n", SDLNet_GetError());
				exit(2);
			}

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			
			
			for ( int k=0;k<10;k++){
			 	arr[k]=TilePLace(tileSet2);
			}

			// Powerup p1(tileSet[100*4 + 5]);
			// Powerup p2(tileSet[100*5 + 14]);
			// Powerup p3(tileSet[100*10 + 5]);
			// Powerup p4(tileSet[100*17 + 5]);
			// Powerup p5(tileSet[100*8 + 24]);
			// Powerup p6(tileSet[100*20 + 22]);

			// Powerup arr1[6] = {p1,p2,p3,p4,p5,p6};

			//hostel tasks
			Tasks t1(tileSet4[150*12 + 12]);
			Tasks t2(tileSet4[150*20 + 12]);
			Tasks t3(tileSet4[150*27 + 12]);
			Tasks t4(tileSet4[150*37 + 12]);
			Tasks t5(tileSet4[150*6 + 23]);
			Tasks t6(tileSet4[150*5 + 78]);
			Tasks t7(tileSet4[150*6 + 42]);
			Tasks t8(tileSet4[150*5 + 54]);
			Tasks t9(tileSet4[150*12 + 76]);


			// // int location[9] = {100*24 + 38,100*22 + 47,100*23 + 64,100*4 + 8,100*16 + 49};
			Tasks task[9] = {t1,t2,t3,t4,t5,t6,t7,t8,t9};
			for (int i=0;i<9;i++){
				task[i].type=0; //hostel
				task[i].msg="hostel task";
			}

			Tasks finaltask[4];
			srand(time(0));
			for (int i = 0; i < 4; i++)
			{
				int k = rand() % 9;
				finaltask[i] = task[k];
				
			}	
			// Point p2(tileSet[1]);

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			bool done = false;

			LTimer gameTimer;

			LButton gameStartButton; 
			gameStartButton.InitialiseButton(1,&gameTimer,&curr_state,0.4,0.25,0.2,0.25,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"start-up.png","start-down.png");
			
			LButton InfoButton; 
			InfoButton.InitialiseButton(1,&gameTimer,&curr_state,0.01,0.92,0.04,0.06,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/infobutton.png","");

			LButton ResumeButton; 
			ResumeButton.InitialiseButton(1,&gameTimer,&curr_state,0.01,0.92,0.06,0.08,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/resume1.png","");
			
			LButton RetryButton; 
			RetryButton.InitialiseButton(1,&gameTimer,&curr_state,0.45,0.65,0.09,0.12,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/restart1.png","");

			LButton ExitButton; 
			ExitButton.InitialiseButton(1,&gameTimer,&curr_state,0.45,0.85,0.09,0.12,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/exit1.png","");
			
			
			LButton girnar; 
			girnar.InitialiseButton(1,&gameTimer,&curr_state,0.06,0.25,0.2,0.2,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/GIRNAR.png","");
			
			LButton udaigiri; 
			udaigiri.InitialiseButton(1,&gameTimer,&curr_state,0.4,0.25,0.2,0.2,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/UDAIGIRI.png","");
			
			LButton satpura; 
			satpura.InitialiseButton(1,&gameTimer,&curr_state,0.74,0.25,0.2,0.2,"mixkit-quick-win-video-game-notification-269.wav",gRenderer,"assets/SATPURA.png","");
			
			if (argc == 2 && strcmp(argv[1], "server") == 0) {
				printf("Starting server...\n");
				TCPsocket server, client;
				IPaddress ip;
				if (SDLNet_ResolveHost(&ip, NULL, 9999) == -1) {
				printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
				exit(1);
				}
				server = SDLNet_TCP_Open(&ip);
				if (!server) {
				printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
				exit(2);
				}
				while (!done) {
				/* try to accept a connection */
				client = SDLNet_TCP_Accept(server);
				if (!client) { /* no connection accepted */
					/*printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
					SDL_Delay(100); /*sleep 1/10th of a second */
					continue;
				}

				/* get the clients IP and port number */
				IPaddress *remoteip;
				remoteip = SDLNet_TCP_GetPeerAddress(client);
				if (!remoteip) {
					printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
					continue;
				}

				/* print out the clients IP and port number */
				Uint32 ipaddr;
				ipaddr = SDL_SwapBE32(remoteip->host);
				printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
						(ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
						remoteip->port);

				while (1) {
					/* read the buffer from client */
					char message[1024];
					int len = SDLNet_TCP_Recv(client, message, 1024);
					if (!len) {
					printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
					break;
					}
					/* print out the message */
					printf("Received: %.*s\n", len, message);
					//break;
					if (message[0] == 'q') {
					printf("Disconecting on a q\n");
					break;
					}
					if (message[0] == 'Q') {
					printf("Closing server on a Q.\n");
					done = true;
					break;
					}
				}
				break;
				SDLNet_TCP_Close(client);
				}
			} else if (argc == 2 && strcmp(argv[1], "client") == 0) {
				printf("Starting client...\n");
				IPaddress ip;
				TCPsocket tcpsock;
				//192.168.1.2
				if (SDLNet_ResolveHost(&ip, "192.168.29.119", 9999) == -1) {
				printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
				exit(1);
				}

				tcpsock = SDLNet_TCP_Open(&ip);
				if (!tcpsock) {
				printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
				exit(2);
				}

				while (1) {
				printf("message: ");
				//break;
				char message[1024];
				fgets(message, 1024, stdin);
				int len = strlen(message);

				/* strip the newline */
				message[len - 1] = '\0';

				if (len) {
					int result;

					/* print out the message */
					printf("Sending: %.*s\n", len, message);

					result =
						SDLNet_TCP_Send(tcpsock, message, len); /* add 1 for the NULL */
					if (result < len)
					printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
				}

				if (len == 2 && tolower(message[0]) == 'q') {
					break;
				}
				}

				SDLNet_TCP_Close(tcpsock);
			} else {
				printf("Choose server or client\n");
			}

			//int lastTime = 0,currentTime;
			//While application is running
			
			while( !quit )
			{
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
					if(curr_state==2){dot.mBox.x=32*8;dot.mBox.y = 0;curr_state = 5;};
					udaigiri.handleEvent(&e,3);
					if(curr_state==3){dot.mBox.x=1600;dot.mBox.y = 30;curr_state=5;};
					satpura.handleEvent(&e,4);
					if(curr_state==4){dot.mBox.x=1600;dot.mBox.y = 30;curr_state=5;};
				}
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
            	SDL_RenderClear(gRenderer);
				HostelTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

				girnar.render();
				udaigiri.render();
				satpura.render();
				SDL_RenderPresent(gRenderer);

					
			}
			else if(curr_state == 5){
				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//dot.handleEvent( e );
					dot.handleEvent( e );
					if(ti == 0){curr_state=7;}
					//dot2.handleEvent( e );
					InfoButton.handleEvent(&e , 6); 
					//dot2.handleEvent( e );
					
				}
				// const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				//dot.handle(currentKeyStates);
				// dot2.handle(currentKeyStates);

				//Move the dot
				
				dot.move( tileSet2,gHigh,gMedium,gLow );
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
				SDL_Color textColor = { 0, 0, 0 };
				gTextTexture.loadFromRenderedText("Tennis",textColor,gFont,gRenderer);
				gTextTexture.render(gRenderer,1120-camera.x,480-camera.y,0,0);
				gTextTexture.loadFromRenderedText("SAC",textColor,gFont,gRenderer);
				gTextTexture.render(gRenderer,1280-camera.x,1280-camera.y,0,0);
				
				MinimapTexture.render(gRenderer,1500,0,0,0);
				dot2.renderPlayer2(camera,gTextTexture,myFont,gRenderer);


				//dot2.move(tileSet2,gHigh,gMedium,gLow);
				//dot2.setCamera( camera);
				//Clear screen
				
				//Render dot
				//dot.render( camera,gTextTexture,gFont,gRenderer);
				enemy1.render(camera,gRenderer);
				enemy2.render(camera,gRenderer);
				enemy3.render(camera,gRenderer);

				

				if (dot.myfunctions.checkCollision(dot.mBox,enemy1.mBox)) curr_state = 7;
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy1.mBox)) quit=true;
				if (dot.myfunctions.checkCollision(dot.mBox,enemy2.mBox)) quit=true;
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy2.mBox)) quit=true;
				if (dot.myfunctions.checkCollision(dot.mBox,enemy3.mBox)) quit=true;
				if (dot2.myfunctions.checkCollision(dot2.mBox,enemy3.mBox)) quit=true;

				currentTime1 = SDL_GetTicks();
				if(currentTime1 > lastTime1 + 1000) //ms to wait before change angle
				{
					if (ti>0){
						ti -= 1;
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


				// for (int k=0;k<5;k++){
				// 	if (arr1[k].GetTile()->SetPowerUp==true) arr1[k].Render(camera,powerUpTexture,gRenderer);
				// }

				for (int k=0;k<4;k++){
					if (finaltask[k].GetTile()->SetTask==true) finaltask[k].Render(camera,gRenderer);
				}
				//Update screen
				InfoButton.render();
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
				ResumeButton.render();
				SDL_RenderPresent( gRenderer );
			}
			else if (curr_state == 7)
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//dot.handleEvent( e );
					RetryButton.handleEvent(&e,0);
					ExitButton.handleEvent(&e,8);
					if(curr_state==8){quit = true;}
				}
				EndScreenTexture.render(gRenderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				RetryButton.render();
				ExitButton.render();
				SDL_RenderPresent( gRenderer );
			}



				SDL_Delay(100);
			}

			SDL_DestroyRenderer( gRenderer );
				gameStartButton.close();
				girnar.close();
				udaigiri.close();
				satpura.close();
				InfoButton.close();
				ResumeButton.close();
				RetryButton.close();
				ExitButton.close();
		}
		SDLNet_Quit();
		//Free resources and close SDL
		
		close( tileSet1,tileSet2,tileSet3,tileSet4 );
	}

	return 0;
}