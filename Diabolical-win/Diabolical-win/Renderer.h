#ifndef _RENDERER_H
#define _RENDERER_H

#include "glew.h"
#include <vector>
#include "World.h"

class Renderer
{
private:
	GLuint terrainDataBuffer;
	GLfloat* terrainData;
	int terrainSize;

public:
	static Renderer renderer;
	void initRenderer();
	void getWorldTerrain(World* world);
	void resize(int w,int h);
  void testRender();
	void drawTerrain();
};
#endif //RENDERER_H
