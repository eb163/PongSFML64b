#include "PhysObj.h"

PhysObj::PhysObj()
{
	pastAccX = pastAccY = accX = accY = 0;
	pastVelX = pastVelY = velX = velY = 0;
	pastDX = pastDY = dX = dY = 0;
}
PhysObj::PhysObj(float initialAccX, float initialAccY)
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
PhysObj::PhysObj(float initialAccX, float initialAccY, float initialVelX, float initialVelY)
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
void PhysObj::update(float dtime) //takes time in seconds (or fractions of)
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
void PhysObj::setAccX(float newAccX)
{
	//accX = newAccX;
	pastAccX = newAccX;
}
void PhysObj::setAccY(float newAccY)
{
	//accY = newAccY;
	pastAccY = newAccY;
}
float PhysObj::getDeltaX()
{
	return dX;
}
float PhysObj::getDeltaY()
{
	return dY;
}