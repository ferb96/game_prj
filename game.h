#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include "gameState.h"
using namespace std;

class Game
{
public:
	Game();
	bool init();
	void runGame(); 

private:
	//enumerators
	enum playerStates { 
		MOVING_UP,
		MOVING_DOWN,
		MOVING_LEFT,
		MOVING_RIGHT,
		SHOOTING,
		TOTAL
	};

	//the GameState
	GameState gamemgr;

	//gameplay-related values
	int asteroidSplitNumber;
	unsigned int lastShot;
	unsigned int delayBetweenBullets;
	int playerMoveSpeed;
	int asteroidMoveSpeed;
	int bulletMoveSpeed;
	int winSizeX;
	int winSizeY;

	//player actions: array of boolean
	bool playerAction[TOTAL];

	//SDL elements
	SDL_Window* window;
	SDL_Renderer* renderer;

	//init functions
	bool initSDL();
	bool createWindow();
	bool createRenderer();
	void setupRenderer();

	//processing functions
	void gameLoop();
	bool processInput();
	bool checkCollisions();
	void moveObjects();
	void renderObjects();
	//void scoreBoard();
	void close();
};

#endif /* GAME_H */