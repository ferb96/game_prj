#include "asteroid.h"
#include "object.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Asteroid::Asteroid(double x, double y, double traj, double iVel, double level0Radius, int iLevel)
	: Object(x, y, traj, iVel)
	{
		hitRad = level0Radius;
		level = iLevel;
		for (int i = 1; i <= level; i++) {
			hitRad = hitRad / 2;
		}
		vel = iVel;
		type = rand() % 4;

	}

double Asteroid::getLevel() const {
	return level;
}

void Asteroid::setLevel(double newLevel) {
	level = newLevel;
}

void Asteroid::drawSelf(SDL_Renderer *rend) {
	if(type == 0) {
		lineRGBA(rend,
					(x - hitRad), (y - (hitRad / 5)),
					(x - hitRad), (y + (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - hitRad), (y + (hitRad / 5)),
					(x - ((2 * hitRad) / 5)), (y + (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
				(x - ((2 * hitRad) / 5)), (y + (hitRad / 5)),
				(x - ((2 * hitRad) / 5)), (y + ((3 * hitRad)/ 5)),
				0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y + ((3 * hitRad)/ 5)),
					x, y + hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, y + hitRad,
					(x + ((2 * hitRad) / 5)), y + hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((2 * hitRad) / 5)), y + hitRad,
					(x + ((3 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					(x + ((3 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					(x + hitRad), y,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + hitRad), y,
					(x + ((4 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((4 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					(x + (hitRad / 5)), (y - hitRad),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + (hitRad / 5)), (y - hitRad),
					(x - ((2 * hitRad) / 5)), (y - hitRad),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y - hitRad),
					(x - ((4 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					(x - hitRad), (y - (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
	}
	else if(type == 1) {
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), y,
					x - hitRad, (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x - hitRad, (y + ((2 * hitRad)/ 5)),
					(x - ((2 * hitRad) / 5)), y + hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), y + hitRad,
					x, (y + ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, (y + ((3 * hitRad)/ 5)),
					(x + ((4 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((4 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					x + hitRad, (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x + hitRad, (y + ((2 * hitRad)/ 5)),
					(x + ((2 * hitRad) / 5)), y,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((2 * hitRad) / 5)), y,
					(x + ((4 * hitRad) / 5)), (y - ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((4 * hitRad) / 5)), (y - ((2 * hitRad)/ 5)),
					x + hitRad, (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x + hitRad, (y - ((4 * hitRad)/ 5)),
					(x + ((2 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((2 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					(x + ((2 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((2 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					x, (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, (y - ((3 * hitRad)/ 5)),
					(x - ((2 * hitRad) / 5)), y - hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), y - hitRad,
					x - hitRad, (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x - hitRad, (y - ((3 * hitRad)/ 5)),
					(x - ((4 * hitRad) / 5)), y,
					0xFF, 0xFF, 0xFF, 255);

	}
	else if (type == 2) {
		lineRGBA(rend,
					(x - ((6 * hitRad) / 5)), y,
					(x - ((4 * hitRad) / 5)), (y + (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), (y + (hitRad / 5)),
					(x - ((2 * hitRad) / 5)), (y + (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y + (hitRad / 5)),
					(x - ((4 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					(x - (hitRad / 5)), (y + ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - (hitRad / 5)), (y + ((3 * hitRad)/ 5)),
					x, y + hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, y + hitRad,
					(x + ((3 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y + ((4 * hitRad)/ 5)),
					x + hitRad, (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x + hitRad, (y + ((2 * hitRad)/ 5)),
					(x + ((6 * hitRad) / 5)), y,
					0xFF, 0xFF, 0xFF, 255);

		lineRGBA(rend,
					(x - ((6 * hitRad) / 5)), y,
					(x - ((4 * hitRad) / 5)), (y - (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), (y - (hitRad / 5)),
					(x - ((2 * hitRad) / 5)), (y - (hitRad / 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y - (hitRad / 5)),
					(x - ((4 * hitRad) / 5)), (y - ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((4 * hitRad) / 5)), (y - ((2 * hitRad)/ 5)),
					(x - (hitRad / 5)), (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - (hitRad / 5)), (y - ((3 * hitRad)/ 5)),
					x, y - hitRad,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, y - hitRad,
					(x + ((3 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					x + hitRad, (y - ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x + hitRad, (y - ((2 * hitRad)/ 5)),
					(x + ((6 * hitRad) / 5)), y,
					0xFF, 0xFF, 0xFF, 255);

	}
	else if(type == 3) {
		lineRGBA(rend,
					x - hitRad, (y + (hitRad/ 5)),
					(x - ((2 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					(x - (hitRad / 5)), (y + ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - (hitRad / 5)), (y + ((4 * hitRad)/ 5)),
					(x + (hitRad / 5)), (y + ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + (hitRad / 5)), (y + ((4 * hitRad)/ 5)),
					(x + ((3 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y + ((2 * hitRad)/ 5)),
					x + hitRad, y,
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x + hitRad, y,
					(x + ((3 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + ((3 * hitRad) / 5)), (y - ((4 * hitRad)/ 5)),
					(x + (hitRad / 5)), (y - ((4 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x + (hitRad / 5)), (y - ((4 * hitRad)/ 5)),
					x, (y - ((6 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x, (y - ((6 * hitRad)/ 5)),
					(x - ((2 * hitRad) / 5)), (y - ((6 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((2 * hitRad) / 5)), (y - ((6 * hitRad)/ 5)),
					(x - ((3 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					(x - ((3 * hitRad) / 5)), (y - ((3 * hitRad)/ 5)),
					x - hitRad, (y - ((2 * hitRad)/ 5)),
					0xFF, 0xFF, 0xFF, 255);
		lineRGBA(rend,
					x - hitRad, (y - ((2 * hitRad)/ 5)),
					x - hitRad, (y + (hitRad/ 5)),
					0xFF, 0xFF, 0xFF, 255);
	}

	//circleRGBA(rend, x, y, hitRad, 0xFF, 0xFF, 0xFF, 255);
}