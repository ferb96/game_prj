#include "player.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <iostream>
#include "bullet.h"
#include "gameState.h"
#include "asteroid.h"


// Size of the window
int sizeX = 800;
int sizeY = 600;

const double BULLET_SPEED = 10;
const double BULLET_REACH = 300;

// This will be our main window and renderer we used throughout the program
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

GameState game;
Asteroid ast1(sizeX/4, sizeY/4, 0.0, 2.0, 60, 0);
Player player1(sizeX/2, sizeY/2);
// Declaring functions, implement them afterwards
bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();
 
void movePlayer();
void Render();
void RunGame();
void close();


bool playerMoveUp = false;
bool playerMoveDown = false;
bool playerMoveLeft = false;
bool playerMoveRight = false; 
bool playerShoot = false;
// The main program
int main( int argc, char* args[] )
{
	// Init everything, if init fails then quit
	if ( !InitEverything() ) 
		return -1;
 
 	player1.setDecel(0.03);
	// Run the game
	RunGame();

	return 0;
}


void RunGame()
{
	// Basically the game is a big loop. This is the flag to know if the game has finished or not
	bool loop = true;
 
	while ( loop )
	{
		// Processing events by pulling each item out of the event queue
		SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type ) {
				case ( SDL_QUIT ):
					loop = false;
					break;
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
											// Move the user
						case SDLK_RIGHT:
							playerMoveRight  = true;
							break;
						case SDLK_LEFT:
							playerMoveLeft = true;
							break;
						case SDLK_DOWN:
							playerMoveDown = true;
							break;
						case SDLK_UP:
							playerMoveUp = true;
							break;
						case SDLK_SPACE:
							playerShoot = true;
							//Bullet* bull = player1.shoot(BULLET_SPEED, BULLET_REACH);
							game.addBullet(player1.shoot(BULLET_SPEED, BULLET_REACH));
							break;
						default :
							break;
					}
					break;
				case SDL_KEYUP:
 	               switch( event.key.keysym.sym ){
    	                case SDLK_RIGHT:
							playerMoveRight  = false;
							break;
						case SDLK_LEFT:
							playerMoveLeft = false;
							break;
						case SDLK_DOWN:
							playerMoveDown = false;
							break;
						case SDLK_UP:
							playerMoveUp = false;
							break;
    	                default:
        	                break;
            	    }
                	break;
             
   	        	default:
        	        break;
			}
		}
 		
 		// Draw everything on the screen
 		movePlayer();
 		player1.updatePosition(sizeX, sizeY);
 		ast1.updatePosition(sizeX, sizeY);
 		game.resetIteBullet();
		while (!game.noMoreBullet()) {
			Bullet* bull = game.getBullet();
			bull->updatePosition(sizeX, sizeY);
			if ( bull->isExpired() )
				game.delBullet();
	}

		Render();
 
		// Add a 16msec delay to make our game run at ~60 fps
		SDL_Delay( 17 );
	}

	// Before we quit we must deallocate memory and close everything
	close();
}


void movePlayer()
{
	if (playerMoveUp)
		player1.setAccel(.15);
	if (!playerMoveUp)
		player1.setAccel(0);
	if (playerMoveRight)
		player1.changeTrajectory(.07);
	if (playerMoveLeft)
		player1.changeTrajectory(-.07);
	//if (playerShoot)

}

void Render()
{
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Change color of player
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	// Render a box, aka a rectangle, aka out "Player"
	player1.drawSelf( renderer );
	ast1.drawSelf( renderer );

	game.resetIteBullet();
	while (!game.noMoreBullet()) {
		Bullet* bull = game.getBullet();
		//bull->updatePosition(sizeX, sizeY);
		bull->drawSelf(renderer);
	}
 
	// Render the changes above to the window
	SDL_RenderPresent( renderer );

}


bool InitEverything()
{
	// Init the SDL and everything
	if ( !InitSDL() )
		return false;
 
 	// Create a window
	if ( !CreateWindow() )
		return false;
 
 	// Create the renderer
	if ( !CreateRenderer() )
		return false;
 
 	// Setup the renderer
	SetupRenderer();
 
	return true;
}


bool InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
 
	return true;
}


bool CreateWindow()
{
	window = SDL_CreateWindow( "LOLOLOL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeX, sizeY, 0 );
 
	if ( window == NULL )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
 
	return true;
}


bool CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, 0 );
 
	if ( renderer == NULL )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
 
	return true;
}


void SetupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, sizeX, sizeY );
 
	// Set color of renderer to red
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );
}


void close()
{

	//Destroy Renderer
	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return;
}




