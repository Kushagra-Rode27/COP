#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "Player2.h"
#include "texture.h"
#include "auxFunctions.h"

bool Dot2 :: touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
		//( tiles[ i ]->getType() >= TILE_ROAD ) && ( tiles[ i ]->getType() <= TILE_STORE )
        if( tiles[ i ]->getType() <= TILE_NONE)
        {
            //If the collision box touches the wall tile
            if( myfunctions.checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
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
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox2)){
				score+=1;
				Mix_PlayChannel( -1, gLow, 0 );
				tiles[k]->SetPoint=NULL;
			}
		}
		if (tiles[k]->SetPowerUp){
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox2)){
				score+=5;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetPowerUp=NULL;
			}
		}
		if (tiles[k]->SetTask){
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox2)){
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



void Dot2::render2( SDL_Rect& camera )
{
    //Show the dot
	gDot2Texture.render(gRenderer, mBox2.x - camera.x, mBox2.y - camera.y );
	
	score_text2="score: "+std::to_string(score);
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(score_text2,textColor,gFont,gRenderer);
	gTextTexture.render(gRenderer, mBox2.x - camera.x -40, mBox2.y - camera.y -60);


	gTextTexture.loadFromRenderedText("Tasks Completed P2:" + std::to_string(tasksComp),textColor,gFont,gRenderer);
	gTextTexture.render(gRenderer,SCREEN_WIDTH-300,40);
}