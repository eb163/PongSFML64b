#include "Rectangle.h"

Rectangle::Rectangle()
{
	this->setAccX(0);
	this->setAccY(0);
	this->update(0);

	sprite.setFillColor(sf::Color::White);
	sprite.setOutlineColor(sf::Color::White);
	sprite.setSize(sf::Vector2f(1.0f, 1.0f));
	sprite.setScale(100.0f, 100.0f); //arbitrary for now
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}
Rectangle::Rectangle(float initialAccX, float initialAccY)
{
	this->setAccX(initialAccX);
	this->setAccY(initialAccY);
	this->update(0);

	sprite.setFillColor(sf::Color::White);
	sprite.setOutlineColor(sf::Color::White);
	sprite.setSize(sf::Vector2f(1.0f, 1.0f));
	sprite.setScale(100.0f, 100.0f); //arbitrary for now
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}
Rectangle::Rectangle(sf::Vector2f acc, sf::Color color, sf::Vector2f lengthwidth, sf::Vector2f scale, sf::Vector2f pos)
{
	this->setAccX(acc.x);
	this->setAccY(acc.y);
	this->update(0);

	sprite.setFillColor(color);
	sprite.setOutlineColor(color);
	sprite.setSize(lengthwidth);
	sprite.setScale(scale.x, scale.y);
	sprite.setPosition(pos.x, pos.y);
}

void Rectangle::update(float dtime)
{
	this->PhysObj::update(dtime);

	sprite.setPosition(sprite.getPosition().x + getDeltaX(), sprite.getPosition().y + getDeltaY());
}

sf::RectangleShape& Rectangle::getSprite()
{
	return sprite;
}