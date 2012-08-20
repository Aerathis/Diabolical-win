#include "stdafx.h"

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

Model::Model(std::vector<Vector3> verts, std::vector<Model::s_face> inFaces)
{
		vertices = verts;
		faces = inFaces;
}

Model::Model(std::vector<Vector3> verts, std::vector<Vector3> norms, std::vector<Model::s_face> inFaces)
{
		vertices = verts;
		normals = norms;
		faces = inFaces;
}

void Model::loadModelFromFile(char* file)
{
	
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

std::vector<Model::s_renderTri> Model::createRenderTris()
{
	int numFaces = faces.size();
	std::vector<Model::s_renderTri> result;
	for (int i = 0; i < numFaces; i++)
	{
		Model::s_renderTri tri;
		tri.vec1 = vertices[faces[i].vertexIndices.getX()];
		tri.vec2 = vertices[faces[i].vertexIndices.getY()];
		tri.vec3 = vertices[faces[i].vertexIndices.getZ()];
		tri.norm1 = normals[faces[i].normalIndices.getX()];
		tri.norm2 = normals[faces[i].normalIndices.getY()];
		tri.norm3 = normals[faces[i].normalIndices.getZ()];
		result.push_back(tri);
	}
	return result;
}