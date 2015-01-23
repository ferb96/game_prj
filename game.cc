#include "game.h"
#include "gameState.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include <iostream>
using namespace std;

// Gameplay-related constants
const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;
const int ASTEROID_SPLIT_NUMBER = 2;
const int DELAY_BETWEEN_BULLETS = 500;
const int PLAYER_MOVE_SPEED = 8;
const int ASTEROID_MOVE_SPEED = 9;
const int BULLET_MOVE_SPEED = 20;

/*
 * Implementing the functions in the Game class
 */
void Game::runGame(){
	Player* lePlayer = new Player(winSizeX/2, winSizeY/2);
	lePlayer->setDecel(.05);
	gamemgr.addPlayer(lePlayer);
	gameLoop();
	//scoreBoard();
	close();
}

void Game::gameLoop(){
	bool loop = true;
	while (loop){
		if ( !processInput() )
			loop = false;
		if ( !checkCollisions() )
			loop = false;
		moveObjects();
		renderObjects();
		SDL_Delay(16);
	}
}

bool Game::checkCollisions(){
	bool playerAlive = true;
	Player* lePlayer = gamemgr.getPlayer();
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		//check for collision between player and roid
		gamemgr.resetIteBullet();
		while ( !gamemgr.noMoreBullet() ){
			Bullet* bull = gamemgr.getBullet();
			//check for collision between roid and bull
			//check for bullet expiration
		}
	}
	return playerAlive;
}

void Game::moveObjects(){
	Player* lePlayer = gamemgr.getPlayer();
	if (playerAction[MOVING_UP])
		lePlayer->setAccel(.15);
	if (!playerAction[MOVING_UP])
		lePlayer->setAccel(0);
	if (playerAction[MOVING_RIGHT])
		lePlayer->changeTrajectory(.07);
	if (playerAction[MOVING_LEFT])
		lePlayer->changeTrajectory(-.07);
	lePlayer->updatePosition(winSizeX, winSizeY);
}

void Game::renderObjects(){
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Change color of player
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	// Render the player
	Player* lePlayer = gamemgr.getPlayer();
	lePlayer->drawSelf( renderer );
 
	// Render the changes above to the window
	SDL_RenderPresent( renderer );
}

Game::Game(){
	this->window = NULL;
	this->renderer = NULL;
	for (int i; i < TOTAL; i++)
		playerAction[i] = false;
	this->asteroidSplitNumber = ASTEROID_SPLIT_NUMBER;
	this->delayBetweenBullets = DELAY_BETWEEN_BULLETS;
	this->playerMoveSpeed = PLAYER_MOVE_SPEED;
	this->asteroidMoveSpeed = ASTEROID_MOVE_SPEED;
	this->bulletMoveSpeed = BULLET_MOVE_SPEED;
	this->winSizeX = WINDOW_SIZE_X;
	this->winSizeY = WINDOW_SIZE_Y;
}

bool Game::init(){
	// Init the SDL and everything
	if ( !initSDL() )
		return false;
 
 	// Create a window
	if ( !createWindow() )
		return false;
 
 	// Create the renderer
	if ( !createRenderer() )
		return false;
 	
 	// Setup the renderer
	setupRenderer();

	return true;
}

bool Game::initSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
 
	return true;
}

bool Game::createWindow()
{
	this->window = SDL_CreateWindow( "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->winSizeX, this->winSizeY, 0 );
 
	if ( this->window == NULL )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
 
	return true;
}

bool Game::createRenderer()
{
	this->renderer = SDL_CreateRenderer( this->window, -1, 0 );
 
	if ( this->renderer == NULL )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
 
	return true;
}

void Game::setupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( this->renderer, this->winSizeX, this->winSizeY );
 
	// Set color of renderer to red
	SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 255 );
}

void Game::close()
{

	//Destroy Renderer
	SDL_DestroyRenderer( this->renderer );
	this->renderer = NULL;

	//Destroy window
	SDL_DestroyWindow( this->window );
	this->window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return;
}

bool Game::processInput(){
	bool gameRunning = true;
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
					case SDLK_RIGHT:
						playerAction[MOVING_RIGHT] = true;
						break;
					case SDLK_LEFT:
						playerAction[MOVING_LEFT] = true;
						break;
					case SDLK_DOWN:
						playerAction[MOVING_DOWN] = true;
						break;
					case SDLK_UP:
						playerAction[MOVING_UP] = true;
						break;
					case SDLK_SPACE:
						playerAction[SHOOTING] = true;
						break;
					default :
						break;
				}
				break;

			case SDL_KEYUP:
	            switch( event.key.keysym.sym ){
					case SDLK_RIGHT:
						playerAction[MOVING_RIGHT] = false;
						break;
					case SDLK_LEFT:
						playerAction[MOVING_LEFT] = false;
						break;
					case SDLK_DOWN:
						playerAction[MOVING_DOWN] = false;
						break;
					case SDLK_UP:
						playerAction[MOVING_UP] = false;
						break;
					case SDLK_SPACE:
						playerAction[SHOOTING] = false;
						break;
					default :
						break;
	    	    }
	        	break;

	        default:
		    	break;
		}
	}
	return gameRunning;
}