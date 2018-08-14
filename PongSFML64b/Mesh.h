#pragma once
#include <SFML/System.hpp>
//basic rectangular mesh for now, will work on circle later

class Mesh
{
private:
	sf::Vector2f origin;
	float length; //x
	float width; //y
	//float height; //unneeded for 2d

public:
	sf::Vector2f getOrigin();
	void setOrigin(sf::Vector2f newOrigin);

	float getLength();
	void setLength(float newLength);

	float getWidth();
	void setWidth(float newWidth);
};