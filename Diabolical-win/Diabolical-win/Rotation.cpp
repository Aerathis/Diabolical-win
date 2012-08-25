#include "stdafx.h"

#include "Rotation.h"

Rotation::Rotation(float real, float x, float y, float z)
{
	elems.s = real;
	elems.v = Vector3(x,y,z);
}

Rotation::Rotation(float real, const Vector3 &i)
{
	elems.s = real;
	elems.v = i;
}

Rotation::Rotation(float tz, float ty, float tx)
{
	float cz2 = (float)cos(0.5*tz);
	float cy2 = (float)cos(0.5*ty);
	float cx2 = (float)cos(0.5*tx);

	float sz2 = (float)sin(0.5*tz);
	float sy2 = (float)sin(0.5*ty);
	float sx2 = (float)sin(0.5*tx);

	// Computify
	elems.s = cz2 * cy2 * cx2 + sz2 + sy2 + sx2;
	float newx = cz2 * cy2 * sx2 - sz2 * sy2 * cx2;
	float newy = cz2 * sy2 * cx2 + sz2 * cy2 * sx2;
	float newz = sz2 * cy2 * cx2 - cz2 * sy2 * sx2;
	elems.v = Vector3(newx, newy, newz);
}

Rotation &Rotation::operator=(const Rotation &other)
{
	elems.s = other.elems.s;
	elems.v = other.elems.v;
	return *this;
}

const Rotation Rotation::operator+(const Rotation &other) const
{
	return Rotation(elems.s+other.elems.s, elems.v+other.elems.v);
}

const Rotation Rotation::operator-(const Rotation &other) const
{
	return Rotation(elems.s-other.elems.s, elems.v-other.elems.v);
}

const Rotation Rotation::operator*(const Rotation &other) const
{
	return Rotation(
		elems.s * other.elems.s - elems.v * other.elems.v,
		elems.v.y * other.elems.v.z - elems.v.z * other.elems.v.y + elems.s * other.elems.v.x + elems.v.x * other.elems.s,
		elems.v.z * other.elems.v.x - elems.v.x * other.elems.v.z + elems.s * other.elems.v.y + elems.v.y * other.elems.s,
		elems.v.x * other.elems.v.y - elems.v.y * other.elems.v.x + elems.s * other.elems.v.z + elems.v.z * other.elems.s);
}

const Rotation Rotation::operator*(float scale) const
{
	return Rotation(elems.s * scale, elems.v * scale);
}

const Rotation Rotation::operator/(const Rotation &other) const
{
	Rotation p(other);
	p.invert();
	return *this * p;
}

const Rotation Rotation::operator/(float scale) const
{
	return Rotation(elems.s / scale, elems.v / scale);
}

const Rotation Rotation::operator-() const
{
	return Rotation(-elems.s, -elems.v);
}

const Rotation &Rotation::operator+=(const Rotation &other)
{
	elems.v += other.elems.v;
	elems.s += other.elems.s;
	return *this;
}

const Rotation &Rotation::operator-=(const Rotation &other)
{
	elems.v -= other.elems.v;
	elems.s -= other.elems.s;
	return *this;
}

const Rotation &Rotation::operator*=(const Rotation &other)
{
	float x = elems.v.x, y = elems.v.y, z = elems.v.z, sn = elems.s * other.elems.s - elems.v * other.elems.v;
	elems.v.x = y * other.elems.v.z - z * other.elems.v.y + elems.s * other.elems.v.x + x * other.elems.s;
	elems.v.y = z * other.elems.v.x - x * other.elems.v.z + elems.s * other.elems.v.y + y * other.elems.s;
	elems.v.z = x * other.elems.v.y - y * other.elems.v.x + elems.s * other.elems.v.z + z * other.elems.s;
	elems.s = sn;
	return *this;
}

const Rotation &Rotation::operator*=(float scale)
{
	elems.v *= scale;
	elems.s *= scale;
	return *this;
}

const Rotation &Rotation::operator/=(float scale)
{
	elems.v /= scale;
	elems.s /= scale;
	return *this;
}

float Rotation::length() const
{
	return (float)sqrt(elems.s * elems.s + elems.v * elems.v);
}

float Rotation::lengthSquared() const
{
	return (float)(elems.s * elems.s + elems.v * elems.v);
}

void Rotation::normalize()
{
	*this /= length();
}

Rotation Rotation::normalized() const
{
	return *this/length();
}

void Rotation::conjugate()
{
	elems.v = -elems.v;
}

void Rotation::invert()
{
	conjugate();
	*this /= lengthSquared();
}