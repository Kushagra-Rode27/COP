/*
 * Ball.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "BaseEntity.h"

using namespace std;

class Ball : public BaseEntity {
public:
	// constructor
	Ball(SDL_Renderer* renderer, string texture, int x, int y, float xSpeed, float ySpeed) :
		// call base constructor
		BaseEntity(renderer, texture, x, y),
		// init our fields
		initialXSpeed(xSpeed), initialYSpeed(ySpeed) {};

	void init();
	void update(Uint32 tpf);
	virtual ~Ball();

	// hit a paddle - increase speed
	void hit();
	void resetSpeed() {xVelocity = initialXSpeed; yVelocity = initialYSpeed;}

	float getSpeed() const {return speed;}
	void setSpeed(float speed) {this->speed = speed;}

	float getXVelocity() const {return xVelocity;}
	float getYVelocity() const {return yVelocity;}

	void setXVelocity(float value) {
		if (value > this->maxSpeed) {
			value = maxSpeed;
		}

		if (value < this->maxSpeed*-1) {
			value = maxSpeed*-1;
		}
		xVelocity = value;
	}

	void setYVelocity(float value) {
		if (value > this->maxSpeed) {
			value = maxSpeed;
		}

		if (value < this->maxSpeed*-1) {
			value = maxSpeed*-1;
		}

		yVelocity = value;
	}

private:
	// movement speed
	float initialXSpeed;
	float initialYSpeed;

	float speed = initialXSpeed;
	float maxSpeed = 400;

	float xVelocity = speed;
	float yVelocity = initialYSpeed;

	// sound
	Mix_Chunk * paddleHit = NULL;
};

#endif /* SRC_BALL_H_ */

