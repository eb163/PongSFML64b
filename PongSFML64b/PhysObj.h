#pragma once
#include <iostream> //debug

using std::cout;
using std::endl;

/*
CONSTANT ACCELERATION MOTION EQUATIONS
--------------------------------------
a = a
v = v(0) + a * dt
x = x(0) + v * dt = x(0) + (1/2) * a * dt^2
*/

class PhysObj
{
private:
	float pastAccX, pastAccY;
	float accX, accY;
	float pastVelX, pastVelY;
	float velX, velY;
	float pastDX, pastDY;
	float dX, dY;
public:
	PhysObj();
	PhysObj(float initialAccX, float initialAccY);
	PhysObj(float initialAccX, float initialAccY, float initialVelX, float initialVelY);
	void update(float dtime); //takes time in seconds (or fractions of)

	void setAccX(float newAccX);
	void setAccY(float newAccY);

	void setVelX(float newVelX);
	void setVelY(float newVelY);

	float getDeltaX();
	float getDeltaY();

	//virtual bool detectCollision();
};