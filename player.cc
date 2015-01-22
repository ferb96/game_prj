#include <cmath>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "player.h"
#include "bullet.h"
#include "object.h"

Player::Player(double x_pos, double y_pos)
	: Object(x_pos, y_pos, 0.0, 0.0)
{
	setHitRad(22);
	accelMag = 0;
	decelMag = 0;
	decelAmt = 0.0;
	decelTraj = 0.0;
}

void Player::changeTrajectory(double addTraj) {
	const double RADIAN_CIRCLE = 2 * M_PI;
	trajectory += addTraj;
	if (trajectory > RADIAN_CIRCLE)
		trajectory -= RADIAN_CIRCLE;
	else if (trajectory < 0)
		trajectory += RADIAN_CIRCLE;
}

void Player::setAccel(double accel) {
	accelMag = accel;
}

void Player::setDecel(double decel) {
	decelMag = decel;
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
	if (x < 0)
		x = limitX;
	if (x > limitX)
		x = 0;
	if (y < 0)
		y = limitY;
	if (y > limitY)
		y = 0;
}

void Player::drawSelf(SDL_Renderer *rend) {
	// calculate the front point
	frontX = x + 25 * sin(trajectory);
	frontY = y - 25 * cos(trajectory);

	// calculate the right point
	double nextAngle = trajectory + M_PI * 2/3;
	double rightX = x + 15 * sin(nextAngle);
	double rightY = y - 15 * cos(nextAngle);

	// calculate the left point
	nextAngle = trajectory - M_PI * 2/3;
	double leftX = x + 15 * sin(nextAngle);
	double leftY = y - 15 * cos(nextAngle);

	// draw the triangle
	trigonRGBA(rend,
               	int(frontX + .5), int(frontY + .5), // x y of first vertex
                int(rightX + .5), int(rightY + .5), // x y of second vertex
                int(leftX + .5), int(leftY + .5), // x y of third vertex
                0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
	
}

Bullet Player::shoot(double bulletSpeed, double bulletReach) {
	// Uses the pythagorean theorem to calculate total player velocity from x/y components
	const double RADIAN_QUARTER = M_PI / 2;
	double playerVel = sqrt((velX * velX) + (velY * velY));
	double playerTheta = RADIAN_QUARTER - (atan(velY / velX));
	double playerVectX = playerVel * (sin(playerTheta));
	double playerVectY = playerVel * (cos(playerTheta));
	double bulletTraj = trajectory; // The new bullet's trajectory is the direction the player is facing
	double bulletTheta = RADIAN_QUARTER - M_PI;
	double finalX = playerVectX + bulletSpeed * (sin(bulletTheta));
	double finalY = playerVectY + bulletSpeed * (cos(bulletTheta));
	double finalSpeed = sqrt((finalX * finalX) + (finalY * finalY));
	double finalTheta = atan(finalY / finalX);
	double finalAlpha = RADIAN_QUARTER - finalTheta;

	// Creates a bullet object inheriting that velocity
	Bullet newBullet(frontX, frontY, finalAlpha, finalSpeed, bulletReach);
	return newBullet;
}
