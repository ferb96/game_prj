
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "bullet.h"

class Player: public Object
{
public:
	Player(int screenWidth, int screenHeight);
	void changeTrajectory(double addTraj);
	void setAccel(double accel);
	void setDecel(double decel);
	void setMaxVel(double vel);

	void updatePosition(int limitX, int limitY);
	void drawSelf(SDL_Renderer *rend);
	Bullet shoot();
private:
	double frontX; // The position where the gun is at
	double frontY;
	double accelMag; // Magnitude of acceleration, to be changed each time player press UP
	double decelMag; // Magnitude of deceleration, stay constant throughout the game
	double decelAmt; // Amount of deceleration to reach full stop
	double decelTraj; // Trajectory of deceleration, opposite to where player is sliding
	double maxVel; // Maximum velocity allowed
};

#endif /* PLAYER_H */