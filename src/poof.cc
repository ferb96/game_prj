#include "bullet.h"
#include "poof.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <cmath>

Poof::Poof(double x_pos, double y_pos, double traj, double iVel, int poofLife) 
	: Bullet(x_pos, y_pos, traj, iVel, poofLife)
{
}

void Poof::drawSelf(SDL_Renderer* rend) {
	pixelRGBA(rend, x, y, 0xFF, 0xFF, 0xFF, 255);
}
