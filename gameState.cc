#include "gameState.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
#include "const.h"
#include <cmath>
using namespace std;

GameState::GameState(){
	Player* lePlayer = new Player(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2, PLAYER_LIVES);
	lePlayer->setDecel(PLAYER_DECELERATION);
	addPlayer(lePlayer);
	iteRoid = leAsteroids.begin();
	iteBull = leBullets.begin();
	level = 0;
	minRoid = 4;
	maxRoid = 6;
	roidMinSpd = .5;
	roidMaxSpd = 1.5;
}

void GameState::initLevel(){
	level++;
	if (level % 5 == 0 && level != 1){
		maxRoid++;
		minRoid++;
	}
	if (roidMaxSpd < ASTEROID_MAX_SPD && level != 1){
		roidMinSpd += ASTEROID_MAX_SPD/18;
		roidMaxSpd += ASTEROID_MAX_SPD/15;
	}
	cout << "minspd =" << roidMinSpd << " maxspd=" << roidMaxSpd << endl;

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
		Asteroid* roid = new Asteroid(roidX, roidY, roidTraj, roidSpd, ASTEROID_INITIAL_RADIUS, 0);
		addAsteroid(roid);
		cout << "adding a roid at x=" << roidX << " y=" << roidY << " traj=" << roidTraj << " spd=" << roidSpd << endl;
	}
}

void GameState::splitAsteroid(Asteroid* roid){
	delAsteroid();
	if (roid->getLevel() < 2){
		Asteroid* newroid1 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() + M_PI/6, roid->getVel() + .5, 50, roid->getLevel()+1);
		Asteroid* newroid2 = new Asteroid(roid->getX(), roid->getY(), roid->getTrajectory() - M_PI/6, roid->getVel() + .5, 50, roid->getLevel()+1);
		addAsteroid(newroid1);
		addAsteroid(newroid2);
	}
	resetIteRoid();
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

bool GameState::zeroAsteroid(){
	return (leAsteroids.size() == 0);
}

int GameState::getLevel(){
	return level;
}