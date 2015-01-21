#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "player.h"
#include "bullet.h"
#include "object.h"

Player::Player(int screenWidth, int screenHeight)
	: Object(screenWidth / 2, screenHeight / 2, 0.0, 0.0)
{
	/*x = screenWidth / 2;
	y = screenHeight / 2;
	trajectory = 0;
	xVel = 0;
	yVel = 0; */
	Object::setHitRad(30);
	const double RADIAN_QUARTER = M_PI / 2;
	const double DIST_FROM_CENTER = hitRad * (4 / 3);
	double pointTheta = RADIAN_QUARTER - trajectoryF;
	frontX = (DIST_FROM_CENTER * (cos(pointTheta))) + x;
	frontY = (DIST_FROM_CENTER * (sin(pointTheta))) + y;
}

void Player::changeTrajectory(double addTraj) {
	const double RADIAN_CIRCLE = 2 * M_PI;
	trajectoryF += addTraj;
	if (trajectoryF > RADIAN_CIRCLE)
		trajectoryF -= RADIAN_CIRCLE;
	else if (trajectoryF < 0)
		trajectoryF += RADIAN_CIRCLE;
}

void Player::changeSpeed(double accel) {
	double currentMovX = vel * movX;
	double currentMovY = vel * movY;
	const double RADIAN_QUARTER = M_PI / 2;
	const double RADIAN_CIRCLE = 2 * M_PI;
	double accelTheta = RADIAN_QUARTER - trajectoryF;
	double accelX = accel * (cos(accelTheta));
	double accelY = accel * (sin(accelTheta));
	double newMovX = currentMovX + accelX;
	double newMovY = currentMovY + accelY;
	trajectoryM = (RADIAN_QUARTER - (atan(newMovY / newMovX)));
	vel = sqrt((newMovX * newMovX) + (newMovY * newMovY));
	if (vel > 10)
		vel = 10;
	if (trajectoryM > RADIAN_CIRCLE)
		trajectoryM -= RADIAN_CIRCLE;
	else if (trajectoryM < 0)
		trajectoryM += RADIAN_CIRCLE;
	double trajTheta = RADIAN_QUARTER - trajectoryM;
	movX = cos(trajTheta);
	movY = sin(trajTheta);


	//if (accel == 0 && xVel != 0 && yVel != 0)
	//	accel = -2;
	/*const double RADIAN_QUARTER = M_PI / 2;
	double accelTheta = RADIAN_QUARTER - trajectory;
	xVel += accel * (cos(accelTheta));
	yVel += accel * (sin(accelTheta));

	double velvel = sqrt(xVel*xVel + yVel*yVel)
	if (velvel > 10)
		xVel = 10;
	if (yVel > 10)
		yVel = 10;
	if (xVel < -10)
		xVel = -10;
	if (yVel < -10)
		yVel = -10;*/

}

void Player::drawSelf(SDL_Renderer *rend) {
	const double RADIAN_CIRCLE = 2 * M_PI;
	const double RADIAN_QUARTER = M_PI / 2;
	const double DIST_FROM_CENTER = this->getHitRad() * (4 / 3);
	double ptraj = trajectoryM + RADIAN_CIRCLE / 3;

	double pointTheta = RADIAN_QUARTER - trajectoryF;
	frontX = (DIST_FROM_CENTER * (cos(pointTheta))) + x;
	frontY = (DIST_FROM_CENTER * (sin(pointTheta))) + y;

	int drawFrontX = frontX + .5;
	int drawFrontY = frontY + .5;

	pointTheta = RADIAN_QUARTER - ptraj;
	int rightX = ((DIST_FROM_CENTER * (cos(pointTheta))) + this->getX()) + .5;
	int rightY = ((DIST_FROM_CENTER * (sin(pointTheta))) + this->getY()) + .5;

	ptraj += RADIAN_CIRCLE / 3;

	pointTheta = RADIAN_QUARTER - ptraj;
	int leftX = ((DIST_FROM_CENTER * (cos(pointTheta))) + this->getX()) + .5;
	int leftY = ((DIST_FROM_CENTER * (sin(pointTheta))) + this->getY()) + .5;

	trigonRGBA(rend,
                 drawFrontX, drawFrontY, // x y of first vertex
                 rightX, rightY, // x y of second vertex
                 leftX, leftY, // x y of third vertex
                 0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
	
}

Bullet Player::shoot() {
	Bullet newBullet(frontX, frontY, trajectoryF);
	return newBullet;
}



