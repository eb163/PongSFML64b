#include "Ball.h"

/*
CONSTANT ACCELERATION MOTION EQUATIONS
--------------------------------------
a = a
v = v(0) + a * dt
x = x(0) + v * dt = x(0) + (1/2) * a * dt^2
*/

Ball::Ball()
{
	pastAccX = pastAccY = accX = accY = 0;
	pastVelX = pastVelY = velX = velY = 0;
	pastDX = pastDY = dX = dY = 0;
}
Ball::Ball(float initialAccX, float initialAccY)
{
	//accX = initialAccX;
	//accY = initialAccY;
	pastAccX = initialAccX;
	pastAccY = initialAccY;
	accX = accY = 0;
	pastVelX = pastVelY = velX = velY = 0;
	pastDX = pastDY = dX = dY = 0;
	this->update(0);
}
Ball::Ball(float initialAccX, float initialAccY, float initialVelX, float initialVelY)
{
	pastAccX = initialAccX;
	pastAccY = initialAccY;
	pastVelX = initialVelX;
	pastVelY = initialVelY;
	accX = accY = 0;
	velX = velY = 0;
	pastDX = pastDY = dX = dY = 0;
	this->update(0);

}
void Ball::update(float dtime) //takes time in seconds (or fractions of)
{
	accX = pastAccX;
	accY = pastAccY;
	cout << "Acceleration: (" << accX << ", " << accY << ")" << endl;

	pastVelX = velX;
	pastVelY = velY;
	velX = pastVelX + accX * dtime;
	velY = pastVelY + accY * dtime;
	cout << "Velocity: (" << velX << ", " << velY << ")" << endl;

	pastDX = dX;
	pastDY = dY;
	dX = pastDX + 0.5f * velX * dtime;
	dY = pastDY + 0.5f * velY * dtime;
	cout << "Delta X: (" << dX << ", " << dY << ")" << endl;
}
void Ball::setAccX(float newAccX)
{
	accX = newAccX;
}
void Ball::setAccY(float newAccY)
{
	accY = newAccY;
}
float Ball::getDeltaX()
{
	return dX;
}
float Ball::getDeltaY()
{
	return dY;
}