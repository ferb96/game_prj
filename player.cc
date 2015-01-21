#include <vector>
#include <cmath>
#include "player.h"


Player::Player(int screenWidth, int screenHeight); {
	x = screenWidth / 2;
	y = screenHeight / 2;
	trajectory = 0;
	speed = 0;
	hitRad = 30;
	const int RADIAN_QUARTER = M_PI / 2;
	const double DIST_FROM_CENTER = hitrad * (4 / 3);
	double pointTheta = RADIAN_QUARTER - trajectory;
	frontX = DIST_FROM_CENTER * (cos(pointTheta));
	frontY = DIST_FROM_CENTER * (sin(pointTheta));
}

void Player::changeTrajectory(double addTraj) {
	const int RADIAN_CIRCLE = 2 * M_PI;
	trajectory += addTraj;
	if (trajectory > RADIAN_CIRCLE)
		trajectory -= RADIAN_CIRCLE;
	else if (trajectory < 0)
		trajectory += RADIAN_CIRCLE;	
}

void Player::changeSpeed(int accel) {
	const int RADIAN_QUARTER = M_PI / 2;
	double accelTheta = RADIAN_QUARTER - trajectory;
	xVel += accel * (cos(accelTheta));
	yVel += accel * (sin(accelTheta));

}

void Player::drawSelf(SDL_Renderer* rend) {
	const int RADIAN_CIRCLE = 2 * M_PI;
	const int RADIAN_QUARTER = M_PI / 2;
	const double DIST_FROM_CENTER = hitrad * (4 / 3);
	int ptraj = trajectory + RADIAN_CIRCLE / 3;
	vector<int> pCoordinates;
	for (int i = 0; i < 2; i ++) {
		double pointTheta = RADIAN_QUARTER - ptraj;
		int pointX = DIST_FROM_CENTER * (cos(pointTheta));
		int pointY = DIST_FROM_CENTER * (sin(pointTheta));
		pCoordinates.push_back(pointX);
		pCoordinates.push_back(pointY);
		ptraj += RADIAN_CIRCLE / 3;
	}
	trigonRGBA(*rend,
                 frontX, frontY, // x y of first vertex
                 pCoordinates[0], pCoordinates[1], // x y of second vertex
                 pCoordinates[2], pCoordinates[3], // x y of third vertex
                 0xFF, 0xFF, 0xFF, 255); // R G B Alpha values, white
	
}

Bullet Player::shoot() {
	Bullet newBullet(frontX, frontY, trajectory);
	return newBullet;
}

//int main() {





