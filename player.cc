#include <cmath>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "poof.h"
#include "const.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

Player::Player(double x_pos, double y_pos, int lives)
	: Object(x_pos, y_pos, 0.0, 0.0)
{
	// Sets the hit radius and size of the player model (see const.h)
	setHitRad(PLAYER_HIT_RADIUS);
	//The player never begins the game in motion
	accelMag = 0;
	decelMag = 0;
	decelAmt = 0.0;
	decelTraj = 0.0;
	livesLeft = lives;
	alive = true;
	invul = false;
}

void Player::changeTrajectory(double addTraj) {
	trajectory += addTraj;
	// Resets the trajectory if it makes a full circle
	if (trajectory > RADIAN_CIRCLE) // RADIAN_CIRCLE = 2 * M_PI, see const.h
		trajectory -= RADIAN_CIRCLE;
	else if (trajectory < 0)
		trajectory += RADIAN_CIRCLE;
}

bool Player::isAlive(){
	return alive;
}
bool Player::isInvul(){
	return invul;
}
void Player::setAlive(bool state){
	alive = state;
}
void Player::setInvul(bool state){
	invul = state;
}
void Player::minusOneLife(){
	livesLeft -= 1;
}
void Player::oneUp(){
	livesLeft += 1;
}
int Player::getLivesLeft(){
	return livesLeft;
}

void Player::setAccel(double accel) {
	accelMag = accel;
}

void Player::setDecel(double decel) {
	decelMag = decel;
}

void Player::resetPlayer(double x_pos, double y_pos){
	// The player always respawns at the center of the screen, facing up
	x = x_pos/2;
	y = y_pos/2;
	trajectory = 0.0;
	velX = 0;
	velY = 0;
	decelAmt = 0;
}

void Player::updatePosition(int limitX, int limitY){
	// Player acceleration
	double accelX = accelMag * sin(trajectory);
	double accelY = accelMag * cos(trajectory);

	// Player deceleration
	// Init the decel to be zero
	double decelX = 0;
	double decelY = 0;
	// If the player is accelerating, do not decelerate, but prepare the decelTraj and decelAmt accordingly
	if (accelMag != 0){
		double velTraj = M_PI / 2 - atan2(velY,velX);
		decelTraj = velTraj + M_PI;
		decelAmt = sqrt(velX*velX + velY*velY);
	}
	// If the player is not accelerating, start to decelerate, decrease decelAmt over time till it reaches zero
	if (accelMag == 0 && decelAmt > 0){
		decelX = decelMag * sin(decelTraj);
		decelY = decelMag * cos(decelTraj);
		decelAmt -= sqrt(decelX*decelX + decelY*decelY);
	}
	// Making sure player reaches full stop by little trick
	if (decelAmt < 0){
		decelX = -velX;
		decelY = -velY;
	}

	// Modify velocity based on accel and decel
	velX += accelX + decelX;
	velY += accelY + decelY;

	// Update position based on velocity
	x += velX;
	y -= velY;

	// Screen wrap
	if (x < 0 - hitRad)
		x = limitX + hitRad;
	if (x > limitX + hitRad)
		x = 0 - hitRad;
	if (y < 0 - hitRad)
		y = limitY + hitRad;
	if (y > limitY + hitRad)
		y = 0 - hitRad;
}

void Player::drawSelf(SDL_Renderer *rend) {
	// calculates the front point
	frontX = x + PLAYER_FRONT_POINT_DISTANCE * sin(trajectory);
	frontY = y - PLAYER_FRONT_POINT_DISTANCE * cos(trajectory);

	// calculates the right point
	double nextAngle = trajectory + THIRD_OF_CIRCLE;
	double rightX = x + PLAYER_SIDE_POINT_DISTANCE * sin(nextAngle);
	double rightY = y - PLAYER_SIDE_POINT_DISTANCE * cos(nextAngle);

	// calculates the left point
	nextAngle = trajectory - THIRD_OF_CIRCLE;
	double leftX = x + PLAYER_SIDE_POINT_DISTANCE * sin(nextAngle);
	double leftY = y - PLAYER_SIDE_POINT_DISTANCE * cos(nextAngle);

	double baseMidX = ((rightX + leftX) / 2.0) + .5;
	double baseMidY = ((rightY + leftY) / 2.0) + .5;

	// draws the triangle
	trigonRGBA(rend,
               	int(frontX + .5), int(frontY + .5), // x y of first vertex
                int(rightX + .5), int(rightY + .5), // x y of second vertex
                int(leftX + .5), int(leftY + .5), // x y of third vertex
                0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
	// draws the center line
	lineRGBA(rend,
				int(frontX + .5), int(frontY + .5),
				int(baseMidX), int(baseMidY),
				0xFF, 0xFF, 0xFF, 255);

	if (accelMag > 0) { // AKA if the player is accelerating / holding the front arrow
		// Calculates the base points of the exhaust triangle
		double leftMidX = ((baseMidX + leftX) / 2.0);
		double leftMidY = ((baseMidY + leftY) / 2.0);
		double rightMidX = ((baseMidX + rightX) / 2.0);
		double rightMidY = ((baseMidY + rightY) / 2.0);
		// Calcualates the final endpoint
		double exhaustLen = sqrt(((leftX - rightX) * (leftX - rightX)) + ((leftY - rightY) * (leftY - rightY))) / 3;
		double centerToBase = sqrt(((x - baseMidX) * (x - baseMidX)) + ((y - baseMidY) * (y - baseMidY)));
		double totalDist = exhaustLen + centerToBase;
		double exhaustTraj = (2 * M_PI) - trajectory;
		double exhaustX = totalDist * (sin(exhaustTraj)) + x;
		double exhaustY = totalDist * (cos(exhaustTraj)) + y;
		/* Checks the current time before drawing the exhaust triangle. This simple if/else statement
		 * creates the "flickering" exhause flame effect */
		if (SDL_GetTicks() % 2 == 0) { // Draws the shorter triangle
			trigonRGBA(rend,
        	       	int(leftMidX + .5), int(leftMidY + .5), // x y of first vertex
        	        int(rightMidX + .5), int(rightMidY + .5), // x y of second vertex
        	        int(exhaustX + .5), int(exhaustY + .5), // x y of third vertex
        	        0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
		}
		else { // Draws the longer triangle
			totalDist = totalDist * EXHAUST_VARIABILITY;
			double exhaustX = totalDist * (sin(exhaustTraj)) + x;
			double exhaustY = totalDist * (cos(exhaustTraj)) + y;
			trigonRGBA(rend,
        	       	int(leftMidX + .5), int(leftMidY + .5), // x y of first vertex
        	        int(rightMidX + .5), int(rightMidY + .5), // x y of second vertex
        	        int(exhaustX + .5), int(exhaustY + .5), // x y of third vertex
        	        0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
		}
		
	}
	
}

Bullet* Player::shoot(double bulletSpeed, double bulletReach) {
	// Uses the pythagorean theorem to calculate total player velocity from x/y components
	double bulletTraj = trajectory; // The new bullet's trajectory is the direction the player is facing
	// The x and y components of the bullet's velocity
	double finalX = velX + bulletSpeed * (sin(bulletTraj));
	double finalY = velY + bulletSpeed * (cos(bulletTraj));
	// The magnitude of the bullet velocity
	double finalSpeed = sqrt((finalX * finalX) + (finalY * finalY));
	double finalAlpha = (M_PI / 2) - atan2(finalY,finalX);

	// Creates a bullet object inheriting that velocity
	Bullet* newBullet = new Bullet(frontX, frontY, finalAlpha, finalSpeed, bulletReach);
	return newBullet;
}

vector<Poof*> Player::goBoom() {
	// Randomly determines the number of particles to make
	int num = (rand() % 8) + 20;
	// Creates the vector
	vector<Poof*> boom;
	// Creates the appropriate number of poofs with random trajectories and velocities
	for (int i = 0; i < num; i ++) {
		Poof* zoom = new Poof(x, y, (rand() % 100 + 1) * 1.0 / 100 * M_PI*2, ((rand() % 4) + 5), POOF_LIFESPAN * 3);
		boom.push_back(zoom);
	}
	return boom;
}
