/*
 * PlayerPaddle.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "PlayerPaddle.h"
#include "GameManager.h"

void PlayerPaddle::init() {

	// we want to draw the paddle at location 'x'
	// adjust x to be in the center of the paddle
	x -= texW/2;
	y -= texH/2;
}

void PlayerPaddle::handleEvent(SDL_Event &e) {
	if (e.key.keysym.sym == SDLK_UP) {
		if (e.type == SDL_KEYDOWN) {
			moveUp = true;
		} else if (e.type == SDL_KEYUP) {
			moveUp = false;
		}
	}

	if (e.key.keysym.sym == SDLK_DOWN) {
		if (e.type == SDL_KEYDOWN) {
			moveDown = true;
		} else if (e.type == SDL_KEYUP) {
			moveDown = false;
		}
	}
}

void PlayerPaddle::update(Uint32 tpf) {
	if (disabled) {
		return;
	}
	if (moveUp && moveDown) {
		return;
	}

	float velocity = 0;
	if (moveDown) {
		velocity = speed;
	}

	if (moveUp) {
		velocity = speed * -1.0f;
	}

	y += velocity * (tpf/1000.f);

	if (y < 0) {
		y = 0;
	}

	if (y + this->texH > GameManager::screenH) {
		y = GameManager::screenH - this->texH;
	}
}

PlayerPaddle::~PlayerPaddle() 
{

}

