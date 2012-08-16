#include "stdafx.h"
#include "Creators.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265

namespace creators
{

  // Pretty much everything in this anonymous namespace I stole from another project I was working on, and it's better commented there.
  namespace
  {
    double interpolate(double x, double y, double fract)
    {
      double fract_deg = fract * PI;
      double f = (1 - cos(fract_deg)) * .5;

      return x*(1-f)+y*f;
    }

    double smooth(double x, double y, int i, ShiftRand* rando)
    {
      double corners = ((rando->next()+rando->next()+rando->next()+rando->next())/16);
      double sides = ((rando->next()+rando->next()+rando->next()+rando->next())/8);
      double centre = (rando->next()/4);

      return corners+sides+centre;
    }

     double interpNoise(double x, double y, int i, ShiftRand* rando)
    {
      int int_x = int(x);
      double fract_x = x - int_x;

      int int_y = int(y);
      double fract_y = y - int_y;

      double v1 = smooth(int_x, int_y, i, rando);
      double v2 = smooth(int_x + 1, int_y, i, rando);
      double v3 = smooth(int_x, int_y + 1, i, rando);
      double v4 = smooth(int_x + 1, int_y + 1, i, rando);

      double i1 = interpolate(v1, v2, fract_x);
      double i2 = interpolate(v3, v4, fract_x);

      return interpolate(i1, i2, fract_y);
    }

    double perlin(int x, int y, ShiftRand* rando)
    {
      double total = 0;
      double persistence = 0.25;
      double octaves = 9;

      for (int i = 0; i < octaves; i++)
	{
	  double frequency = pow(2.0f, i);
	  double amplitude = pow(persistence, i);

	  total = (total + interpNoise(x*frequency, y*frequency, i, rando) * amplitude);
	}

      return total/octaves;
    }
  }

  // Fill up the terrainMap with nice fun slightly hilly terrain
  bool fillTerrain(Map<double>* terrainMap)
  {
    // Get an xorshift RNG
    ShiftRand terrainGen;
    // Get the map size so I don't blow up the program but segfaulting
    int mapSize = terrainMap->getMapSize();
    // Max and min (since the RNG outputs values on a different scale, I wasn't thinking ahead)
    int hMin = 1000000000;
    int hMax = 0;
    // And off we go through the various locations in the map
    for (int y = 0; y < mapSize; y++)
      {
	for (int x = 0; x < mapSize; x++)
	  {
	    // Get the value for the cell and if it is higher or lower than the min or max, set the min/max to that value
	    double hVal = perlin(x,y,&terrainGen);
	    if (hVal > hMax)
	      hMax = (int)hVal;
	    if (hVal < hMin)
	      hMin = (int)hVal;
	    // Toss it into the map. (Yes I know I just pull it out again later, I'm lazy)
	    terrainMap->setLocationAtCoord(x,y,hVal);
	  }
      }

    // Not the most efficient, but it does the job. I can fix the speed problem later. Here I'm just normalizing the values to a sane scale. 
    for (int y = 0; y < mapSize; y++)
      {
	for (int x = 0; x < mapSize; x++)
	  {
	    double swap = terrainMap->getLocationAtCoord(x,y);
	    swap = (swap-hMin)/(hMax-hMin);	    
	    terrainMap->setLocationAtCoord(x,y,swap > 0.01 ? swap : 0);
	    std::cout << terrainMap->getLocationAtCoord(x,y) << " ";
	  }
	std::cout << std::endl;
      }
    return true;
  }


  // At the moment this just sets everything to the body temp so that things don't die
  bool fillWeather(Map<int>* weatherMap)
  {
    int mapSize = weatherMap->getMapSize();
    for (int y = 0; y < mapSize; y++)
      {
	for (int x = 0; x < mapSize; x++)
	  {
	    weatherMap->setLocationAtCoord(x,y,37);
	    std::cout << weatherMap->getLocationAtCoord(x,y) << " ";
	  }
	std::cout << std::endl;
      }
    return true;
  }

  bool fillPrecipitation(Map<float>* precipMap)
  {
    int mapSize = precipMap->getMapSize();
    for (int y = 0; y < mapSize; y++)
    {
      for (int x = 0; x < mapSize; x++)
      {
        precipMap->setLocationAtCoord(x,y,0);
      }
    }
    return true;
  }

  // Simple fill function - checks for magic height values and fills the typeMap with the 
  // Corresponding enum value
  bool fillTerrainDetails(Map<e_terrainType>* terrainMap, Map<double>* worldMap)
  {
    int mapSize = terrainMap->getMapSize();
    for (int y = 0; y < mapSize; y++)
      {
	for (int x = 0; x < mapSize; x++)
	  {
	    if (worldMap->getLocationAtCoord(x,y) < 0.2)
	      {
		terrainMap->setLocationAtCoord(x,y,e_water);
		std::cout << "w ";
	      }
	    else if (worldMap->getLocationAtCoord(x,y) < 0.4 && worldMap->getLocationAtCoord(x,y) > 0.2)
	      {
		terrainMap->setLocationAtCoord(x,y,e_shallowWater);
		std::cout << "s ";
	      }
	    else if (worldMap->getLocationAtCoord(x,y) > 0.8)
	      {
		terrainMap->setLocationAtCoord(x,y,e_mountain);
		std::cout << "m ";
	      }
	    else 
	      {
		terrainMap->setLocationAtCoord(x,y,e_grass);
		std::cout << "  ";
	      }
	  }
	std::cout << std::endl;
      }
    return true;
  }

  bool placeResources(std::vector<Object>* objects, Map<e_terrainType>* terrain)
  {
    int mapSize = terrain->getMapSize();
    for (int y = 0 ; y < mapSize; y++)
      {
	for (int x = 0; x < mapSize; x++)
	  {
	    if (terrain->getLocationAtCoord(x,y) == e_mountain)
	      {
		Object stone;
		stone.initObject(x,y,Object::e_rock);
		objects->push_back(stone);
	      }
	    if (terrain->getLocationAtCoord(x,y) == e_grass)
	      {
		Object tree;
		tree.initObject(x,y, Object::e_tree);
		objects->push_back(tree);
	      }
	  }
      }
    return true;
  }

	Model createWorldModel(Map<double>* worldMap)
	{
		std::vector<Vector3> vecs;
		std::vector<Vector3> norms;
		std::vector<Model::s_face> faces;

		//TODO: This is where the magic needs to happen.

	  int mapSize = worldMap->getMapSize();

		for (int y = 0; y < mapSize; y++)
		{
			for (int x = 0; x < mapSize; x++)
			{
					vecs.push_back(Vector3((float)x, (float)worldMap->getLocationAtCoord(x,y), (float)y));
			}
		}

		//int numFaces = ((mapSize -1) * 2) * 2;
		int numFaces = ((mapSize - 1) * (mapSize - 1)) * 2;

		for (int i = 0; i < numFaces; i++)
		{
			int row = i / ((mapSize - 1) * 2);
			Model::s_face face;
			if (i % 2 == 0)
			{
				// Think that I might have mixed up vertex/face indexes for this one. 
				// TODO: Look into ^ later.
				face.vertexIndices = Vector3((row * mapSize) + ((i/2) % (mapSize - 1)), (row * mapSize) + ((i/2) % (mapSize - 1)) + 1, ((row+1) * mapSize) + ((i/2) % (mapSize - 1)));
			}
			else
			{
				// TODO: Keep your eye on the return values from the i/2 terms in this one. 
				face.vertexIndices = Vector3(((row + 1) * mapSize) + ((i/2) % (mapSize - 1)) + 1, ((row + 1) * mapSize) + ((i/2) % (mapSize - 1)), (row * mapSize) + ((i/2) % (mapSize - 1)) + 1);
			}
			faces.push_back(face);
		}

		int numVecs = vecs.size();

		for (int j = 0; j < numVecs; j++)
		{
			std::vector<Model::s_face> contributors;
			for (int k = 0; k < numFaces; k++)
			{
				int v1 = faces[k].vertexIndices.getX();
				int v2 = faces[k].vertexIndices.getY();
				int v3 = faces[k].vertexIndices.getZ();

				if (v1 == j || v2 == j || v3 == j)
				{
					contributors.push_back(faces[k]);
				}
			}

			std::vector<Vector3> faceNormals;
			// We have the contributing faces at this point in contributors.
			// TODO: Find the surface normals for the faces, then we average them together to find the vertex normals.
			for (int i = 0; i < contributors.size(); i++)
			{
				Vector3 U = vecs[contributors[i].vertexIndices.getY()] - vecs[contributors[i].vertexIndices.getX()];
				Vector3 V = vecs[contributors[i].vertexIndices.getZ()] - vecs[contributors[i].vertexIndices.getX()];

				float xNorm = (U.getY() * V.getZ()) - (U.getZ() * V.getY());
				float yNorm = (U.getZ() * V.getX()) - (U.getX() * V.getZ());
				float zNorm = (U.getX() * V.getY()) - (U.getY() * V.getX());

				faceNormals.push_back(Vector3(xNorm, yNorm, zNorm));
			}

			Vector3 vertNorm;

			for (int i = 0; i < faceNormals.size(); i++)
			{
				Vector3 tempNorm = faceNormals[i];
				vertNorm = vertNorm + tempNorm;
			}
			norms.push_back(vertNorm.normalize());
		}

		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].normalIndices = Vector3(faces[i].vertexIndices.getX(), faces[i].vertexIndices.getY(), faces[i].vertexIndices.getZ());
		}
		return Model(vecs, norms, faces);
	}
}
