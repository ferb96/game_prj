
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "bullet.h"
#include "poof.h"
#include <vector>
using namespace std;

class Player: public Object
{
public:
	// Constructs a player at the center of a screen of the given proportions
	Player(double x_pos, double y_pos, int lives);
	// Turns the player left(addTraj is negative) or right (addTraj is positive)
	void changeTrajectory(double addTraj);
	// Sets the acceleration
	void setAccel(double accel);
	// Sets the deceleration
	void setDecel(double decel);
	// Reset player's position n stuff
	void resetPlayer(double x_pos, double y_pos);
	// The player's state: alive or dead
	bool isAlive();
	// Checks whether or not the player is currently invulnerable
	bool isInvul();
	// Changes the player's state to "alive"
	void setAlive(bool state);
	// Changes the player's state to "invulnerable"
	void setInvul(bool state);
	// Subtracts one life from the player's life count 
	void minusOneLife();
	// Returns the number of lives the player has remaining
	int getLivesLeft();

	// Ubdates player position based on velocity. Also calculates deceleration.
	void updatePosition(int limitX, int limitY);
	// Draws the player at his/her current position, with trajectory fiven by the data members
	void drawSelf(SDL_Renderer *rend);
	// Creates a new bullet object at the position of the player's "front" point, held in the data members 
	Bullet* shoot(double bulletSpeed, double bulletReach);
	/* Creates a large number of collisionless "Poof" objects which fly out in every direction,
	 * mimicking an explosion */
	vector<Poof*> goBoom();
private:
	bool alive; // True if the player is alive
	bool invul; // True if the player is invulnerable
	int livesLeft; // Number of lives remaining. Starts at three.
	double frontX; // The position of the front point, or "gun"
	double frontY;
	double accelMag; // Magnitude of acceleration, to be changed each time player press UP
	double decelMag; // Magnitude of deceleration, stay constant throughout the game
	double decelAmt; // Amount of deceleration to reach full stop
	double decelTraj; // Trajectory of deceleration, opposite to where player is sliding
};

#endif /* PLAYER_H */