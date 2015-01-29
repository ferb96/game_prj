#include "gameState.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
#include "const.h"
#include "poof.h"
#include <cmath>
#include <cassert>
using namespace std;

GameState::GameState(){
	lePlayer = NULL;
	iteRoid = leAsteroids.begin();
	iteBull = leBullets.begin();
	level = 0;
	minRoid = 2;
	maxRoid = 4;
	roidMinSpd = .5;
	roidMaxSpd = 1.5;
}

void GameState::initLevel(){
	level++;
	if (level % 3 == 0 && level != 1){
		maxRoid++;
		minRoid++;
	}
	if (roidMaxSpd < ASTEROID_MAX_SPD && level != 1){
		roidMinSpd += ASTEROID_MAX_SPD/18;
		roidMaxSpd += ASTEROID_MAX_SPD/15;
	}

	Player* lePlayer = getPlayer();
	//generating Asteroids
	int numberOfRoids = rand() % (maxRoid - minRoid + 1);
	numberOfRoids += minRoid;
	for (int i = 0; i < numberOfRoids; i++){
		double roidX;
		double roidY;
		double distanceFromPlayer;
		do {
			roidX = (rand() % 100 + 1) * 1.0 / 100 * WINDOW_SIZE_X;
			roidY = (rand() % 100 + 1) * 1.0 / 100 * WINDOW_SIZE_Y;
			distanceFromPlayer = sqrt( pow(roidX - lePlayer->getX(), 2) + pow(roidY - lePlayer->getY(), 2) );
		} while (distanceFromPlayer < SAFETY_ZONE);
		double roidTraj = (rand() % 100 + 1) * 1.0 / 100 * M_PI*2;
		double roidSpd = (rand() % 100 + 1) * 1.0 / 100 * (roidMaxSpd - roidMinSpd) + roidMinSpd;
		Asteroid* roid = new Asteroid(roidX, roidY, roidTraj, roidSpd, 0);
		addAsteroid(roid);
	}
}

void GameState::splitAsteroid(Asteroid*& roid){
	if (roid != NULL){
		delAsteroid();
		if (roid->getLevel() < 2){
			Asteroid* newroid1 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() + M_PI/6, roid->getVel() + .5, roid->getLevel()+1);
			Asteroid* newroid2 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() - M_PI/6, roid->getVel() + .5, roid->getLevel()+1);
			addAsteroid(newroid1);
			addAsteroid(newroid2);
		}
		destroyAsteroid(roid);
		resetIteRoid();
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

void GameState::addPoofs(vector<Poof*> newPoofs){
	for (int i = 0; i < newPoofs.size(); i++) {
		lePoofs.push_back(newPoofs[i]);
	}
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

void GameState::delPoof(){
	if (itePoof != lePoofs.begin()){
		itePoof = lePoofs.erase(itePoof-1);
	}
	else
		cout << "Error: deleting nonexistent poof" << endl;
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

Poof* GameState::getPoof(){
	Poof* tmp = *itePoof;
	itePoof++;
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

bool GameState::noMorePoof(){
	if (itePoof == lePoofs.end())
		return true;
	return false;
}

void GameState::resetIteRoid(){
	iteRoid = this->leAsteroids.begin();
}

void GameState::resetIteBullet(){
	iteBull = this->leBullets.begin();
}

void GameState::resetItePoof(){
	itePoof = this->lePoofs.begin();
}

bool GameState::zeroAsteroid(){
	return (leAsteroids.size() == 0);
}

int GameState::getLevel(){
	return level;
}

void GameState::destroyAsteroid(Asteroid*& roid){
	delete roid;
	roid = NULL;
}

void GameState::destroyBull(Bullet*& bull){
	delete bull;
	bull = NULL;
}

void GameState::destroyPoof(Poof*& poof){
	delete poof;
	poof = NULL;
}

void GameState::resetGameState(){
	// Delete all asteroids
	resetIteRoid();
	while ( !noMoreAsteroid() ){
		Asteroid* roid = getAsteroid();
		delAsteroid();
		destroyAsteroid(roid);
	}
	resetIteRoid();

	// Delete all bullets
	resetIteBullet();
	while ( !noMoreBullet() ){
		Bullet* bull = getBullet();
		delBullet();
		destroyBull(bull);
	}
	resetIteBullet();

	// Delete all Poofs
	resetItePoof();
	while ( !noMorePoof() ){
		Poof* poof = getPoof();
		delPoof();
		destroyPoof(poof);
	}
	resetItePoof();

	if (lePlayer != NULL){
		delete lePlayer;
		lePlayer = NULL;
	}

	if (lePlayer == NULL){
		Player* newPlayer = new Player(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2, PLAYER_LIVES);
		newPlayer->setDecel(PLAYER_DECELERATION);
		addPlayer(newPlayer);
	}
}