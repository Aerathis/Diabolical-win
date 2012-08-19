#ifndef _CAMERA_H
#define _CAMERA_H

#include "Rotation.h"
#include "Vector3.h"

class Camera
{
private:
	
	Vector3 position;
	Rotation rotation;

public:
	
	Camera();

	Rotation getViewRotation();
	Vector3 getViewPosition();

	void setCameraLocation(float x, float y, float z);
	void moveCamera(Rotation rotation, Vector3 translation);
};
#endif //CAMERA_H