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