#include "game.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include <iostream>

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