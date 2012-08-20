#ifndef _VECTOR3_H
#define _VECTOR3_H

class Vector3
{
private:
	

public:
	float x,y,z;
	Vector3();
	Vector3(float x, float y, float z);

	void zeroVector();
	void setVector(float x, float y, float z);
	float getX();
	float getY();
	float getZ();

	float length() const;
	Vector3 normalize();

	const Vector3 &operator=(const Vector3 other);
	const Vector3 operator+(const Vector3 other) const;
	const Vector3 &operator+=(const Vector3 other);
	const Vector3 operator-(const Vector3 other) const;
	const Vector3 &operator-=(const Vector3 other);
	const Vector3 operator-() const;
	// Dot product
	const float operator*(const Vector3 other) const;
	const Vector3 operator*(float scale) const;
	const Vector3 &operator*=(float scale);
	const Vector3 operator/(float scale) const;
	const Vector3 &operator/=(float scale);
	// Cross product
	const Vector3 operator%(const Vector3 other) const;
};

#endif //VECTOR3_H