/*
 * PlayerPaddle.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_PLAYERPADDLE_H_
#define SRC_PLAYERPADDLE_H_
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "BaseEntity.h"

using namespace std;

class PlayerPaddle :public BaseEntity {
public:
	PlayerPaddle(SDL_Renderer* renderer, string texture, float x, float y, float speed)
		// call base constructor
		: BaseEntity(renderer, texture, x, y),
		  // initialize our fields
		  initialX(x), initialY(y), speed(speed)  {};
	void init();
	void handleEvent(SDL_Event &e);
	void update(Uint32 tpf);
	virtual ~PlayerPaddle();

	void resetPos() {x = initialX; y = initialY -texH/2; };

private:
	float initialX;
	float initialY;
	float speed;

	bool moveUp = false;
	bool moveDown = false;
};

#endif /* SRC_PLAYERPADDLE_H_ */
