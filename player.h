
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "bullet.h"

class Player: public Object
{
public:
	// Constructs a player at the center of a screen of the given proportions
	Player(double x_pos, double y_pos);
	// Turns the player left(addTraj is negative) or right (addTraj is positive)
	void changeTrajectory(double addTraj);
	void setAccel(double accel);
	void setDecel(double decel);

	// Ubdates player position based on velocity. Also calculates deceleration.
	void updatePosition(int limitX, int limitY);
	// Draws the player at his/her current position, with trajectory fiven by the data members
	void drawSelf(SDL_Renderer *rend);
	// Creates a new bullet object at the position of the player's "front" point, held in the data members 
	Bullet* shoot(double bulletSpeed, double bulletReach);
private:
	double frontX; // The position where the gun is at
	double frontY;
	double accelMag; // Magnitude of acceleration, to be changed each time player press UP
	double decelMag; // Magnitude of deceleration, stay constant throughout the game
	double decelAmt; // Amount of deceleration to reach full stop
	double decelTraj; // Trajectory of deceleration, opposite to where player is sliding
};

#endif /* PLAYER_H */