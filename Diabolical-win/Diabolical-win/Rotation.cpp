#include "stdafx.h"

#include "Rotation.h"

Rotation::Rotation() : Vector3()
{
	
}

Rotation::Rotation(float inx, float iny, float inz) : Vector3(inx, iny, inz)
{
}

const Rotation Rotation::operator=(Vector3 other)
{
	this->setVector(other.getX(), other.getY(), other.getZ());
	return *this;
}

//TODO: Some sort of actual rotation addition
const Rotation Rotation::operator+(Rotation other)
{
	Rotation self = *this;
	float newx, newy, newz;
	newx = self.getX() + other.getX();
	newy = self.getY() + other.getY();
	newz = self.getZ() + other.getZ();

	if (newx > 360)
	{
		newx = newx - 360;
	}
	if (newy > 360) 
	{
		newy = newy - 360;
	}
	if (newz > 360)
	{
		newz = newz - 360;
	}

	if (newx < 0)
	{
		newx = newx + 360;
	}
	if (newy < 0)
	{
		newy = newy + 360;
	}
	if (newz < 0)
	{
		newz = newz + 360;
	}

	Rotation result = Rotation(newx, newy, newz);
	return result;
}