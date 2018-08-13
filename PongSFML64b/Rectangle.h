#pragma once

#include "PhysObj.h"
#include <SFML/Graphics.hpp>

class Rectangle : public PhysObj
{
private:
	sf::RectangleShape sprite;
public:
	Rectangle();
	Rectangle(float initialAccX, float initialAccY);
	Rectangle(sf::Vector2f acc, sf::Color color, sf::Vector2f lengthwidth, sf::Vector2f scale, sf::Vector2f pos);
	void update(float dtime);

	sf::RectangleShape& getSprite();

	//bool detectCollision(PhysObj otherObj);
};