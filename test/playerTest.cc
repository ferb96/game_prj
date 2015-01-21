#include "player.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <iostream>




// Size of the window
int sizeX = 800;
int sizeY = 600;

 Player player1(sizeX, sizeY);
// This will be our main window and renderer we used throughout the program
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
 
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
// Positions of player
/*int playerPosx = 20;
int playerPosy = 20;
int playerPosw = 20;
int playerPosh = 20;*/

// Velocity of player
/*int playerVelx = 0;
int playerVely = 0;*/

// The main program
int main( int argc, char* args[] )
{
	// Init everything, if init fails then quit
	if ( !InitEverything() ) 
		return -1;
 
 
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
						/*case SDLK_SPACE:
							playerMoveRight -= 10;
							break;*/
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
 		player1.updatePosition();
		Render();
 
		// Add a 16msec delay to make our game run at ~60 fps
		SDL_Delay( 16 );
	}

	// Before we quit we must deallocate memory and close everything
	close();
}


void movePlayer()
{
	if (playerMoveUp)
		player1.changeSpeed(2);
	//if (!playerMoveUp)
		//player1.changeSpeed(-1);
	//if (playerMoveDown)
	//	player1.changeSpeed(10);
	if (playerMoveRight)
		player1.changeTrajectory(-.05);
	if (playerMoveLeft)
		player1.changeTrajectory(.05);

	if (player1.getX() < 0)
		player1.setX(800);
	if (player1.getX() > 800)
		player1.setX(0);
	if (player1.getY() < 0)
		player1.setY(600);
	if (player1.getY() > 600)
		player1.setY(0);
}

void Render()
{
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Change color of player
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	SDL_Renderer* rend = renderer;
	// Render a box, aka a rectangle, aka out "Player"
	player1.drawSelf(rend);
 
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



