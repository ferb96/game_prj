
#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid{

public:
	Asteroid();
	void initSizes(double lvl1, double lvl2, double lvl3);
	void drawSelf();
	void updatePosition(int limitX, int limitY);
	
private:
	int level;

};

#endif /* ASTEROID_H */