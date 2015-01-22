#include "asteroid.h"
#include "object.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"

Asteroid::Asteroid(double x, double y, double traj, double iVel, double level0Radius, int iLevel)
	: Object(x, y, traj, iVel)
	{
		hitRad = level0Radius;
		level = iLevel;
		for (int i = 1; i <= level; i++) {
			hitRad = hitRad / 2;
		}
	}

double Asteroid::getLevel() const {
	return level;
}

void Asteroid::setLevel(double newLevel) {
	level = newLevel;
}

void Asteroid::drawSelf(SDL_Renderer *rend) {
	circleRGBA(rend, x, y, hitRad, 0xFF, 0xFF, 0xFF, 255);
}