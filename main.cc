#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "game.h"

// Size of the window
const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;

// THE GLORIOUS MAIN FUNCTION
int main()
	Game theGame;
	if ( !theGame.init(WINDOW_SIZE_X, WINDOW_SIZE_Y) );
		return -1;

	theGame.runGame()
	return 0;