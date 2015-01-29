#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "game.h"
#include "gameState.h"
#include <ctime>

// THE GLORIOUS MAIN FUNCTION
int main(){
	srand(time(NULL));

	GameState gameData;
	Game theGame;
		if ( !theGame.init() )
			return -1;

	bool playAgain = false;
	do{
		playAgain = theGame.runGame(gameData);
	} while (playAgain);

	theGame.close();
	return 0;
}