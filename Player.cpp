#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "Player.h"
#include "texture.h"
#include "auxFunctions.h"


bool Dot :: touchesWall( SDL_Rect box, Tile* tiles1[] , Tile* tiles2[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
		//( tiles[ i ]->getType() >= TILE_ROAD ) && ( tiles[ i ]->getType() <= TILE_STORE )
        if( tiles1[ i ]->getType() == 0 && tiles2[i]->getType() == 0)
        {
            //If the collision box touches the wall tile
            if( myfunctions.checkCollision( box, tiles1[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}


Dot::Dot(int XCycle,int YCycle,int PlayerSpriteWidth , int PlayerSpriteHeight , int PlayerRenderHeight , int PlayerRenderWidth , int bestState)
{
    //Initialize the collision box
    mBox.x = 8*32;
    mBox.y = 0;
	mBox.w = PlayerRenderWidth;
	mBox.h = PlayerRenderHeight;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize other Params for spritesheet
    Xcycle = XCycle;
    Ycycle = YCycle;
    Spritewidth = PlayerSpriteWidth;
    Spriteheight = PlayerSpriteHeight;
    Renderheight = PlayerRenderHeight;
    Renderwidth = PlayerRenderWidth;
    


}

//Dot :: Dot(LTexture gDotTexture,LTexture gTextTexture,TTF_Font *gFont,SDL_Renderer* gRenderer,Mix_Chunk *gHigh,Mix_Chunk *gMedium,Mix_Chunk *gLow){
    //Initialize the collision box
//     mBox.x = 8*32;
//     mBox.y = 0;
// 	mBox.w = DOT_WIDTH;
// 	mBox.h = DOT_HEIGHT;

//     //Initialize the velocity
//     mVelX = 0;
//     mVelY = 0;
    
//     gDotTexture = gDotTexture;
//     gTextTexture = gTextTexture;
//     gFont = gFont;
//     gRenderer = gRenderer;
//     gHigh = gHigh;
//     gMedium = gMedium;
//     gLow = gLow;

// }

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN)
    {

        switch(e.key.keysym.sym)
        {   
            case SDLK_DOWN : if(myState.first == 0) myState.second+=1 ;else myState={0,stayState};break;

            case SDLK_LEFT : if(myState.first == 1) myState.second+=1;else myState={1,stayState};break;

            case SDLK_RIGHT : if(myState.first == 0) myState.second+=1;else myState={0,stayState};break;
            
            case SDLK_UP : if(myState.first ==1) myState.second+=1;else myState={1,stayState};break;

            
        }
        if (myState.second <0 ) myState.second+=Xcycle;
        if(myState.second>=Xcycle) myState.second-=Xcycle;

        // VELOCITY ADJUSTED
        if(e.key.repeat==0)
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_UP: mVelY -= DOT_VEL; break;
                case SDLK_DOWN: mVelY += DOT_VEL; break;
                case SDLK_LEFT: mVelX -= DOT_VEL; break;
                case SDLK_RIGHT: mVelX += DOT_VEL; break;
            }
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

void Dot::move( Tile *tiles1[],Tile *tiles2[],Mix_Chunk *gHigh,Mix_Chunk *gMedium,Mix_Chunk *gLow )
{

	for (int k=0;k<TOTAL_TILES;k++){
		if (tiles1[k]->SetPoint){
			if (myfunctions.checkCollision(tiles1[k]->getBox(),mBox)){
				money+=5;
				Mix_PlayChannel( -1, gLow, 0 );
				tiles1[k]->SetPoint=NULL;
			}
		}
		if (tiles2[k]->SetPowerUp){
			if (myfunctions.checkCollision(tiles2[k]->getBox(),mBox) && !isPowerUpEnabled){
				isPowerUpEnabled = true;
				Mix_PlayChannel( -1, gMedium, 0 );
				tiles2[k]->SetPowerUp=NULL;
			}
		}

		if (tiles2[k]->SetTask){
			if (myfunctions.checkCollision(tiles2[k]->getBox(),mBox)){

                if((tiles2[k]->Tasktype) == 0){
                    if(health < 98){
                        health+=3;
                    }
                    else {
                        health = 100;
                    }
                    tasksComp+=1;
                    Mix_PlayChannel( -1, gMedium, 0 );
				    tiles2[k]->SetTask=NULL;
                    waitime=3;
                }
                else if((tiles2[k]->Tasktype) == 1){
                    money += CG*2;
                    tasksComp+=1;
                    Mix_PlayChannel( -1, gMedium, 0 );
				    tiles2[k]->SetTask=NULL;
                    waitime=7;
                }
                else if((tiles2[k]->Tasktype) == 2){
                    if(CG <= 9.75){
                        CG+= 0.25;
                    }
                    else {
                        CG = 10;
                    }
                    
                    tasksComp+=1;
                    Mix_PlayChannel( -1, gMedium, 0 );
				    tiles2[k]->SetTask=NULL;
                    waitime = 4;
                }
                else if((tiles2[k]->Tasktype)== 3){
                    if(health < 98){
                        health+=3;
                    }
                    else {
                        health = 100;
                    }
                    tasksComp+=1;
                    Mix_PlayChannel( -1, gMedium, 0 );
				    tiles2[k]->SetTask=NULL;
                    waitime = 5;
                }
                else if ((tiles2[k]->Tasktype) == 4) {
                    if(health < 98){
                        health+=3;
                    }
                    else {
                        health = 100;
                    }
                    tasksComp+=1;
                    Mix_PlayChannel( -1, gMedium, 0 );
				    tiles2[k]->SetTask=NULL;
                    waitime = 4;
                }
                else if((tiles2[k]->Tasktype) == 5){
                    if(money >= 16){
                        health = 100;
                        money -= 10;
                        waitime = 20;
                        tasksComp+=1;
                        Mix_PlayChannel( -1, gMedium, 0 );
                        tiles2[k]->SetTask=NULL;
                    }
                    
                }
				
				
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
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH )  || touchesWall( mBox, tiles1 ,tiles2)   )
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT )  || touchesWall( mBox, tiles1 ,tiles2)   )
    {
        //move back
        mBox.y -= mVelY;
    }
}

void Dot::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + Renderwidth / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + Renderheight / 2 ) - SCREEN_HEIGHT / 2;

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

string Dot ::double2String(double a){
    string b =  std::to_string(a);
    return b.substr(0,b.find(".") + 3);
}

void Dot::render( SDL_Rect& camera,LTexture TextTexture,TTF_Font *gFont ,SDL_Renderer* gRenderer )
{
    SDL_Rect myClip ={ Spritewidth*myState.second , Spriteheight*myState.first, Spritewidth,Spriteheight};
    //Show the dot
	gDotTexture.render( gRenderer, mBox.x - camera.x, mBox.y - camera.y,Renderwidth,Renderheight,&myClip );
	score_text="Money: "+std :: to_string((int)money);
	SDL_Color textColor = { 255, 255, 255 };
    
	TextTexture.loadFromRenderedText( score_text,textColor,gFont,gRenderer);
	TextTexture.render(gRenderer, mBox.x - camera.x -40, mBox.y - camera.y -60,0,0);     
	// SDL_Color textColor = { 255, 255, 255, 0 };
	// SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
	// LTexture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	// int text_width = textSurface->w;
	// int text_height = textSurface->h;
	// SDL_FreeSurface(textSurface);
	// SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
	// SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	// SDL_DestroyTexture(text);

    
	TextTexture.loadFromRenderedText("Tasks Completed P1 :" + std::to_string(tasksComp),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,65,70,0,0);
    
    TextTexture.loadFromRenderedText("CG P1 : " + double2String(CG),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,65,110,0,0);

    TextTexture.loadFromRenderedText("HEALTH P1 : " + double2String(health),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,65,150,0,0);
}

void Dot :: renderPlayer2( SDL_Rect &camera,LTexture TextTexture,TTF_Font *gFont, SDL_Renderer* gRenderer )
{
    SDL_Rect myClip ={ Spritewidth*myState.second , Spriteheight*myState.first, Spritewidth,Spriteheight};
    //Show the dot
	gDotTexture.render( gRenderer, mBox.x - camera.x, mBox.y - camera.y,Renderwidth,Renderheight,&myClip );
	score_text="Money: "+std :: to_string((int)money);
	SDL_Color textColor = { 255, 255, 255 };
    
	TextTexture.loadFromRenderedText( score_text,textColor,gFont,gRenderer);
	TextTexture.render(gRenderer, mBox.x - camera.x -40, mBox.y - camera.y -60,0,0);


    TextTexture.loadFromRenderedText("Tasks Completed P2 :" + std::to_string(tasksComp),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,SCREEN_WIDTH - 65,70,0,0);
    
    TextTexture.loadFromRenderedText("CG P2 : " + double2String(CG),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,SCREEN_WIDTH - 65,110,0,0);

    TextTexture.loadFromRenderedText("HEALTH P2 : " + double2String(health),textColor,gFont,gRenderer);
    TextTexture.render(gRenderer,SCREEN_WIDTH - 65,150,0,0);

    
   
}


void Dot::displayMyText( std::string sentence,  int sentenceX, int sentenceY,TTF_Font *gFont,SDL_Renderer* gRenderer)
{
    LTexture myTexture;
    SDL_Color textColor = {0, 0, 0};
    if (!myTexture.loadFromRenderedText(sentence, textColor, gFont, gRenderer))
    {
        printf("Error in loading texture for string ");
    }

    

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    // myTexture.render(gRenderer,WindowWidth/3 , WindowHeight*9/10, WindowWidth/3 , WindowHeight/11 );

    // myTexture.render(gRenderer, (int)(((double)(*SCREEN_WIDTH)) * sentenceX), (int)(((double)(*SCREEN_HEIGHT)) * sentenceY));
    

     myTexture.render(gRenderer, sentenceX,sentenceY);

    myTexture.free();
}


void Dot::NetworkUpdate(int myStateFirst, int myStateSecond, int myXcoord , int myYcoord ,int Health , int CG, int Money){
    myState.first=myStateFirst;
    myState.second = myStateSecond;
    mBox.x = myXcoord ; 
    mBox.y = myYcoord ; 
    health =Health;
    CG =CG;
    money = Money;
}