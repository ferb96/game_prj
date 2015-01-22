#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

class Object
{
public:
	// Constructor
	Object(double x_pos, double y_pos, double traj, double iVel);

	// Returns the object's x-coordinate
	double getX() const;
	// Returns the object's y-coordinate
	double getY() const;
	// Returns the object's trajectory
	double getTrajectory() const;
	// Returns the object's current velocity
	double getVelX() const;

	double getVelY() const;
	// Returns the object's hit radius
	int getHitRad() const;

	// Sets the object's x-coordinate
	void setX(double newX);
	// Sets the object's y-coordinate
	void setY(double newY);
	// Sets the object's trajectory
	void setTrajectory(double newTraj);
	// Sets the object's velocity
	void setVelX(double newVel);
	// Sets the object's velocity
	void setVelY(double newVel);
	// Sets the object's hit radius
	void setHitRad(int newHitRad);
	// Draws the object; blank in this definition
	void drawSelf(SDL_Renderer* rend);
	// Update its own positions
	void updatePosition(int limitX, int limitY);
	// Checks for a collision with the given object
	bool checkCollision(Object incoming);

protected:
	
	double x; // Object's current x-coordinate
	double y; // Object's current x-coordinate
	double trajectory; // Object's current trajectory
	double velX; // Object's current velocity 
	double velY;
	int hitRad; // Object's hit radius
};

#endif /* OBJECT_H */