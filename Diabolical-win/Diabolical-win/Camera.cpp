#include "stdafx.h"

#include "Camera.h"

Camera::Camera()
{
	position.setVector(-0.5f,-0.5f,-0.5f);
	rotation.setVector(0,0,0);
}

Rotation Camera::getViewRotation()
{
	return rotation;
}

Vector3 Camera::getViewPosition()
{
	return position;
}

void Camera::setCameraLocation(float x, float y, float z)
{
	position.setVector(x, y, z);
}

void Camera::moveCamera(Rotation rotate, Vector3 translation)
{
	rotation = rotation + rotate;
	position = position + translation;
}