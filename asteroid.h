#ifndef ASTEROID_H
#define ASTEROID_H

#include "object.h"
#include <SDL2/SDL.h>
#include "poof.h"
#include <vector>
using namespace std;

class Asteroid: public Object {

public:
	// Constructor
	Asteroid(double x, double y, double traj, double iVel, int iLevel);
	// Returns the asteroid's level, either 0, 1 or 2
	double getLevel() const;
	// Returns the asteroid's velocity
	double getVel() const;
	// Sets the asteroid's velocity
	void setLevel(double newLevel);
	// Draws the asteroid model based on the "type" data member
	void drawSelf(SDL_Renderer *rend);
	// Creates a vector of "Poof" objects that fly in random directions, simulating an explosion
	vector<Poof*> goBoom();

private:
	int level; // The "level" of the asteroid, based on how many times it has been split
	double vel; // The total velocity of the asteroid
	int type; // The "type" determines which asteroid model drawSelf will animate
};

#endif /* ASTEROID_H */
