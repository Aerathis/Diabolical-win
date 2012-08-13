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

	Model();
	Model(std::vector<Vector3> verts, std::vector<Model::s_face> faces);
	Model(std::vector<Vector3> verts, std::vector<Vector3> norms, std::vector<Model::s_face> faces);
  Model(char* file);

	std::vector<Vector3> getVertices();
	std::vector<Vector3> getNormals();
	std::vector<s_face> getFaces();

	void loadModelFromFile(char* file);

private:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<s_face> faces;
};

#endif //MODEL_H