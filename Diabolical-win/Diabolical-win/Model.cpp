#include <iostream>
#include <fstream>

#include "Model.h"

Model::Model()
{
	if (vertices.size() > 0)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].zeroVector();
		}
	}

	if (normals.size() > 0)
	{
		for (int i = 0; i < normals.size(); i++)
		{
			normals[i].zeroVector();
		}
	}

	if (faces.size() > 0)
	{
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].normalIndices.zeroVector();
			faces[i].vertexIndices.zeroVector();
		}
	}
}

void Model::loadModelFromFile(char* file)
{
	FILE* handle = fopen(file,"r");
	if (handle != NULL)
	{

	}
}