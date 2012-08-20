#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

Renderer Renderer::renderer;

Renderer::Renderer()
{
	renderCamera = new Camera();
}

Camera* Renderer::getRenderCamera()
{
	return renderCamera;
}

bool Renderer::initRenderer(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return true;
}

void Renderer::drawModel(Model model)
{
	Rotation workingRot = renderCamera->getViewRotation();
	std::vector<Model::s_renderTri> tris = model.createRenderTris();
	int numTris = tris.size();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glTranslatef(renderer.getRenderCamera()->getViewPosition().getX(),renderer.getRenderCamera()->getViewPosition().getY(),renderer.getRenderCamera()->getViewPosition().getZ());
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < numTris; i++)
	{
		glVertex3f(tris[i].vec1.getX(),tris[i].vec1.getY(),tris[i].vec1.getZ());
		glNormal3f(tris[i].norm1.getX(),tris[i].norm1.getY(),tris[i].norm1.getZ());
		glVertex3f(tris[i].vec2.getX(),tris[i].vec2.getY(),tris[i].vec2.getZ());
		glNormal3f(tris[i].norm2.getX(),tris[i].norm2.getY(),tris[i].norm2.getZ());
		glVertex3f(tris[i].vec3.getX(),tris[i].vec3.getY(),tris[i].vec3.getZ());
		glNormal3f(tris[i].norm3.getX(),tris[i].norm3.getY(),tris[i].norm3.getZ());
	}
	glEnd();
}