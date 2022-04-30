#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "texture.h"
#include "tile.h"
#include "point.h"

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

void Point::Render(SDL_Rect& camera,SDL_Renderer* gRenderer, LTexture pointTexture)
{
	pointTexture.render(gRenderer,position.x- camera.x, position.y- camera.y,0,0);
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