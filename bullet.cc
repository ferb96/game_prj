#include "bullet.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"

Bullet::Bullet(double x_pos, double y_pos, double traj) 
	: Object(x_pos, y_pos, traj, 0.0, 0.0)
{
}

void Bullet::drawSelf(SDL_Renderer* rend) {
	pixelRGBA(rend, x, y, 0xFF, 0xFF, 0xFF, 255);
}