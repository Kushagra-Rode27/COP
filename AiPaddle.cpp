/*
 * AiPaddle.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "AiPaddle.h"
#include "GameManager.h"

bool AiPaddle::ballMovesAway(Ball &ball) {
	bool ballMovingAway = false;
	if (isLeft) {
		if (ball.getXVelocity() > 0){
			ballMovingAway = true;
		} else {
			ballMovingAway = false;
		}
	} else {
		if (ball.getXVelocity() < 0){
			ballMovingAway = true;
		} else {
			ballMovingAway = false;
		}
	}

	return ballMovingAway;
}

void AiPaddle::moveToCenter(Uint32 tpf) {
	int centerH = GameManager::screenH/2;
	centerH -= this->texH/2;

	float distance = abs(this->y - centerH);

	// slow down if we are nearer than 100 px
	float fact = 1.0f / 100 * distance;
	if (fact > 1) {
		fact = 1;
	}

	this->yVelocity = this->speed * fact;

	if (this->y > centerH) {
		this->yVelocity *= -1;
	}

	this->y += yVelocity * ((float) (tpf) / 1000.0f);
}

void AiPaddle::moveToBall(float absYDistance, int padCenterY, Uint32 tpf,
		Ball& ball) {

	// if the distance is less than the paddle height, we reduce the speed accordingly
	float fact = 1.0f / this->texH * absYDistance;
	if (fact > 1) {
		fact = 1;
	}
	// calculate velocity speed and direction
	this->yVelocity = this->speed * fact;
	if (padCenterY > ball.getCenterY()) {
		// paddle lower than ball - move up
		this->yVelocity *= -1;
	}

	this->y += yVelocity * ((float) (tpf) / 1000.0f);

}

void AiPaddle::update(Uint32 tpf, Ball &ball) {

	// paddle mid
	int padCenterY = this->y + this->texH/2;
	int padCenterX = this->x + this->texW/2;

	// absolute distance to ball
	float absYDistance = abs(padCenterY - ball.getCenterY());
	float absXDistance = abs(padCenterX - ball.getCenterX());

	if (absXDistance > sightRange || ballMovesAway(ball)) {
		// can't see ball
		moveToCenter(tpf);
	} else {
		// if the distance is less than the paddle height, we reduce the speed accordingly
		moveToBall(absYDistance, padCenterY, tpf, ball);
	}

	// limit paddle movement
	if (this->y + this->texH > GameManager::screenH) {
		this->y = GameManager::screenH - this->texH;
	}
	if (this->y + this->texH < 0) {
		this->y = 0;
	}
}

void AiPaddle::init() {

	// tint color red
	if (isLeft) {
		SDL_SetTextureColorMod(tex, 0xF0, 0x00, 0x00);
	} else {
		SDL_SetTextureColorMod(tex, 0x00, 0x00, 0xF0);
	}

	// adjust x location for the right paddle
	if (this->isLeft == false) {
		x -= texW;
	}

	y -= texH/2;
}

AiPaddle::~AiPaddle() {

}

void AiPaddle::resetPos() {
	x = initialX;
	y = initialY -texH/2;
}
