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
SDL_Renderer* rend;
SDL_Renderer* rende;
SDL_Texture* tex;
//Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;

// const int SCREEN_WIDTH = 3200;
// const int SCREEN_HEIGHT = 1600;

//The dimensions of the level
const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 1600;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 50*100;
const int TOTAL_TILE_SPRITES = 100;

//The different tile sprites
const int TILE_NONE = 0;
const int TILE_GREEN = 1;
const int TILE_ROAD = 13;
const int TILE_HOSTEL = 46;
const int TILE_STORE = 65;
const int TILE_ANOTHER = 74;
const int TILE_SOME=43;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
// till here in texture.h


// from here in tile.h slight change in render function
//The tile
class Tile
{
    public:
		//Initializes position and type
		Tile( int x, int y, int tileType );

		//Shows the tile
		void render( SDL_Rect& camera );

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();

		bool SetPoint=false;
		bool SetPowerUp=false;
		bool SetTask = false;
    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};
// in Player1.h
//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		int DOT_VEL = 16;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		void handle(const Uint8* currentKeyStates);

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera );

		int score=0;
		int tasksComp = 0;
		//Collision box of the dot
		SDL_Rect mBox;

    private:

		//The velocity of the dot
		int mVelX, mVelY;
};
// till here
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
		void render(SDL_Rect& camera);

		//Collision box of the dot
		SDL_Rect mBox;

    private:
		

		//The velocity of the dot
		int mVelX;
		int mVelY=16;
};

class Point 
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 3;
	static const int Height = 3;

	static const int Margin = 11;

	// Point();
	Point();
	Point(Tile* tile);
	~Point();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Renders pacman
	void Render(SDL_Rect& camera);

	// Releases texture memory
	// void Free();

	// Mark the object to be deleted
	void Delete();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

private:

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};


class Powerup 
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 3;
	static const int Height = 3;

	static const int Margin = 11;

	// Point();
	Powerup();
	Powerup(Tile* tile);
	~Powerup();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Renders pacman
	void Render(SDL_Rect& camera);

	// Releases texture memory
	// void Free();

	// Mark the object to be deleted
	void Delete();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

private:

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

class Tasks 
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 3;
	static const int Height = 3;

	static const int Margin = 11;

	// Point();
	Tasks();
	Tasks(Tile* tile);
	~Tasks();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Renders pacman
	void Render(SDL_Rect& camera);

	// Releases texture memory
	// void Free();

	// Mark the object to be deleted
	void Delete();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

private:

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};




//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture gTextTexture;

LTexture pointTexture;
LTexture powerUpTexture;
LTexture tasksTexture;
LTexture gDotTexture;
LTexture genemyDotTexture;
LTexture gDot2Texture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

std::string score_text;
std::string score_text2;


//from here texture.cpp
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
// LTexture in texture.cpp some change has been done in function definition of loadfromfile. grenderer has been passed as parameter



Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
// in tile.cpp with some modifications




// in Player.cpp
Dot::Dot()
{
    //Initialize the collision box
    mBox.x = 8*32;
    mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

enemyDot::enemyDot(int pos)
{
    //Initialize the collision box
    mBox.x = pos*32;
    mBox.y = 32;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 16;
}

Dot2::Dot2()
{
    //Initialize the collision box
    mBox2.x = 8*32;
    mBox2.y = 0;
	mBox2.w = DOT2_WIDTH;
	mBox2.h = DOT2_HEIGHT;

    //Initialize the velocity
    mVelX2 = 0;
    mVelY2 = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY =- DOT_VEL; break;
            case SDLK_DOWN: mVelY =+ DOT_VEL; break;
            case SDLK_LEFT: mVelX =- DOT_VEL; break;
            case SDLK_RIGHT: mVelX =+ DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY = 0; break;
            case SDLK_DOWN: mVelY = 0; break;
            case SDLK_LEFT: mVelX = 0; break;
            case SDLK_RIGHT: mVelX = 0; break;
        }
    }
	// if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    // {
    //     //Adjust the velocity
    //     switch( e.key.keysym.sym )
    //     {
    //         case SDLK_UP: mVelY -= DOT_VEL; break;
    //         case SDLK_DOWN: mVelY += DOT_VEL; break;
    //         case SDLK_LEFT: mVelX -= DOT_VEL; break;
    //         case SDLK_RIGHT: mVelX += DOT_VEL; break;
    //     }
    // }
    // //If a key was released
    // else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    // {
    //     //Adjust the velocity
    //     switch( e.key.keysym.sym )
    //     {
    //         case SDLK_UP: mVelY += DOT_VEL; break;
    //         case SDLK_DOWN: mVelY -= DOT_VEL; break;
    //         case SDLK_LEFT: mVelX += DOT_VEL; break;
    //         case SDLK_RIGHT: mVelX -= DOT_VEL; break;
    //     }
    // }
}

void Dot::handle(const Uint8* currentKeyStates)
{
	if( currentKeyStates[ SDL_SCANCODE_W ] )
	{
		mVelY=-DOT_VEL;
	}
	else
	{
		mVelY=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_S ] )
	{
		mVelY=DOT_VEL;
	}
	else
	{
		mVelY=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_A ] )
	{
		mVelX=-DOT_VEL;
	}
	else
	{
		mVelX=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_D ] )
	{
		mVelX=DOT_VEL;
	}
	else
	{
		mVelX=0;
	}

    //If a key was pressed
	// if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    // {
    //     //Adjust the velocity
    //     switch( e.key.keysym.sym )
    //     {
    //         case SDLK_UP: mVelY -= DOT_VEL; break;
    //         case SDLK_DOWN: mVelY += DOT_VEL; break;
    //         case SDLK_LEFT: mVelX -= DOT_VEL; break;
    //         case SDLK_RIGHT: mVelX += DOT_VEL; break;
    //     }
    // }
    // //If a key was released
    // else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    // {
    //     //Adjust the velocity
    //     switch( e.key.keysym.sym )
    //     {
    //         case SDLK_UP: mVelY += DOT_VEL; break;
    //         case SDLK_DOWN: mVelY -= DOT_VEL; break;
    //         case SDLK_LEFT: mVelX += DOT_VEL; break;
    //         case SDLK_RIGHT: mVelX -= DOT_VEL; break;
    //     }
    // }
}

void Dot2::handleEvent2( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY2 =- DOT2_VEL; break;
            case SDLK_s: mVelY2 =+ DOT2_VEL; break;
            case SDLK_a: mVelX2 =- DOT2_VEL; break;
            case SDLK_d: mVelX2 =+ DOT2_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY2 = 0; break;
            case SDLK_s: mVelY2 = 0; break;
            case SDLK_a: mVelX2 = 0; break;
            case SDLK_d: mVelX2 = 0; break;
        }
    }
}

void Dot2::handle(const Uint8* currentKeyStates){
	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{
		mVelY2=-DOT2_VEL;
	}
	else
	{
		mVelY2=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{
		mVelY2=DOT2_VEL;
	}
	else
	{
		mVelY2=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		mVelX2=-DOT2_VEL;
	}
	else
	{
		mVelX2=0;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		mVelX2=DOT2_VEL;
	}
	else
	{
		mVelX2=0;
	}
}

void Dot::move( Tile *tiles[] )
{

	for (int k=0;k<TOTAL_TILES;k++){
		if (tiles[k]->SetPoint){
			if (checkCollision(tiles[k]->getBox(),mBox)){
				score+=1;
				Mix_PlayChannel( -1, gLow, 0 );
				tiles[k]->SetPoint=NULL;
			}
		}
		if (tiles[k]->SetPowerUp){
			if (checkCollision(tiles[k]->getBox(),mBox)){
				score+=5;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetPowerUp=NULL;
			}
		}

		if (tiles[k]->SetTask){
			if (checkCollision(tiles[k]->getBox(),mBox)){
				tasksComp+=1;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetTask=NULL;
				speed1=true;
			}
		}
	}

    //Move the dot left or right
    mBox.x += mVelX;

	if (speed1) {
		DOT_VEL=20;
	}else{
		DOT_VEL=16;
	}

    //If the dot went too far to the left or right or touched a wall || touchesWall( mBox, tiles ) 
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH )  || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT )  || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
    }
}

void enemyDot::move( Tile *tiles[] )
{

    //Move the dot up or down

    mBox.y += mVelY;
	
    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || mBox.y > 1600 )
    {
        //move back
        mVelY = -mVelY;
    }
}

void Dot2::move2( Tile *tiles[] )
{
    //Move the dot left or right
	mBox2.x += mVelX2;

	if (speed2) {
		DOT2_VEL=20;
	}else{
		DOT2_VEL=16;
	}

	for (int k=0;k<TOTAL_TILES;k++){
		if (tiles[k]->SetPoint){
			if (checkCollision(tiles[k]->getBox(),mBox2)){
				score+=1;
				Mix_PlayChannel( -1, gLow, 0 );
				tiles[k]->SetPoint=NULL;
			}
		}
		if (tiles[k]->SetPowerUp){
			if (checkCollision(tiles[k]->getBox(),mBox2)){
				score+=5;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetPowerUp=NULL;
			}
		}
		if (tiles[k]->SetTask){
			if (checkCollision(tiles[k]->getBox(),mBox2)){
				tasksComp+=1;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetTask=NULL;
				speed2=true;
			}
		}
	}

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox2.x < 0 ) || ( mBox2.x + DOT2_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox2, tiles ))
    {
        //move back
        mBox2.x -= mVelX2;
    }

    //Move the dot up or down
    mBox2.y += mVelY2;

    //If the dot went too far up or down or touched a wall
    if( ( mBox2.y < 0 ) || ( mBox2.y + DOT2_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox2, tiles ))
    {
        //move back
        mBox2.y -= mVelY2;
    }
}


void Dot::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Dot2::setCamera2( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox2.x + DOT2_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox2.y + DOT2_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Dot::render( SDL_Rect& camera )
{
    //Show the dot
	gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
	scorep1=score;
	score_text="score: "+std::to_string(scorep1);
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(score_text,textColor);
	gTextTexture.render( mBox.x - camera.x -40, mBox.y - camera.y -60);     
	// SDL_Color textColor = { 255, 255, 255, 0 };
	// SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
	// LTexture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	// int text_width = textSurface->w;
	// int text_height = textSurface->h;
	// SDL_FreeSurface(textSurface);
	// SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
	// SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	// SDL_DestroyTexture(text);
	gTextTexture.loadFromRenderedText("Tasks Completed P1:" + std::to_string(tasksComp),textColor);
	gTextTexture.render(0,40);

	gTextTexture.loadFromRenderedText("Cricket ground",textColor);
	gTextTexture.render(1120-camera.x,500-camera.y);

	//std::cout<<mBox.x- camera.x<<" "<<mBox.y-camera.y<<"\n";
}

void enemyDot::render(SDL_Rect& camera){
	genemyDotTexture.render( mBox.x-camera.x, mBox.y -camera.y);
}

void Dot2::render2( SDL_Rect& camera )
{
    //Show the dot
	gDot2Texture.render( mBox2.x - camera.x, mBox2.y - camera.y );
	scorep2=score;
	score_text2="score: "+std::to_string(scorep2);
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(score_text2,textColor);
	gTextTexture.render( mBox2.x - camera.x -40, mBox2.y - camera.y -60);


	gTextTexture.loadFromRenderedText("Tasks Completed P2:" + std::to_string(tasksComp),textColor);
	gTextTexture.render(SCREEN_WIDTH-300,40);
}
int ti = 180;
int lastTime1 = 0,currentTime1;
void timerRender(){
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(std::to_string(ti) + " seconds",textColor);
	gTextTexture.render( 0, 0);
}


// in point.cpp
Point::Point(){
}

Point::Point(Tile* tile)
{
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetPoint=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;
	} else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	collider.x = position.x;
	collider.y = position.y;
}

Point::~Point()
{
}

void Point::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPoint=NULL;

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetPoint=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;

		collider.x = position.x;
		collider.y = position.y;
	}
}

void Point::Render(SDL_Rect& camera)
{
	pointTexture.render(position.x- camera.x, position.y- camera.y);
}

void Point::Delete()
{
	// Calling the base function
	//GameObject::Delete();

	currTile->SetPoint=NULL;
}

SDL_Rect Point::GetCollider()
{
	return collider;
}

SDL_Point Point::GetPosition()
{
	return position;
}

Tile* Point::GetTile()
{
	return currTile;
}

// Powerup in powerup.cpp
Powerup::Powerup(){
}

Powerup::Powerup(Tile* tile)
{
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetPowerUp=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;
	} else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	collider.x = position.x;
	collider.y = position.y;
}

Powerup::~Powerup()
{
}

void Powerup::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPowerUp=NULL;

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetPowerUp=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;

		collider.x = position.x;
		collider.y = position.y;
	}
}

void Powerup::Render(SDL_Rect& camera)
{
	powerUpTexture.render(position.x- camera.x, position.y- camera.y);
}

void Powerup::Delete()
{
	// Calling the base function
	//GameObject::Delete();

	currTile->SetPowerUp=NULL;
}

SDL_Rect Powerup::GetCollider()
{
	return collider;
}

SDL_Point Powerup::GetPosition()
{
	return position;
}

Tile* Powerup::GetTile()
{
	return currTile;
}



// Tasks
Tasks::Tasks(){
}

Tasks::Tasks(Tile* tile)
{
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetTask=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;
	} else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	collider.x = position.x;
	collider.y = position.y;
}

Tasks::~Tasks()
{
}

void Tasks::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetTask=NULL;

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetTask=true;

		position.x = currTile->getBox().x ;
		position.y = currTile->getBox().y ;

		collider.x = position.x;
		collider.y = position.y;
	}
}

void Tasks::Render(SDL_Rect& camera)
{
	tasksTexture.render(position.x- camera.x, position.y- camera.y);
}

void Tasks::Delete()
{
	// Calling the base function
	//GameObject::Delete();

	currTile->SetTask=NULL;
}

SDL_Rect Tasks::GetCollider()
{
	return collider;
}

SDL_Point Tasks::GetPosition()
{
	return position;
}

Tile* Tasks::GetTile()
{
	return currTile;
}


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
			Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
			rend = SDL_CreateRenderer(gWindow, -1, render_flags);
			if (!rend)
			{
			printf("error creating renderer: %s\n", SDL_GetError());
			SDL_DestroyWindow(gWindow);
			SDL_Quit();
			return 1;
			}

			// load the image into memory using SDL_image library function
			SDL_Surface* surface = IMG_Load("assets/start.png");
			if (!surface)
			{
				printf("error creating surface\n");
				SDL_DestroyRenderer(rend);
				SDL_DestroyWindow(gWindow);
				SDL_Quit();
				return 1;
			}

			// load the image data into the graphics hardware's memory
			tex = SDL_CreateTextureFromSurface(rend, surface);
			SDL_FreeSurface(surface);
			if (!tex)
			{
				printf("error creating texture: %s\n", SDL_GetError());
				SDL_DestroyRenderer(rend);
				SDL_DestroyWindow(gWindow);
				SDL_Quit();
				return 1;
			}

			// clear the window
			SDL_RenderClear(rend);
			
			// draw the image to the window
			SDL_RenderCopy(rend, tex, NULL, NULL);
			SDL_RenderPresent(rend);

			// wait a few seconds
			SDL_Event initial;
			bool startscreen=true;
			int iter=0;
			while(startscreen){
				while( SDL_PollEvent( &initial ) != 0 )
				{
					//Handle key press
                    if( initial.type == SDL_KEYDOWN)
                    {
                        if (initial.key.keysym.sym==SDLK_1){
							startscreen=false;
						}
                    }
				}
				iter+=1;
				if (iter==50) startscreen=false;
				SDL_Delay(100);
			}

			// clean up resources before exiting
			SDL_DestroyTexture(tex);
			SDL_DestroyRenderer(rend);

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

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "assets/character1.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !genemyDotTexture.loadFromFile( "assets/dog3.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gDot2Texture.loadFromFile( "assets/character2.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !pointTexture.loadFromFile( "assets/point.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !powerUpTexture.loadFromFile( "assets/powerup.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !tasksTexture.loadFromFile( "assets/task.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "assets/tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
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
        if( !gTextTexture.loadFromRenderedText( score_text, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
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
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	//Free loaded images
	gDotTexture.free();
	genemyDotTexture.free();
	gDot2Texture.free();
	gTileTexture.free();
	pointTexture.free();
	//Free loaded images
    gTextTexture.free();
	powerUpTexture.free();
	tasksTexture.free();
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

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
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
// till here

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "./lazy.map" );

    //If the map couldn't be loaded
    if( map.fail() )
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
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number && ( tileType < TOTAL_TILE_SPRITES )
			if( ( tileType >= 0 ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
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
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_NONE ].x = 0;
			gTileClips[ TILE_NONE ].y = 0;
			gTileClips[ TILE_NONE ].w = TILE_WIDTH;
			gTileClips[ TILE_NONE ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 32;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_ROAD ].x = 0;
			gTileClips[ TILE_ROAD ].y = 64;
			gTileClips[ TILE_ROAD ].w = TILE_WIDTH;
			gTileClips[ TILE_ROAD ].h = TILE_HEIGHT;

			gTileClips[ TILE_STORE ].x = 32;
			gTileClips[ TILE_STORE ].y = 0;
			gTileClips[ TILE_STORE ].w = TILE_WIDTH;
			gTileClips[ TILE_STORE ].h = TILE_HEIGHT;

			gTileClips[ TILE_ANOTHER ].x = 64;
			gTileClips[ TILE_ANOTHER ].y = 0;
			gTileClips[ TILE_ANOTHER ].w = TILE_WIDTH;
			gTileClips[ TILE_ANOTHER ].h = TILE_HEIGHT;

			gTileClips[ TILE_SOME ].x = 64;
			gTileClips[ TILE_SOME ].y = 32;
			gTileClips[ TILE_SOME ].w = TILE_WIDTH;
			gTileClips[ TILE_SOME ].h = TILE_HEIGHT;

			gTileClips[ TILE_HOSTEL ].x = 160;
			gTileClips[ TILE_HOSTEL ].y = 160;
			gTileClips[ TILE_HOSTEL ].w = TILE_WIDTH;
			gTileClips[ TILE_HOSTEL ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
		//( tiles[ i ]->getType() >= TILE_ROAD ) && ( tiles[ i ]->getType() <= TILE_STORE )
        if( tiles[ i ]->getType() <= TILE_NONE)
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Point TilePLace(Tile* tiles[]){
	srand(time(0));
	for ( int i = 0; i < TOTAL_TILES; 	i++ ){
		int j=rand()%5000;
		if (tiles[j]->getType() == TILE_ROAD && !tiles[j]->SetPoint){
			
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
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet ) )
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
			Dot dot;
			Dot2 dot2;

			enemyDot enemy1(8);
			enemyDot enemy2(42);
			enemyDot enemy3(81);

			Point arr[10];
			for ( int k=0;k<10;k++){
				arr[k]=TilePLace(tileSet);
			}
			// Point p1=TilePLace(tileSet);
			// Point p2=TilePLace(tileSet);
			Powerup p1(tileSet[100*4 + 5]);
			Powerup p2(tileSet[100*5 + 14]);
			Powerup p3(tileSet[100*10 + 5]);
			Powerup p4(tileSet[100*17 + 5]);
			Powerup p5(tileSet[100*8 + 24]);
			Powerup p6(tileSet[100*20 + 22]);

			Powerup arr1[6] = {p1,p2,p3,p4,p5,p6};


			Tasks t1(tileSet[100*24 + 38]);
			Tasks t2(tileSet[100*22 + 47]);
			Tasks t3(tileSet[100*23 + 64]);
			Tasks t4(tileSet[100*6 + 5]);
			Tasks t5(tileSet[100*16 + 49]);
			Tasks t6(tileSet[100*12 + 57]);
			Tasks t7(tileSet[100*5 + 51]);
			Tasks t8(tileSet[100*18 + 5]);
			Tasks t9(tileSet[100*27 + 6]);


			// int location[9] = {100*24 + 38,100*22 + 47,100*23 + 64,100*4 + 8,100*16 + 49};
			Tasks task[9] = {t1,t2,t3,t4,t5,t6,t7,t8,t9};

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

			int lastTime = 0,currentTime;
			//While application is running
			while( !quit )
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
					dot.handleEvent( e );
					dot2.handleEvent2( e );
				}
				// const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				// dot.handle(currentKeyStates);
				// dot2.handle(currentKeyStates);

				//Move the dot
				dot.move( tileSet );
				dot.setCamera( camera );

				enemy1.move(tileSet);
				enemy2.move(tileSet);
				enemy3.move(tileSet);
				
				dot2.move2(tileSet);
				dot2.setCamera2( camera);
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				//Render dot
				dot.render( camera );
				enemy1.render(camera);
				enemy2.render(camera);
				enemy3.render(camera);
				dot2.render2(camera);

				if (checkCollision(dot.mBox,enemy1.mBox)) quit=true;
				if (checkCollision(dot2.mBox2,enemy1.mBox)) quit=true;
				if (checkCollision(dot.mBox,enemy2.mBox)) quit=true;
				if (checkCollision(dot2.mBox2,enemy2.mBox)) quit=true;
				if (checkCollision(dot.mBox,enemy3.mBox)) quit=true;
				if (checkCollision(dot2.mBox2,enemy3.mBox)) quit=true;

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
				currentTime = SDL_GetTicks();
				if(currentTime > lastTime + 20000) //ms to wait before change angle
				{
					for (int k=0;k<5;k++){
						arr1[k].GetTile()->SetPowerUp =true; 
					}
					speed1=false;
					speed2=false;
					lastTime = currentTime;
				}
				// p1.Render(camera);
				// p2.Render(camera);
				// p3.Render(camera);
				// p4.Render(camera);
				// p5.Render(camera);
				// p6.Render(camera);
				
				

				for (int k=0;k<10;k++){
					if (arr[k].GetTile()->SetPoint==true) arr[k].Render(camera);
				}

				for (int k=0;k<5;k++){
					if (arr1[k].GetTile()->SetPowerUp==true) arr1[k].Render(camera);
				}

				for (int k=0;k<4;k++){
					if (finaltask[k].GetTile()->SetTask==true) finaltask[k].Render(camera);
				}
				//Update screen
				SDL_RenderPresent( gRenderer );

				SDL_Delay(100);
			}

			SDL_DestroyRenderer( gRenderer );
			
			Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
			rende = SDL_CreateRenderer(gWindow, -1, render_flags);
			if (!rende)
			{
			printf("error creating renderer: %s\n", SDL_GetError());
			SDL_DestroyWindow(gWindow);
			SDL_Quit();
			return 1;
			}

			// load the image into memory using SDL_image library function
			SDL_Surface* surface = IMG_Load("assets/gamend.jpg");
			if (!surface)
			{
				printf("error creating surface\n");
				SDL_DestroyRenderer(rende);
				SDL_DestroyWindow(gWindow);
				SDL_Quit();
				return 1;
			}

			// load the image data into the graphics hardware's memory
			tex = SDL_CreateTextureFromSurface(rende, surface);
			SDL_FreeSurface(surface);
			if (!tex)
			{
				printf("error creating texture: %s\n", SDL_GetError());
				SDL_DestroyRenderer(rende);
				SDL_DestroyWindow(gWindow);
				SDL_Quit();
				return 1;
			}

			// clear the window
			SDL_RenderClear(rende);
			
			// draw the image to the window
			SDL_RenderCopy(rende, tex, NULL, NULL);
			SDL_RenderPresent(rende);

			// wait a few seconds
			SDL_Event initial;
			bool startscreen=true;
			int iter=0;
			while(startscreen){
				while( SDL_PollEvent( &initial ) != 0 )
				{
					//Handle key press
                    if( initial.type == SDL_KEYDOWN)
                    {
                        if (initial.key.keysym.sym==SDLK_1){
							startscreen=false;
						}
                    }
				}
				iter+=1;
				if (iter==50) startscreen=false;
				SDL_Delay(100);
			}

			// clean up resources before exiting
			SDL_DestroyTexture(tex);
			SDL_DestroyRenderer(rende);
		
		}
		SDLNet_Quit();
		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}