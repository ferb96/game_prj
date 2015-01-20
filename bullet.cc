#include "bullet.h"
#include <SDL2/SDL.h>

Bullet::Bullet(int x_pos, int y_pos, double traj) {
	x = x_pos;
	y = y_pos;
	trajectory = traj;
	speed = 0;
	hitRad = 0;
}

void Bullet::drawSelf(SDL_Renderer* rend) {
	pixelRGBA(rend
			x, y
			0xFF, 0xFF, 0xFF, 255);
}