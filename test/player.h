
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "bullet.h"

class Player: public Object
{
public:
	Player(int screenWidth, int screenHeight);
	void changeTrajectory(double addTraj);
	void changeSpeed(double accel);

	void drawSelf(SDL_Renderer *rend);
	Bullet shoot();
private:
	double frontX;
	double frontY;
	double trajectoryF; // The facing trajectory, or the direction the player is currently facing
};

#endif /* PLAYER_H */