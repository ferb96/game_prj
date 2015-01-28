#include "bullet.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "const.h"
#include <cmath>

Bullet::Bullet(double x_pos, double y_pos, double traj, double iVel, int bulletLife) 
	: Object(x_pos, y_pos, traj, iVel)
{
	bulletLifespan = bulletLife;
	spawnTime = SDL_GetTicks();
	this->setHitRad(BULLET_RADIUS);
}

void Bullet::drawSelf(SDL_Renderer* rend) {
	// Bullet shape is always a filled circle
	filledCircleRGBA(rend, x, y, BULLET_RADIUS, 0xFF, 0xFF, 0xFF, 255);
}

bool Bullet::isExpired() {
	int currentTime = SDL_GetTicks();
	// Checks to see if the bullet has survived longer than its lifespan would allow
	bool expired = (currentTime > spawnTime + bulletLifespan);
	return expired;
}