#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

class Object
{
public:
	// Constructor
	Object(double x_pos, double y_pos, double trajM, double iVel);

	// Returns the object's x-coordinate
	double getX() const;
	// Returns the object's y-coordinate
	double getY() const;
	// Returns the object's trajectory
	double getTrajectoryM() const;
	// Returns the object's current velocity
	double getVel() const;
	// Returns the object's hit radius
	int getHitRad() const;
	double getMovX() const;
	double getMovY() const;


	// Sets the object's x-coordinate
	void setX(double newX);
	// Sets the object's y-coordinate
	void setY(double newY);
	// Sets the object's trajectory
	void setTrajectoryM(double newTraj);
	// Sets the object's velocity
	void setVel(double newXVel);
	// Sets the object's hit radius
	void setMovX(double newMovX);

	void setMovY(double newMovY);

	void setHitRad(int newHitRad);
	// Draws the object; blank in this definition
	void drawSelf(SDL_Renderer* rend);
	void updatePosition();

protected:
	
	double x; // Object's current x-coordinate
	double y; // Object's current x-coordinate
	double trajectoryM; // Object's current trajectory
	double vel; // Object's current velocity 
	int hitRad; // Object's hit radius
	double movX;
	double movY;
};

#endif /* OBJECT_H */