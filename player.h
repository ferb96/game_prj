#include "object.h"
#include "bullet.h"

class Player: public Object
{
public:
	Player(int screenWidth, int screenHeight);
	void changeTrajectory();
	void changeSpeed(int accel);

	void drawSelf(SDL_Renderer* rend);
	Bullet shoot();
private:
	int frontX;
	int frontY;
}