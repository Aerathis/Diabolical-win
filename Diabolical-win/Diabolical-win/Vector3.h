#ifndef _VECTOR3_H
#define _VECTOR3_H

class Vector3
{
private:
	float x,y,z;

public:
	Vector3();
	Vector3(float x, float y, float z);

	void zeroVector();
	float getX();
	float getY();
	float getZ();

	Vector3 normalize();

	const Vector3 operator+(const Vector3 other) const;
	const Vector3 operator-(const Vector3 other) const;
};

#endif //VECTOR3_H