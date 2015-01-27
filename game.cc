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

	gamemgr.initLevel();
	gameLoop();
	//scoreBoard();
	close();
}

void Game::gameLoop(){
	bool loop = true;
	while (loop){
		if ( !checkLevel() )
			loop = false;
		if ( !getInput() )
			loop = false;
		processInput();
		checkCollisions();
		moveObjects();
		renderObjects();
		SDL_Delay(17);
	}
}

bool Game::checkLevel(){
	bool gameOver = false;

	// Handling player respawn
	Player* lePlayer = gamemgr.getPlayer();

	if ( lePlayer->isAlive() ){
		if ( lePlayer->isInvul() && SDL_GetTicks() - lastDeath >= INVULNERABLE_DURATION )
			lePlayer->setInvul(false);
		if ( !lePlayer->isInvul() )
			lastDeath = SDL_GetTicks();
	}
	if ( !lePlayer->isAlive() ){
		if ( lePlayer-> getLivesLeft() == 0 )
			gameOver = true;
		if ( lePlayer-> getLivesLeft() > 0 )
			if ( SDL_GetTicks() - lastDeath >= DELAY_BETWEEN_RESPAWNS ){
				lePlayer->setAlive(true);
				lePlayer->setInvul(true);
				lePlayer->resetPlayer(WINDOW_SIZE_X, WINDOW_SIZE_Y);
			}
	}

	// Handling new levels
	if (gamemgr.zeroAsteroid()){
		if (SDL_GetTicks() - lastLevelClear >= DELAY_BETWEEN_LEVELS)
			gamemgr.initLevel();
	}
	else
		lastLevelClear = SDL_GetTicks();

	return (!gameOver);
}

void Game::checkCollisions(){
	Player* lePlayer = gamemgr.getPlayer();
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		//check for collision between player and roid
		if ( lePlayer->checkCollision(roid) && lePlayer->isAlive() && !lePlayer->isInvul()){
			lePlayer->setAlive(false);
			lePlayer->minusOneLife();
			splitAsteroid(roid);
		}
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
}

void Game::moveObjects(){
	Player* lePlayer = gamemgr.getPlayer();
	lePlayer->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	}
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->updatePosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		//check for bullet expiration
		if ( bull->isExpired() )
			gamemgr.delBullet();
	}
}

void Game::processInput(){
	Player* lePlayer = gamemgr.getPlayer();
	if (lePlayer->isAlive()){
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
	}
}

void Game::splitAsteroid(Asteroid* roid){
	gamemgr.delAsteroid();
	if (roid->getLevel() < 2){
		Asteroid* newroid1 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() + M_PI/6, 1.0, 50, roid->getLevel()+1);
		Asteroid* newroid2 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() - M_PI/6, 1.0, 50, roid->getLevel()+1);
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
	if (lePlayer->isAlive())
		lePlayer->drawSelf( renderer );

	//Render the Asteroids
	gamemgr.resetIteRoid();
	while ( !gamemgr.noMoreAsteroid() ){
		Asteroid* roid = gamemgr.getAsteroid();
		roid->drawSelf(renderer);
	}

	//Render the Bullets
	gamemgr.resetIteBullet();
	while ( !gamemgr.noMoreBullet() ){
		Bullet* bull = gamemgr.getBullet();
		bull->drawSelf(renderer);
	}
 
	// Render the changes above to the window
	SDL_RenderPresent( renderer );
}

Game::Game(){
	window = NULL;
	this->renderer = NULL;
	for (int i = 0; i < TOTAL; i++)
		playerAction[i] = false;
	this->frame = 0;
	lastShot = 0;
	lastDeath = 0;
	lastLevelClear = 0;
	respawnDelay = false;
	levelDelay = false;
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
	window = SDL_CreateWindow( "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0 );
 
	if ( window == NULL )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
 
	return true;
}

bool Game::createRenderer()
{
	this->renderer = SDL_CreateRenderer( window, -1, 0 );
 
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
	SDL_RenderSetLogicalSize( this->renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y );
 
	// Set color of renderer to red
	SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 255 );
}

void Game::close()
{

	//Destroy Renderer
	SDL_DestroyRenderer( this->renderer );
	this->renderer = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return;
}

bool Game::getInput(){
	bool notQuitted = true;
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_QUIT:
				notQuitted = false;
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
	return notQuitted;
}