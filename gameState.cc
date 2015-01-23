#include "gameState.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
using namespace std;

GameState::GameState(){
	iteRoid = leAsteroids.begin();
	iteBull = leBullets.begin();
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