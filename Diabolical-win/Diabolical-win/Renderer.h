#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>

#include "glew.h"

#include "Camera.h"
#include "World.h"

class Renderer
{
private:
	struct s_Vert
	{
		float x;
		float y;
		float z;
	};

	struct s_texCoord
	{
		float u;
		float v;
	};

	GLuint terrainDataBuffer;
	s_Vert* terrainData;
	s_texCoord* texData;
	int terrainSize;
	Camera renderCam;

public:
	static Renderer renderer;
	void initRenderer();
	void getWorldTerrain(World* world);
	void resize(int w,int h);
  void testRender();
	void drawTerrain();
};
#endif //RENDERER_H
