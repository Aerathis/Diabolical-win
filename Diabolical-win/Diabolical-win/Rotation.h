#ifndef _ROTATION_H
#define _ROTATION_H

#include "Vector3.h"


// A clearly separated from normal Vector rotation. 
// This can also add some rotation specific things.
class Rotation : public Vector3
{
private:

public:
	Rotation();
	Rotation(float inx, float iny, float inz);

	const Rotation operator=(Vector3 other);
	const Rotation operator+(Rotation other);
};

#endif //ROTATION_H