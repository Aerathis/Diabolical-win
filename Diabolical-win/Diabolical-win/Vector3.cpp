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

void Vector3::setVector(float inx, float iny, float inz)
{
	x = inx;
	y = iny;
	z = inz;
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

float Vector3::length() const
{
	return (float)sqrt((x*x)+(y*y)+(z*z));
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

const Vector3 &Vector3::operator=(const Vector3 other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

const Vector3 &Vector3::operator+=(const Vector3 other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
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

const Vector3 &Vector3::operator-=(const Vector3 other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

const Vector3 Vector3::operator-() const
{
	Vector3 result(-x,-y,-z);
	return result;
}

const float Vector3::operator*(const Vector3 other) const
{
	float result = 0;
	Vector3 self = *this;
	result = self.x * other.x + self.y * other.y + self.z * other.z;
	return result;
}

const Vector3 Vector3::operator*(float scale) const
{
	Vector3 self = *this;
	self.x *= scale;
	self.y *= scale;
	self.z *= scale;
	return self;
}

const Vector3 &Vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}
const Vector3 Vector3::operator/(float scale) const
{
	Vector3 self = *this;
	self.x /= scale;
	self.y /= scale;
	self.z /= scale;
	return self;
}

const Vector3 &Vector3::operator/=(float scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
	return *this;
}

const Vector3 Vector3::operator%(const Vector3 other) const
{
	Vector3 temp(y*other.z - z*other.y,z*other.x-x*other.z,x*other.y-y*other.x);
	return temp;
}