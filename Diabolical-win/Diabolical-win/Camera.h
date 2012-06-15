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
	void setCameraPosition(float newx, float newy, float newz, float newxrot, float newyrot);

	float getCamX();
	float getCamY();
	float getCamZ();
	float getCamXRot();
	float getCamYRot();
};
#endif //CAMERA_H