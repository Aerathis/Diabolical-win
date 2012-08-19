#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>

#include "glew.h"

#include "Camera.h"
#include "World.h"

class Renderer
{
private:
	Camera* renderCamera;

public:
	static Renderer renderer;

	Renderer();
	Camera* getRenderCamera();
	
};
#endif //RENDERER_H
