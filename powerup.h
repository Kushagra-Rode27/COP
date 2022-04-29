#ifndef POWERUP_H
#define POWERUP_H 

using namespace std;   


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "tile.h"
#include <SDL2/SDL_mixer.h>

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
	void Render(SDL_Rect& camera,LTexture powerUpTexture,SDL_Renderer* gRenderer);

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

#endif