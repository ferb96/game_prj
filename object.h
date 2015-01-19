
class Object

public:
	Object(int x, int y, double traj, int speed);

	const int getX();
	const int getY();
	const double getTrajectory();
	const int getSpeed();

	void setX();
	void setY();
	void setTrajectory();
	void setSpeed();

private:
	int x;
	int y;
	double trajectory;
	int speed;
