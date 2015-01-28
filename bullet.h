#include <SDL2/SDL.h>
#include "object.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public Object
{
public:
	// Constructor
	Bullet(double x_pos, double y_pos, double traj, double iVel, int bulletLife);
	// Draws the bullet model (a tiny filled circle)
	void drawSelf(SDL_Renderer* rend);
	// Determines whether or not a bullet has expired
	bool isExpired();
private:
	// The time at which the bullet was created
	int spawnTime;
	// The amount of time for which a bullet is allowed to exist
	int bulletLifespan;
};

#endif /* BULLET_H */