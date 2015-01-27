#include <SDL2/SDL.h>
#include "object.h"
#include "bullet.h"

#ifndef POOF_H
#define POOF_H

class Poof : public Bullet
{
public:
	Poof(double x_pos, double y_pos, double traj, double iVel, int poofLife);
	void drawSelf(SDL_Renderer* rend);
};

#endif /* POOF_H */