
#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "object.h"

class Bullet : public Object
{
public:
	Bullet(double x_pos, double y_pos, double traj);
	void drawSelf(SDL_Renderer* rend);
};

#endif /* BULLET_H */