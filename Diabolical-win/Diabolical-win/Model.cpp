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

Model::Model(std::vector<Vector3> verts, std::vector<Vector3> norms, std::vector<Model::s_face> inFaces)
{
		vertices = verts;
		normals = norms;
		faces = inFaces;
}

void Model::loadModelFromFile(char* file)
{
	FILE* handle = fopen(file,"r");
	if (handle != NULL)
	{

	}
}

std::vector<Vector3> Model::getVertices()
{
	return vertices;
}

std::vector<Vector3> Model::getNormals()
{
	return normals;
}

std::vector<Model::s_face> Model::getFaces()
{
	return faces;
}