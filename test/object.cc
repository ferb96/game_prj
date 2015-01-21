#include "object.h"


Object::Object(double x_pos, double y_pos, double trajM, double iVel) {

	x = x_pos;
	y = y_pos;
	trajectoryM = trajM;
	vel = iVel;
	const double RADIAN_QUARTER = M_PI / 2;
	double trajTheta = RADIAN_QUARTER - trajectoryM;
	movX = cos(trajTheta);
	movY = sin(trajTheta);
	hitRad = 0;
}

double Object::getX() const {
	return x;
}
double Object::getY() const {
	return y;
}
double Object::getTrajectoryM() const {
	return trajectoryM;
}

double Object::getVel() const {
	return vel;
}

double Object::getMovX() const {
	return movX;
}

double Object::getMovY() const {
	return movY;
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

void Object::setTrajectoryM(double newTraj) {
	trajectoryM = newTraj;
}

void Object::setVel(double newVel){
	vel = newVel; 
}

void Object::setMovX(double newMovX) {
	movX = newMovX;
}

void Object::setMovY(double newMovY) {
	movY = newMovY;
}

void Object::setHitRad(int newHitRad){
	hitRad = newHitRad;
}

void Object::updatePosition() {
	//const double RADIAN_QUARTER = M_PI / 2;
	//double trajTheta = RADIAN_QUARTER - trajectoryM;
	//movX = cos(trajTheta);
	//movY = sin(trajTheta);
	x += vel * movX;
	y += vel * movY;
}


