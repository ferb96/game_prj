#include "object.h"


Object::Object(double x_pos, double y_pos, double traj, double iVelX, double iVelY) {

	x = x_pos;
	y = y_pos;
	trajectory = traj;
	velX = iVelX;
	velY = iVelY;
	hitRad = 0;
}

double Object::getX() const {
	return x;
}
double Object::getY() const {
	return y;
}
double Object::getTrajectory() const {
	return trajectory;
}

double Object::getVelX() const {
	return velX;
}

double Object::getVelY() const {
	return velY;
}

int Object::getHitRad() const {
	return hitRad;
}

void Object::setX(double newX) {
	x = newX;
}

void Object::setY(double newY) {
	y = newY;
}

void Object::setTrajectory(double newTraj) {
	trajectory = newTraj;
}

void Object::setVelX(double newVel){
	velX = newVel; 
}

void Object::setVelY(double newVel){
	velY = newVel; 
}

void Object::setHitRad(int newHitRad){
	hitRad = newHitRad;
}

void Object::updatePosition(int limitX, int limitY) {
	// Update position based on velocity
	x += velX;
	y += velX;

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


