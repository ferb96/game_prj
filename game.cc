#include "game.h"
#include "gameState.h"
#include "const.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

/*
 * Implementing the functions in the Game class
 */
void Game::runGame(){

	Asteroid* ast1 = new Asteroid(winSizeX/4, winSizeY/4, 0.0, 2.0, 50, 0);
	gamemgr.addAsteroid(ast1);
	Asteroid* ast2 = new Asteroid(700, 500, 2.0, 1.0, 50, 0);
	gamemgr.addAsteroid(ast2);
	Asteroid* ast3 = new Asteroid(100, 400, 3.0, 1.5, 50, 0);
	gamemgr.addAsteroid(ast3);

	gameLoop();
	//scoreBoard();
	close();
}

void Game::gameLoop(){
	bool loop = true;
	while (loop){
		//check player dead
		//check level finished
		if ( !processInput() )
			loop = false;
		if ( !checkCollisions() )
			loop = false;
		moveObjects();
		renderObjects();
		SDL_Delay(17);
		frame++;
	}
}

bool Game::checkCollisions(){
	bool playerAlive = true;
	Player* lePlayer = gamemgr.getPlayer();
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		//check for collision between player and roid
		if ( lePlayer->checkCollision(roid) )
			playerAlive = false;
		gamemgr.resetIteBullet();
		while ( !gamemgr.noMoreBullet() ){
			Bullet* bull = gamemgr.getBullet();
			//check for collision between roid and bull
			if ( roid->checkCollision(bull) ){
				splitAsteroid(roid);
				gamemgr.delBullet();
			}
		}
	}
	return playerAlive;
}

void Game::moveObjects(){
	Player* lePlayer = gamemgr.getPlayer();
	if (playerAction[MOVING_UP])
		lePlayer->setAccel(.08);
	if (!playerAction[MOVING_UP])
		lePlayer->setAccel(0);
	if (playerAction[MOVING_RIGHT])
		lePlayer->changeTrajectory(.07);
	if (playerAction[MOVING_LEFT])
		lePlayer->changeTrajectory(-.07);
	if (playerAction[SHOOTING])
		if (SDL_GetTicks() - lastShot > DELAY_BETWEEN_BULLETS){
			lastShot = SDL_GetTicks();
			gamemgr.addBullet(lePlayer->shoot(BULLET_MOVE_SPEED, BULLET_LIFESPAN));
		}
	if (!playerAction[SHOOTING])
		lastShot = 0;

	lePlayer->updatePosition(winSizeX, winSizeY);
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->updatePosition(winSizeX, winSizeY);
	}
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->updatePosition(winSizeX, winSizeY);
		//check for bullet expiration
		if ( bull->isExpired() )
			gamemgr.delBullet();
	}
}

void Game::splitAsteroid(Asteroid* roid){
	gamemgr.delAsteroid();
	if (roid->getLevel() < 2){
		Asteroid* newroid1 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() + M_PI/6, 3.0, 50, roid->getLevel()+1);
		Asteroid* newroid2 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() - M_PI/6, 3.0, 50, roid->getLevel()+1);
		gamemgr.addAsteroid(newroid1);
		gamemgr.addAsteroid(newroid2);
	}
	gamemgr.resetIteRoid();
}

void Game::renderObjects(){
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Color of every other objects
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	// Render the player
	Player* lePlayer = gamemgr.getPlayer();
	lePlayer->drawSelf( renderer );

	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->drawSelf(renderer);
	}
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->drawSelf(renderer);
	}
 
	// Render the changes above to the window
	SDL_RenderPresent( renderer );
}

Game::Game(){
	this->frame = 0;
	this->window = NULL;
	this->renderer = NULL;
	for (int i = 0; i < TOTAL; i++)
		playerAction[i] = false;
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