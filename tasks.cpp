#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "texture.h"
#include "tile.h"
#include "tasks.h"

Tasks::Tasks(){
}

Tasks::Tasks(Tile* tile,string message,int taskType)
{
	msg = message;
	type = taskType;
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetTask=true;
		currTile->Tasktype = taskType;

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

void Tasks::Render(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
	if (type== 1){
		tasksTexture.loadFromFile("assets/money1.png",gRenderer);
	}
	else if(type == 2){
		tasksTexture.loadFromFile("assets/CG1.png",gRenderer);
	}
	else if(type == 4){
		tasksTexture.loadFromFile("assets/powerup.png",gRenderer);
	}
	else if(type == 5){
		tasksTexture.loadFromFile("assets/hospital1.png",gRenderer);
	}
	else {
		tasksTexture.loadFromFile("assets/task.png",gRenderer);
	}
	
	tasksTexture.render(gRenderer,position.x- camera.x, position.y- camera.y,0,0);
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