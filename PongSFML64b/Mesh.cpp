#include "Mesh.h"

sf::Vector2f Mesh::getOrigin()
{
	return origin;
}

void Mesh::setOrigin(sf::Vector2f newOrigin)
{
	origin = newOrigin;
}

float Mesh::getLength()
{
	return length;
}

void Mesh::setLength(float newLength)
{
	length = newLength;
}

float Mesh::getWidth()
{
	return width;
}

void Mesh::setWidth(float newWidth)
{
	width = newWidth;
}