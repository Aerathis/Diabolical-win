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

void Renderer::drawModel(Model model)
{
	Rotation workingRot = renderCamera->getViewRotation();
	std::vector<Model::s_renderTri> tris = model.createRenderTris();
	int numTris = tris.size();
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