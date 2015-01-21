

Object::Object(int x_pos, int y_pos, double traj, int xv, int yv) {
	x = x_pos;
	y = y_pos;
	trajectory = traj;
	xVel = xv;
	yVel = yv;
	hitRad = 0;
}


int Object::getX() const {
	return x;
}

int Object::getY() const {
	return y;
}
double Object::getTrajectory() const {
	return trajectory;
}

double Object::getXVel() const {
	return xVel;
}

double Object::getYVel() const {
	return YVel;
}

double Object::getHitRad() const {
	return hitRad;
}

void Object::setX(int newX) {
	x = newX;
}

void Object::setY(int newY) {
	y = newY;
}

void Object::setTrajectory(double newTraj) {
	trajectory = newTraj;
}

void Object::setXVel(int newXVel){
	xVel = newXVel; 
}

void Object::setYVel(int newYVel){
	yVel = newYVel; 
}

void Object::setHitRad(int newHitRad){
	hitRad = newHitRad;
}

void Object::updatePosition() {
	x += xVel;
	y += yVel;
}

