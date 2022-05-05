/*
 * AiPaddle.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_AIPADDLE_H_
#define SRC_AIPADDLE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ball.h"

using namespace std;

class AiPaddle : public BaseEntity {
public:
	AiPaddle(SDL_Renderer* renderer, string texture, float x, float y, float speed, bool isLeft,
				float sightRange)
	// base constructor
	: BaseEntity(renderer, texture, x, y),
	  // init our fields
	  initialX(x), initialY(y), speed(speed), isLeft(isLeft), sightRange(sightRange)
		{};

	void init();
	void update(Uint32 tpf, Ball &ball);

	void resetPos();;

	virtual ~AiPaddle();

private:
	float initialX;
	float initialY;
	float speed;
	bool isLeft;

	float yVelocity = speed;

	float sightRange;

	void moveToBall(float absYDistance, int padCenterY, Uint32 tpf, Ball& ball);
	void moveToCenter(Uint32 tpf);
	bool ballMovesAway(Ball &ball);
};

#endif /* SRC_AIPADDLE_H_ */
