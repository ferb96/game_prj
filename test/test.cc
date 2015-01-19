#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
 
/* THIS IS A COMMENT. YOU SHOULD BE ABLE TO READ THIS. */
/* Ferb's comment */
 
// Size of the window
int sizeX = 800;
int sizeY = 600;
 
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
int playerPosx = 20;
int playerPosy = 20;
int playerPosw = 20;
int playerPosh = 20;

// Velocity of player
int playerVelx = 0;
int playerVely = 0;

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
		playerPosy -= 10;
	if (playerMoveDown)
		playerPosy += 10;
	if (playerMoveRight)
		playerPosx += 10;
	if (playerMoveLeft)
		playerPosx -=10;
	if (playerPosx < 0)
		playerPosx = 800;
	if (playerPosx > 800)
		playerPosx = 0;
	if (playerPosy < 0)
		playerPosy = 600;
	if (playerPosy > 600)
		playerPosy = 0;
}

void Render()
{
	// Change color of background
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 255 );

	// First we clear the window with that background color
	SDL_RenderClear( renderer );

	// Render a triangle without fill, this is a SDL2_gfx function
	trigonRGBA(renderer,
                 500, 50, // x y of first vertex
                 550, 200, // x y of second vertex
                 600, 150, // x y of third vertex
                 0xFF, 0xFF, 0xFF, 255); // R G B Alpha values (Alpha is transparency, 255 being all opaque)

	// Render a filled triangle, this is a SDL2_gfx function
	filledTrigonRGBA(renderer,
                       200, 200,
                       300, 50,    
                       400, 200, 
                       0, 0, 255, 255);

	// Render a simple line
	lineRGBA(renderer, 
               20, 10, // x y of first point
               70, 90, // x y of second point
               255, 0, 0, 255);

	// Change color of player
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

	// Render a box, aka a rectangle, aka out "Player"
	boxRGBA(renderer, 
              playerPosx, playerPosy, 
              playerPosx+playerPosw, playerPosy+playerPosh,
              0xFF, 0xFF, 0xFF, 255);
 
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