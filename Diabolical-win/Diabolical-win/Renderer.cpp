#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

void Renderer::initRenderer()
{

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