#include <SDL2/SDL.h>
#include "object.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public Object
{
public:
	Bullet(double x_pos, double y_pos, double traj, double iVel, double bulletReach);
	void drawSelf(SDL_Renderer* rend);
	bool isExpired();
private:
	int firedX;
	int firedY;
	double reach;
};

#endif /* BULLET_H */