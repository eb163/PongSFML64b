#pragma once

//basic rectangular mesh for now, will work on circle later

class Mesh
{
private:
	float width;
	float length;
	//float height; //unneeded for 2d

public:
	float getWidth();
	void setWidth(float newWidth);

	float getLength();
	void setLength(float newLength);
};