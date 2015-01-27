#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include "poof.h"
using namespace std;

class GameState
{
public:
	GameState();
	void initLevel();
	void splitAsteroid(Asteroid* roid);
	void addPlayer(Player* playa);
	void addAsteroid(Asteroid* roid);
	void addBullet(Bullet* bull);
	void addPoofs(vector<Poof*> newPoofs);
	void delAsteroid();
	void delBullet();
	void delPoof();
	Player* getPlayer();
	Asteroid* getAsteroid();
	Bullet* getBullet();
	Poof* getPoof();

	bool noMoreAsteroid();
	bool noMoreBullet();
	bool noMorePoof();
	void resetIteRoid();
	void resetIteBullet();
	void resetItePoof();

	bool zeroAsteroid();
	int getLevel();
private:
	vector<Asteroid*>::iterator iteRoid; // Asteroid iterator, pointing to current Asteroid object
	vector<Bullet*>::iterator iteBull; // Bullet iterator, pointing to current Bullet object
	vector<Poof*>::iterator itePoof;
	vector<Asteroid*> leAsteroids;
	vector<Bullet*> leBullets;
	vector<Poof*> lePoofs;
	Player* lePlayer;

	int level;
	int minRoid;
	int maxRoid;
	double roidMinSpd;
	double roidMaxSpd;
};

#endif /* GAMESTATE_H */