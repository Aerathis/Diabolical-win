#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

Renderer Renderer::renderer;

Camera* Renderer::getRenderCamera()
{
	return &renderCam;
}

void Renderer::initRenderer()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
	glViewport(0,0,640,480);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,0);
	GLenum err = glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Renderer::getWorldTerrain(World* world)
{
	int size = world->im_getWorldMap()->getMapSize();
  terrainSize = size*size*6;
	terrainData = new s_Vert[terrainSize];

	int index = 0;
  float vx;
  float vz;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
      for (int tri = 0; tri < 6; tri++)
      {
        vx = (float)x + ((tri == 1 || tri == 2 || tri == 5) ? 1 : 0);
        vz = (float)y + ((tri == 2 || tri == 4 || tri == 5) ? 1 : 0);

        terrainData[index].x = vx;
        terrainData[index].y = (float)world->im_getWorldMap()->getLocationAtCoord(x,y);
        terrainData[index].z = vz;
        index++;
      }
		}
	}
  glGenBuffers(1,&terrainDataBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,terrainDataBuffer);
  glBufferData(GL_ARRAY_BUFFER,terrainSize * 3 * sizeof(float),&terrainData,GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Renderer::resize(int w, int h)
{
	glViewport(0,0,w,h);
}

void Renderer::testRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	glLoadIdentity();
	renderCam.cameraLook();
	glPushMatrix();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER,terrainDataBuffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,0);
	glDrawArrays(GL_TRIANGLES,0,terrainSize);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER,0);
	glPopMatrix();
}