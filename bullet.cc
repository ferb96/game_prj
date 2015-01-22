#include "bullet.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <cmath>

Bullet::Bullet(double x_pos, double y_pos, double traj, double iVel, double bulletReach) 
	: Object(x_pos, y_pos, traj, iVel)
{
	firedX = x_pos;
	firedY = y_pos;
	reach = bulletReach;
}

void Bullet::drawSelf(SDL_Renderer* rend) {
	pixelRGBA(rend, this->x, this->y, 0xFF, 0xFF, 0xFF, 255);
}

bool Bullet::isExpired() {
	double xDist = abs(x - firedX); // Calculates the difference in x values
	double yDist = abs(y - firedY); // Calculates the difference in y values
	/* Finds the total linear distance between the bullet object and its 
	point of origin. Pythagorean theorem: c = sqrt((a*a) + (b*b)) */
	double distance = sqrt((xDist * xDist) + (yDist * yDist)); 
	/* The boolean "expired" is initialized true if the bullet is far enough 
	away from its point of origin */
	bool expired = (distance > reach);
	return expired;
}