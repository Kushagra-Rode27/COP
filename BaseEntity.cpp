/*
 * BaseEntity.cpp
 *
 *  Created on: 26.03.2018
 *      Author: core
 */

#include "BaseEntity.h"

BaseEntity::BaseEntity(SDL_Renderer *renderer, string texture,
						int x, int y)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;

	this->disabled = false;
	// loads texture
	tex = IMG_LoadTexture(renderer, texture.c_str());

	if (tex == NULL) {
		cerr << "unable to load png: " << SDL_GetError() << endl;
	}

	// query the texture to save the width and height
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
}

void BaseEntity::render() {
	if (disabled) {
		return;
	}
	SDL_Rect dstRect = getRect();
	SDL_RenderCopy(renderer, tex, NULL, &dstRect);
}

// returns a SDL_Rect with the current position and texture size
SDL_Rect BaseEntity::getRect() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = texW;
	rect.h = texH;

	return rect;
}
/**
 * Destroy texture.
 */
BaseEntity::~BaseEntity() {

	if (tex != NULL) {
		SDL_DestroyTexture(tex);
	}
}

