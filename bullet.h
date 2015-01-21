#include <SDL2/SDL.h>
#include "object.cc"

#ifndef BULLET_H
#define BULLET_H

class Bullet: public Object
{
public:
	Bullet(int x_pos, int y_pos, double traj);
	void drawSelf(SDL_Renderer* rend);
};

#endif /* BULLET_H */