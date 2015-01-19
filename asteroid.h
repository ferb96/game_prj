
class Asteroid extends Object

public:
	Asteroid(int x, int y, double traj, int speed);

	const int getLevel();

	void setLevel();

	
private:
	int level;
	drawAsteroid();