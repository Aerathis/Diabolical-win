#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

Renderer Renderer::renderer;

void Renderer::initRenderer()
{
	glViewport(0,0,640,480);
	glClearColor(0,0,0,0);
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
}

void Renderer::getWorldTerrain(World* world)
{
	int size = world->im_getWorldMap()->getMapSize();
	terrainData = new GLfloat[size*size*3];
	terrainSize = size*size*3;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int vStart = x * y;
			terrainData[vStart] = (GLfloat)x;
			terrainData[vStart+1] = (GLfloat)world->im_getWorldMap()->getLocationAtCoord(x,y);
			terrainData[vStart+2] = (GLfloat)y;
		}
	}
}

void Renderer::resize(int w, int h)
{
	glViewport(0,0,w,h);
}

void Renderer::testRender()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glBegin(GL_QUADS);
  glColor3f(1,0,0);glVertex3f(0,0,0);
  glColor3f(0,1,0);glVertex3f(0.5f,0,0);
  glColor3f(0,0,1);glVertex3f(0.5f,0.5f,0);
  glColor3f(1,1,1);glVertex3f(0,0.5f,0);
  glEnd();
}

void Renderer::drawTerrain()
{
	glGenBuffersARB(terrainSize,&terrainDataBuffer);
	glBindBufferARB(GL_ARRAY_BUFFER,terrainDataBuffer);
	glBufferDataARB(GL_ARRAY_BUFFER,terrainSize,&terrainData,GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,0);
	glDrawArrays(GL_TRIANGLES,0,terrainSize);
}