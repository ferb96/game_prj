#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "game.h"
#include <ctime>

// THE GLORIOUS MAIN FUNCTION
int main(){
	srand(time(NULL));

	bool playAgain = false;
	do{
		Game theGame;
		if ( !theGame.init() )
			return -1;
		playAgain = theGame.runGame();
	} while (playAgain);
	return 0;
}