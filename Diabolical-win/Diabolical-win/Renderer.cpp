#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

Renderer Renderer::renderer;

void Renderer::initRenderer()
{
	glViewport(0,0,640,480);
	glClearColor(0,0,0,0);
  GLenum err = glewInit();
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
			int vStart = (x + (size * y))*3;
			terrainData[vStart] = (GLfloat)x;
			terrainData[vStart+1] = (GLfloat)world->im_getWorldMap()->getLocationAtCoord(x,y);
			terrainData[vStart+2] = (GLfloat)y;
      GLfloat test = terrainData[vStart+1];
      double otherTest = world->im_getWorldMap()->getLocationAtCoord(x,y);
      int blah = 0;
		}
	}
  glGenBuffers(1,&terrainDataBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,terrainDataBuffer);
  glBufferData(GL_ARRAY_BUFFER,terrainSize,&terrainData,GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
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
  glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER,terrainDataBuffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,0);
	glDrawArrays(GL_TRIANGLES,0,terrainSize);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}