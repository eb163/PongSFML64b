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

class Ball
{
public:
private:
	float pastAccX, pastAccY;
	float accX, accY;
	float pastVelX, pastVelY;
	float velX, velY;
	float pastDX, pastDY;
	float dX, dY;
public:
	Ball();
	Ball(float initialAccX, float initialAccY);
	Ball(float initialAccX, float initialAccY, float initialVelX, float initialVelY);
	void update(float dtime); //takes time in seconds (or fractions of)

	void setAccX(float newAccX);
	void setAccY(float newAccY);

	float getDeltaX();
	float getDeltaY();
};