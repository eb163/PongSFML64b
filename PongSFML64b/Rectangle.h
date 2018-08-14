#pragma once

#include "PhysObj.h"
#include "Mesh.h"
#include <SFML/Graphics.hpp>

class Rectangle : public PhysObj
{
private:
	sf::RectangleShape sprite;
	Mesh mesh;
public:
	Rectangle();
	Rectangle(float initialAccX, float initialAccY);
	Rectangle(sf::Vector2f acc, sf::Color color, sf::Vector2f lengthwidth, sf::Vector2f scale, sf::Vector2f pos);
	void update(float dtime);

	sf::RectangleShape& getSprite();

	Mesh& getMesh();

	//bool detectCollision(PhysObj otherObj);
};