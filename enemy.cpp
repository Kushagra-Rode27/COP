#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "enemy.h"
#include "texture.h"



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

void enemyDot::render(SDL_Rect& camera){
	genemyDotTexture.render( gRenderer,mBox.x-camera.x, mBox.y -camera.y);
}