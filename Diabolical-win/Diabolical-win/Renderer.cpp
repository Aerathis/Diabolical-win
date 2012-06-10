#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

void Renderer::init(HWND hWnd)
{
  m_hWnd = hWnd;

  hDC = GetDC(m_hWnd);

  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory(&pfd,sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  int format = ChoosePixelFormat(hDC,&pfd);
  
  // Create the actual context
  hRC = wglCreateContext(hDC);

  // Make it current
  wglMakeCurrent(hDC,hRC);
}

void Renderer::purge()
{
  if (hRC)
  {
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hRC);
  }
  if (m_hWnd && hDC)
  {
    ReleaseDC(m_hWnd, hDC);
  }
  reset();
}

void Renderer::reset()
{
  m_hWnd = NULL;
  hDC = NULL;
  hRC = NULL;
}

void Renderer::testRender()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glBegin(GL_QUADS);
  glColor3f(1,0,0);glVertex3f(0,0,0);
  glColor3f(0,1,0);glVertex3f(100,0,0);
  glColor3f(0,0,1);glVertex3f(100,100,0);
  glColor3f(1,1,1);glVertex3f(0,100,0);
  glEnd();
  glFlush();
  SwapBuffers(hDC);
}