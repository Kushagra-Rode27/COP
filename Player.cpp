#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "Player.h"
#include "texture.h"
#include "auxFunctions.h"


bool Dot :: touchesWall( SDL_Rect box, Tile* tiles[] )
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

void Dot::move( Tile *tiles[] )
{

	for (int k=0;k<TOTAL_TILES;k++){
		if (tiles[k]->SetPoint){
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox)){
				score+=1;
				Mix_PlayChannel( -1, gLow, 0 );
				tiles[k]->SetPoint=NULL;
			}
		}
		if (tiles[k]->SetPowerUp){
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox)){
				score+=5;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles[k]->SetPowerUp=NULL;
			}
		}

		if (tiles[k]->SetTask){
			if (myfunctions.checkCollision(tiles[k]->getBox(),mBox)){
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

void Dot::render( SDL_Rect& camera )
{
    //Show the dot
	gDotTexture.render( gRenderer, mBox.x - camera.x, mBox.y - camera.y );
	score_text="score: "+std::to_string(score);
	SDL_Color textColor = { 0, 0, 0 };
	gTextTexture.loadFromRenderedText(score_text,textColor,gFont,gRenderer);
	gTextTexture.render(gRenderer, mBox.x - camera.x -40, mBox.y - camera.y -60);     
	// SDL_Color textColor = { 255, 255, 255, 0 };
	// SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
	// LTexture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	// int text_width = textSurface->w;
	// int text_height = textSurface->h;
	// SDL_FreeSurface(textSurface);
	// SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
	// SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	// SDL_DestroyTexture(text);
	gTextTexture.loadFromRenderedText("Tasks Completed P1:" + std::to_string(tasksComp),textColor,gFont,gRenderer);
	gTextTexture.render(gRenderer,0,40);

	gTextTexture.loadFromRenderedText("Cricket ground",textColor,gFont,gRenderer);
	gTextTexture.render(gRenderer,1120-camera.x,500-camera.y);

	//std::cout<<mBox.x- camera.x<<" "<<mBox.y-camera.y<<"\n";
}