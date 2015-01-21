#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "game.h"

// THE GLORIOUS MAIN FUNCTION
int main()
	Game theGame;
	if ( !theGame.init() );
		return -1;

	theGame.runGame()
	return 0;