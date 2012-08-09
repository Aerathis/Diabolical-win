#ifndef _MODEL_H
#define _MODEL_H

#include <vector>

#include "Vector3.h"

class Model 
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<s_face> faces;
	
public:

	struct s_face
	{
		Vector3 vertexIndices;
		Vector3 normalIndices;
	};

	Model();
	Model(std::vector<Vector3> verts, std::vector<Vector3> norms, std::vector<Model::s_face> faces);
  Model(char* file);

	std::vector<Vector3> getVertices();
	std::vector<Vector3> getNormals();
	std::vector<s_face> getFaces();

	void loadModelFromFile(char* file);
};

#endif //MODEL_H