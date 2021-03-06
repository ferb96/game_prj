#include "asteroid.h"
#include "object.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "poof.h"
#include "const.h"
using namespace std;

Asteroid::Asteroid(double x, double y, double traj, double iVel, int iLevel)
	: Object(x, y, traj, iVel)
	{
		hitRad = ASTEROID_INITIAL_RADIUS;
		level = iLevel;
		/* When an asteroid is split, its "children" inherit half of its radius. A level 0
		 * asteroid will have a radius of ASTEROID_RADIUS. A level 1 asteroid will have  half that,
		 * and a level 2 will have one quarter */
		for (int i = 1; i <= level; i++) {
			hitRad = hitRad / 2;
		}
		vel = iVel;
		// "type" will be randomly assigned to 0, 1, 2, or 3, representing the four asteroid types
		type = rand() % 4;

	}

double Asteroid::getLevel() const {
	return level;
}

double Asteroid::getVel() const {
	return vel;
}

void Asteroid::setLevel(double newLevel) {
	level = newLevel;
}

void Asteroid::drawSelf(SDL_Renderer *rend) {
	// The asteroid draws itself according to its type
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
}
vector<Poof*> Asteroid::goBoom() {
	// Randomly determines the number of particles to make
	int num = (rand() % 4) + 4;
	vector<Poof*> boom;
	for (int i = 0; i < num; i ++) {
		// Creates the appropriate number of poofs with random trajectories and velocities
		Poof* zoom = new Poof(x, y, (rand() % 100 + 1) * 1.0 / 100 * M_PI*2, ((rand() % 4) + 5), POOF_LIFESPAN);
		boom.push_back(zoom);
	}
	return boom;
}

	//circleRGBA(rend, x, y, hitRad, 0xFF, 0xFF, 0xFF, 255);
