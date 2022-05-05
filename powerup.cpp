#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "texture.h"
#include "tile.h"
#include "powerup.h"


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

void Powerup::Render(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
	powerUpTexture.loadFromFile("assets/powerup.png",gRenderer);
	powerUpTexture.render(gRenderer,position.x- camera.x, position.y- camera.y,0,0);
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