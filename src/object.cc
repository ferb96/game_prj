#include "object.h"
#include <iostream>
#include <cmath>
using namespace std;

Object::Object(double x_pos, double y_pos, double traj, double iVel) {

	x = x_pos;
	y = y_pos;
	trajectory = traj;
	hitRad = 0;
	// Breaks the initial velocity into its x and y components
	velX = iVel * sin(trajectory);
	velY = iVel * cos(trajectory);
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
	this->x += velX;
	this->y -= velY;

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

bool Object::checkCollision(Object* incoming) {
	double xDist = x - incoming->getX(); // Calculates the difference in x values
	double yDist = y - incoming->getY(); // Calculates the difference in y values
	/* Finds the total linear distance between the first object and the 
	second. Pythagorean theorem. c = sqrt((a*a) + (b*b)) */
	double distance = sqrt((xDist * xDist) + (yDist * yDist)); 
	/* The boolean "collide" is initialized true if the objects' centerpoints are 
	close enough to warrant a collision. */
	bool collide = (distance <= hitRad + incoming->getHitRad());
	return collide;
}

