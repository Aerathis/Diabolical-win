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