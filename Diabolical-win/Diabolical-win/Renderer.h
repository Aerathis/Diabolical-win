#ifndef _RENDERER_H
#define _RENDERER_H

#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>

#include "glext.h"
#include "World.h"

class Renderer
{
private:
	PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	PFNGLBINDBUFFERARBPROC glBindBufferARB;
	PFNGLBUFFERDATAARBPROC glBufferDataARB;
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
