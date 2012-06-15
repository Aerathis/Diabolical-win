#ifndef _CAMERA_H
#define _CAMERA_H

class Camera
{
private:
	float xpos,ypos,zpos;
	float xrot,yrot;

public:
	Camera();
	void cameraLook();
};
#endif //CAMERA_H