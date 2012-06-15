#include "stdafx.h"

#include "Camera.h"

Camera::Camera()
{
	xpos = 851;
	ypos = 351;
	zpos = 281;
	xrot = 758;
	yrot = 238;
}

void Camera::cameraLook()
{
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,1.0,0.0);
	glTranslated(-xpos,-ypos,-zpos);
}

void Camera::setCameraPosition(float newx, float newy, float newz, float newxrot, float newyrot)
{
	xpos = newx;
	ypos = newy;
	zpos = newz;
	xrot = newxrot;
	yrot = newyrot;
}

float Camera::getCamX()
{
	return xpos;
}

float Camera::getCamY()
{
	return ypos;
}

float Camera::getCamZ()
{
	return zpos;
}

float Camera::getCamXRot()
{
	return xrot;
}

float Camera::getCamYRot()
{
	return yrot;
}