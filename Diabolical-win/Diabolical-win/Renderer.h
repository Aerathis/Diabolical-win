#ifndef _RENDERER_H
#define _RENDERER_H

#include <gl/GL.h>
#include <gl/GLU.h>

class Renderer
{
private:
  HWND m_hWnd;
  HDC hDC;
  HGLRC hRC;

  void reset();

public:
  void init(HWND hWnd);
  void purge();
  void testRender();
};

#endif //RENDERER_H
