#include "stdafx.h"

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

Vector3 Vector3::normalize()
{
	float mag = sqrt((x * x) + (y * y) + (z * z));
	return Vector3(x/mag, y/mag, z/mag);
}

const Vector3 Vector3::operator+(const Vector3 other) const
{
	Vector3 result;
	Vector3 self = *this;
	float x1 = self.x;
	float y1 = self.y;
	float z1 = self.z;

	float x2 = other.x;
	float y2 = other.y;
	float z2 = other.z;

	result.x = x1 + x2;
	result.y = y1 + y2;
	result.z = z1 + z2;
	
	return result;
}

const Vector3 Vector3::operator-(const Vector3 other) const
{
	Vector3 result;
	Vector3 self = *this;
	Vector3 convOther;
	convOther.x = -other.x;
	convOther.y = -other.y;
	convOther.z = -other.z;

	result = self + convOther;
	return result;
}