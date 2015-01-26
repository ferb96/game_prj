#include "gameState.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
#include "const.h"
using namespace std;

GameState::GameState(){
	Player* lePlayer = new Player(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2);
	lePlayer->setDecel(PLAYER_DECELERATION);
	addPlayer(lePlayer);
	iteRoid = leAsteroids.begin();
	iteBull = leBullets.begin();
	level = 0;
	minRoid = 1;
	maxRoid = 2;
	roidSpdLimit = .5;
}

void GameState::initLevel(){
	level++;
	if (level % 2 == 0)
		maxRoid++;
	if (level % 2 != 0)
		minRoid++;
	roidSpdLimit += .2;

	//generating Asteroids
	int numberOfRoids = rand() % (maxRoid - minRoid);
	numberOfRoids += minRoid;
	for (int i = 0; i < numberOfRoids; i++){
		
	}
}

void GameState::addPlayer(Player* playa){
	lePlayer = playa;
}

void GameState::addAsteroid(Asteroid* roid){
	leAsteroids.push_back(roid);
}

void GameState::addBullet(Bullet* bull){
	leBullets.push_back(bull);
}

void GameState::delAsteroid(){
	if (iteRoid != leAsteroids.begin()){
		iteRoid = leAsteroids.erase(iteRoid-1);
	}
	else
		cout << "Error: deleting nonexistent asteroid" << endl;
}

void GameState::delBullet(){
	if (iteBull != leBullets.begin()){
		iteBull = leBullets.erase(iteBull-1);
	}
	else
		cout << "Error: deleting nonexistent bullet" << endl;
}

Player* GameState::getPlayer(){
	return lePlayer;
}

Asteroid* GameState::getAsteroid(){
	Asteroid* tmp = *iteRoid;
	iteRoid++;
	return tmp;
}

Bullet* GameState::getBullet(){
	Bullet* tmp = *iteBull;
	iteBull++;
	return tmp;
}

bool GameState::noMoreAsteroid(){
	if (iteRoid == leAsteroids.end())
		return true;
	return false;
}

bool GameState::noMoreBullet(){
	if (iteBull == leBullets.end())
		return true;
	return false;
}

void GameState::resetIteRoid(){
	iteRoid = this->leAsteroids.begin();
}

void GameState::resetIteBullet(){
	iteBull = this->leBullets.begin();
}

vector<Asteroid*>::iterator GameState::getIteRoid(){
	return iteRoid;
}

void GameState::setIteRoid(vector<Asteroid*>::iterator newIte){
	iteRoid = newIte;
}