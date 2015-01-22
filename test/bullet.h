
#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "object.cc"

class Bullet
{
public:
	Bullet(int x_pos, int y_pos, double traj);
	void drawSelf(SDL_Renderer* rend);
};

#endif /* BULLET_H */