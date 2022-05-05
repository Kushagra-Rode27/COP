/*
 * GameManager.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "GameManager.h"

GameManager::~GameManager() {
	TTF_CloseFont(fpsFont);
	TTF_CloseFont(scoreFont);
}

void GameManager::init(int screenW, int screenH) {
	this->screenW = screenW;
	this->screenH = screenH;

	this->scoreFont = TTF_OpenFont("res/OpenSans-Regular.ttf", 40);
	this->fpsFont = TTF_OpenFont("res/OpenSans-Regular.ttf", 25);
}

bool GameManager::handleInput() {
	bool quit = false;

	SDL_Event e = {0};
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			cout << "QUIT requested, exiting ..." << endl;
			quit = true;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			cout << "ESC pressed, exiting ... " << endl;
			quit = true;
		}

		// pass event to player
		player.handleEvent(e);
	}
	return quit;
}

void GameManager::render() {

	// clear screen
	SDL_SetRenderDrawColor(pRenderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear(pRenderer);

	drawUI();

	player.render();

	ball.render();

	aiLeft.render();
	aiRight.render();

	// update screen
	SDL_RenderPresent(pRenderer);
}

// tpf: time per frame
void GameManager::update(Uint32 tpf) {
	player.update(tpf);
	ball.update(tpf);

	aiLeft.update(tpf, ball);
	aiRight.update(tpf, ball);

	checkCollision();

	Uint32 now = SDL_GetTicks();
	if (lastFpsUpdate < now-300) {
		fps = (float)1000/(float)tpf;
		lastFpsUpdate = SDL_GetTicks();
	}
}

float GameManager::calcYVelChange(const SDL_Rect& playerRect, int ballY) {
	// paddle center
	int paddleCenter = playerRect.y + playerRect.h / 2;
	// distance from center
	float dist = abs(ballY - paddleCenter);
	float fact = 1.0f / playerRect.h * dist;
	float yVelChange = 100.0f * fact;
	if (ballY > paddleCenter) {
		// hit lower region
	} else {
		yVelChange *= -1;
	}

	// add some random variance
	int randYvel = (rand()%20)-10;
	return yVelChange + randYvel;
}

void GameManager::checkCollision() {
	// check paddle collision

	SDL_Rect ballRect = ball.getRect();
	SDL_Rect playerRect = player.getRect();
	SDL_Rect aiLeftRect = aiLeft.getRect();
	SDL_Rect aiRightRect = aiRight.getRect();

	SDL_Rect result;

	if (player.isDisabled() == false && SDL_IntersectRect(&playerRect, &ballRect, &result) == SDL_TRUE) {
		fprintf(stderr, "player hit\n");
		// ball hit player paddle
		// reset ball to player edge
		// bounce
		ball.setX(playerRect.x + playerRect.w+1);
		ball.setXVelocity(abs(ball.getXVelocity()));

		// ball center
		int ballY = ball.getCenterY();

		// calc y velocity change
		float yVelChange = calcYVelChange(playerRect, ballY);
		ball.setYVelocity(ball.getYVelocity() + yVelChange);

		ball.hit();
	}

	// check collision with right ai
	if (SDL_IntersectRect(&ballRect, &aiRightRect, &result) == SDL_TRUE) {
		// ball hit ai paddle
		// reset ball to paddle edge
		// bounce to the left
		ball.setX(aiRightRect.x - ballRect.w);
		ball.setXVelocity(-ball.getXVelocity());

		// ball center
		int ballY = ball.getCenterY();
		float yVelChange = calcYVelChange(aiRightRect, ballY);
		ball.setYVelocity(ball.getYVelocity()+yVelChange);

		ball.hit();
	}

	// check collision with left ai
	if (SDL_IntersectRect(&ballRect, &aiLeftRect, &result) == SDL_TRUE) {
		// ball hit ai paddle
		// reset ball to paddle edge
		// bounce to the right
		ball.setX(aiLeftRect.x + aiLeftRect.w);
		ball.setXVelocity(abs(ball.getXVelocity()));

		// ball center
		int ballY = ball.getCenterY();
		float yVelChange = calcYVelChange(aiLeftRect, ballY);
		ball.setYVelocity(ball.getYVelocity()+yVelChange);

		ball.hit();
	}

	// check play field collision
	SDL_Rect windowSize;
	SDL_RenderGetViewport(pRenderer, &windowSize);

	if (ball.getX() < 0) {
		// left wall hit - AI scores
		aiScore++;
		restartRound();
		return;
	}

	if (ball.getX() + ball.getTexW() > windowSize.w) {
		// right wall hit - Player scores
		playerScore++;
		restartRound();
		return;
	}

	if (ball.getY() < 0) {
		// top hit - bounce down
		ball.setY(0);
		ball.setYVelocity(abs(ball.getYVelocity()));
	}

	if (ball.getY() + ball.getTexH() > windowSize.h) {
		ball.setY(windowSize.h - ball.getTexH());
		ball.setYVelocity(abs(ball.getYVelocity()) * -1);
	}
}

void GameManager::restartRound() {

	// reset ball position
	ball.resetSpeed();

	int randDirection = rand() %2;

	// random value between -50 and 50
	int randYVel = (rand() %100) -50;

	ball.setXVelocity(ball.getXVelocity() * (randDirection == 0?-1:1));
	ball.setYVelocity(ball.getYVelocity() + randYVel);

	ball.setX(GameManager::screenW/2 - ball.getTexW()/2);
	ball.setY(GameManager::screenH/2);

	player.resetPos();

	aiLeft.resetPos();
	aiRight.resetPos();
}

void GameManager::renderScore(int score, int x, int y) {
	// player score
	string sPlayerScore = std::to_string(score);
	SDL_Color scoreColor = { 255, 255, 255, 0};
	SDL_Surface* tmpSurface = TTF_RenderText_Blended(scoreFont,
			sPlayerScore.c_str(), scoreColor);
	SDL_Texture* playerScoreTex = SDL_CreateTextureFromSurface(pRenderer,
			tmpSurface);
	int texW;
	int texH;
	SDL_QueryTexture(playerScoreTex, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = texW;
	dstRect.h = texH;
	SDL_RenderCopy(pRenderer, playerScoreTex, NULL, &dstRect);

	SDL_FreeSurface(tmpSurface);
	SDL_DestroyTexture(playerScoreTex);
}

void GameManager::drawUI() {

	// draw middle line
	SDL_SetRenderDrawColor(pRenderer, 0xFF,0xFF,0xFF,120);

	SDL_RenderDrawLine(this->pRenderer, this->screenW/2, 20, this->screenW/2,this->screenH-20);

	// player score
	renderScore(playerScore, screenW / 2 - 100, 30);
	// ai score
	renderScore(aiScore, screenW / 2 + 100, 30);
	// show fps
	drawFps();
}

void GameManager::drawFps() {
	string sFps = "FPS: " +std::to_string(fps);

	SDL_Color color = { 255, 255, 0, 0};
	SDL_Surface* tmpSurface = TTF_RenderText_Blended(fpsFont,
			sFps.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(pRenderer,
			tmpSurface);
	int texW;
	int texH;
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
	SDL_Rect fpsRect;
	fpsRect.x = 20;
	fpsRect.y = 20;
	fpsRect.w = texW;
	fpsRect.h = texH;

	SDL_RenderCopy(pRenderer, tex, NULL, &fpsRect);

	SDL_FreeSurface(tmpSurface);
	SDL_DestroyTexture(tex);

}


