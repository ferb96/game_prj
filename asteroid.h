#ifndef ASTEROID_H
#define ASTEROID_H

#include "object.h"
#include <SDL2/SDL.h>

class Asteroid: public Object {

public:
	Asteroid(double x, double y, double traj, double iVel, double level0Radius, int iLevel);

	double getLevel() const;
	double getVel() const;

	void setLevel(double newLevel);

	void drawSelf(SDL_Renderer *rend);

private:
	int level;
	double vel;
	int type;
};

#endif /* ASTEROID_H */
