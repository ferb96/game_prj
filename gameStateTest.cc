#include "gameState.h"
#include <vector>
#include <iostream>
#include "asteroid.h"
#include "bullet.h"
using namespace std;

int main(){
	GameState gamemgr;
	Asteroid roid1;
	gamemgr.addAsteroid(roid1);
	gamemgr.resetIteRoid();
	Asteroid roid2 = gamemgr.getCurrentAsteroid();
	roid2.drawSelf();
	roid2 = gamemgr.getAsteroid();
	roid2.drawSelf();
	return 0;
}