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
};

#endif //VECTOR3_H