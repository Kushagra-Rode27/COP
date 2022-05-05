/*
 * GameManager.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_GAMEMANAGER_H_
#define SRC_GAMEMANAGER_H_

#include <iostream>

#include "PlayerPaddle.h"
#include "AiPaddle.h"
#include "Ball.h"

#include "SDL2/SDL_ttf.h"

class GameManager {
public:
	static int screenW;
	static int screenH;

	GameManager(SDL_Renderer *pRenderer, Ball &b, PlayerPaddle &player,
				AiPaddle &aiLeft, AiPaddle &aiRight)
		: pRenderer(pRenderer), ball(b), player(player),
		  aiLeft(aiLeft), aiRight(aiRight) {};

	GameManager(const GameManager &orig) = delete;

	void init(int screenW, int screenH);

	bool handleInput();
	// render all objects
	void render();
	// update all objects
	void update(Uint32 tpf);

	void drawFps();
	void drawUI();
	void checkCollision();
	void restartRound();

	PlayerPaddle &getPlayer()  {return player;}

	virtual ~GameManager();
private:
	SDL_Renderer *pRenderer;
	Ball &ball;

	PlayerPaddle &player;

	AiPaddle &aiLeft;
	AiPaddle &aiRight;

	int playerScore = 0;
	int aiScore = 0;

	int fps = 0;
	Uint32 lastFpsUpdate = 0;

	TTF_Font* scoreFont = NULL;
	TTF_Font* fpsFont = NULL;

	void renderScore(int score, int x, int y);
	float calcYVelChange(const SDL_Rect& playerRect, int ballY);
};

#endif /* SRC_GAMEMANAGER_H_ */
