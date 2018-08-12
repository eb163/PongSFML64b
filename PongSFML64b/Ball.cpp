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
	this->setAccX(0);
	this->setAccY(0);
	this->update(0);

	sprite.setFillColor(sf::Color::White);
	sprite.setOutlineColor(sf::Color::White);
	sprite.setRadius(1.0f);
	sprite.setScale(100.0f, 100.0f); //arbitrary for now
	sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
}
Ball::Ball(float initialAccX, float initialAccY)
{
	this->setAccX(initialAccX);
	this->setAccY(initialAccY);
	this->update(0);

	sprite.setFillColor(sf::Color::White);
	sprite.setOutlineColor(sf::Color::White);
	sprite.setRadius(1.0f);
	sprite.setScale(100.0f, 100.0f); //arbitrary for now
	sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
}
Ball::Ball(sf::Vector2f acc, sf::Color color, float radius, sf::Vector2f scale, sf::Vector2f pos)
{
	this->setAccX(acc.x);
	this->setAccY(acc.y);
	this->update(0);

	sprite.setFillColor(color);
	sprite.setOutlineColor(color);
	sprite.setRadius(radius);
	sprite.setScale(scale.x, scale.y);
	sprite.setPosition(pos.x, pos.y);
}
void Ball::update(float dtime) //takes time in seconds (or fractions of)
{
	this->PhysObj::update(dtime);
}

sf::CircleShape& Ball::getSprite()
{
	return sprite;
}