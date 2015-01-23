#include "bullet.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <cmath>

Bullet::Bullet(double x_pos, double y_pos, double traj, double iVel, int bulletLife) 
	: Object(x_pos, y_pos, traj, iVel)
{
	bulletLifespan = bulletLife;
	spawnTime = SDL_GetTicks();
}

void Bullet::drawSelf(SDL_Renderer* rend) {
	filledCircleRGBA(rend, x, y, 1, 0xFF, 0xFF, 0xFF, 255);
}

bool Bullet::isExpired() {
	int currentTime = SDL_GetTicks();
	bool expired = (currentTime > spawnTime + bulletLifespan);
	return expired;
}