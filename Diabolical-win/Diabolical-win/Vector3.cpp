#include "Vector3.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float inx, float iny, float inz)
{
	x = inx;
	y = iny;
	z = inz;
}

void Vector3::zeroVector()
{
	x = 0;
	y = 0;
	z = 0;
}

float Vector3::getX()
{
	return x;
}

float Vector3::getY()
{
	return y;
}

float Vector3::getZ()
{
	return z;
}