#include "stdafx.h"

#include "Camera.h"

Camera::Camera()
{
	position.setVector(1.0f,1.0f,1.0f);
}

void Camera::setCameraLocation(float x, float y, float z)
{
	position.setVector(x, y, z);
}

void Camera::moveCamera(Rotation rotation, Vector3 translation)
{
}