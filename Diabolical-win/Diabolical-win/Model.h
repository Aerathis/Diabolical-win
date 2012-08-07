#ifndef _MODEL_H
#define _MODEL_H

#include <vector>

#include "Vector3.h"

struct s_face
{
	Vector3 vertexIndices;
	Vector3 normalIndices;
};

class Model 
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<s_face> faces;
	
public:
	Model();
  Model(char* file);

	void drawModel();

	void loadModelFromFile(char* file);
};

#endif //MODEL_H