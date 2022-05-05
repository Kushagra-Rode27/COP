/*
 * BaseEntity.h
 *
 *  Created on: 26.03.2018
 *      Author: core
 */

#ifndef SRC_BASEENTITY_H_
#define SRC_BASEENTITY_H_

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;
/**
 * The BaseEntity has the following attributes:
 * - a pointer to the renderer
 * - a texture
 * - width / height of the texture
 * - x/y position (top left corner of the texture)
 */
class BaseEntity {
public:
	BaseEntity(SDL_Renderer *renderer, string texture,	int x, int y);
	virtual ~BaseEntity();

	virtual void render();

	float getCenterY() {return this->y + this->texH/2 ;}
	float getCenterX() {return this->x + this->texW/2 ;}

	int getX() {return x;}
	void setX(int x) {this->x = x;}

	int getTexW() {return this->texW;}
	void setTexW(int val) {this->texW = val;}

	int getY() {return y;}
	void setY(int val) {this->y = val;}

	int getTexH() {return this->texH;}
	void setTexH(int val) {this->texH = val;}

	SDL_Rect getRect();

	void setDisabled(bool value) {this->disabled = value;}
	bool isDisabled() {return disabled;}
protected:
	SDL_Renderer *renderer;
	SDL_Texture *tex = NULL;
	float x;
	float y;
	int texW = 0;
	int texH = 0;

	bool disabled = false;
};

#endif /* SRC_BASEENTITY_H_ */
