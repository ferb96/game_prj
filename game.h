#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <vector>

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

	//gameplay-related values
	int asteroidSplitNumber;
	int delayBetweenBullets;
	int playerMoveSpeed;
	int asteroidMoveSpeed;
	int bulletMoveSpeed;
	int winSizeX;
	int winSizeY;

	//player actions: array of boolean
	bool playerAction[TOTAL];

	//declare vector of asteroids here (not sure how to works with pointers yet so just leave it here)
	//declare vector of bullets here
	//declare player object here

	//SDL elements
	SDL_Window* window;
	SDL_Renderer* renderer;

	//init functions
	bool initSDL();
	bool createWindow();
	bool createRenderer();
	void setupRenderer();

	//processing functions
	void processInput();
	void moveObjects();
	void renderObjects();
	void close();
};

#endif /* GAME_H */