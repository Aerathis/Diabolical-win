#ifndef _MODEL_H
#define _MODEL_H

#include <vector>

#include "Vector3.h"

class Model 
{
	
public:

	struct s_face
	{
		Vector3 vertexIndices; // Not actual vertices. Just indices for the vertices.
		Vector3 normalIndices; // Indices for the vertex normals
	};

	struct s_renderTri
	{
		Vector3 vec1;
		Vector3 vec2;
		Vector3 vec3;
		Vector3 norm1;
		Vector3 norm2;
		Vector3 norm3;
	};

	Model();
	Model(std::vector<Vector3> verts, std::vector<Model::s_face> faces);
	Model(std::vector<Vector3> verts, std::vector<Vector3> norms, std::vector<Model::s_face> faces);
  Model(char* file);

	std::vector<Vector3> getVertices();
	std::vector<Vector3> getNormals();
	std::vector<s_face> getFaces();
	std::vector<s_renderTri> createRenderTris();

	void loadModelFromFile(char* file);

private:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<s_face> faces;
};

#endif //MODEL_H