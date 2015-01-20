#include <SDL2/SDL.h>

class Object
{
public:
	// Constructor
	Object(int x_pos, int y_pos, double traj, int spd);

	// Returns the object's x-coordinate
	int getX() const;
	// Returns the object's y-coordinate
	int getY() const;
	// Returns the object's trajectory
	double getTrajectory() const;
	// Returns the object's current x-velocity
	int getXVel() const;
	// Returns the object's current y-velocity
	int getYVel() const;
	// Returns the object's hit radius
	int getHitRad() const;

	// Sets the object's x-coordinate
	void setX(int newX);
	// Sets the object's y-coordinate
	void setY(int newY);
	// Sets the object's trajectory
	void setTrajectory(newTraj);
	// Sets the object's x-velocity
	void setXVel(newXVel);
	// Sets the object's y-velocity
	void setYVel(newYVel);
	// Sets the object's hit radius
	void setHitRad(int newHitRad)
	// Draws the object; blank in this definition
	void drawSelf(SDL_Renderer* rend);

protected:
	void updatePosition();
	int x; // Object's current x-coordinate
	int y; // Object's current x-coordinate
	double trajectory; // Object's current trajectory
	int xVel; // Object's current y-velocity
	int yVel // Object's current x-velocity
	int hitRad; // Object's hit radius
}