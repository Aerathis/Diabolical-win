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
}
