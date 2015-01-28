#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL_ttf.h"
#include <string>
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
	bool runGame(); 

private:
	//enumerators
	enum playerStates { 
		MOVING_UP,
		MOVING_DOWN,
		MOVING_LEFT,
		MOVING_RIGHT,
		SHOOTING,
		REPLAY,
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
	unsigned int score;
	unsigned int lifeEarned;
	bool respawnDelay;
	bool levelDelay;

	//player actions: array of boolean
	bool playerAction[TOTAL];

	//SDL elements
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	TTF_Font *font;
	TTF_Font *symbolfont;

	//utility functions
	void renderText(string text, double x, double y, TTF_Font *font);
	void addScore(int roidLevel);

	//init functions
	bool initSDL();
	bool createWindow();
	bool createRenderer();
	void setupRenderer();

	//processing functions
	bool gameLoop();
	bool checkLevel();
	bool getInput();
	void processInput();
	void checkCollisions();
	void splitAsteroid(Asteroid* roid);
	void moveObjects();
	void renderObjects();
	bool scoreBoard();
	void close();
};

#endif /* GAME_H */