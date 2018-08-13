#pragma once
#include "PhysObj.h"
#include <SFML/Graphics.hpp>
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

class Ball: public PhysObj
{
private:
	sf::CircleShape sprite;
public:
	Ball();
	Ball(float initialAccX, float initialAccY);
	Ball(sf::Vector2f acc, sf::Color color, float radius, sf::Vector2f scale, sf::Vector2f pos);
	void update(float dtime); //takes time in seconds (or fractions of)

	//void setAccX(float newAccX);
	//void setAccY(float newAccY);

	//float getDeltaX();
	//float getDeltaY();

	sf::CircleShape& getSprite();

	//bool detectCollision(PhysObj otherObj);
};