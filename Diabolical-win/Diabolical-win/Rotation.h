#ifndef _ROTATION_H
#define _ROTATION_H

#include "Vector3.h"

class Rotation
{
public:
	union rotElem
	{
		struct
		{
			float s; // Real component
			Vector3 v; // Imaginary components
		};
		struct
		{
			float elem[4];
		};
	};

	rotElem elems;

	Rotation() {}
	Rotation(float real, float x, float y, float z);
	Rotation(float real, const Vector3 &i);

	// Constructor from 3 Euler angles
	Rotation(float tz, float ty, float tx);

	// The basic operators
	Rotation &operator=(const Rotation &other);
	const Rotation operator+(const Rotation &other) const;
	const Rotation operator-(const Rotation &other) const;
	const Rotation operator*(const Rotation &other) const;
	const Rotation operator*(float scale) const;
	const Rotation operator/(const Rotation &other) const;
	const Rotation operator/(float scale) const;
	const Rotation operator-() const;
	const Rotation &operator+=(const Rotation &other);
	const Rotation &operator-=(const Rotation &other);
	const Rotation &operator*=(const Rotation &other);
	const Rotation &operator*=(float scale);
	const Rotation &operator/=(float scale);

	// Get the rotation length
	float length() const;
	float lengthSquared() const;

	// Normalize the rotation
	void normalize();

	// Return the normalized rotation
	Rotation normalized() const;

	// Computes the conjugate
	void conjugate();

	// Inverts the rotation
	void invert();
};

#endif //ROTATION_H