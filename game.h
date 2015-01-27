#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include "gameState.h"
#include "poof.h"
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

	//current frame, for animations
	int frame;

	//gameplay-related values
	unsigned int lastShot;
	unsigned int lastDeath;
	unsigned int lastLevelClear;
	//unsigned int frameCount;
	bool respawnDelay;
	bool levelDelay;

	//player actions: array of boolean
	bool playerAction[TOTAL];

	bool drawPlayer;

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
	bool checkLevel();
	bool getInput();
	void processInput();
	void checkCollisions();
	void splitAsteroid(Asteroid* roid);
	void moveObjects();
	void renderObjects();
	//void scoreBoard();
	void close();
};

#endif /* GAME_H */