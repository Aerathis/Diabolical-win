#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <malloc.h>

// Currently this is only going to make squares, because they're easier to work with and I'm lazy. 
template <class T>
class Map
{
 public:
  Map()
    {
      mapSize = 0;
      setSize(mapSize);
    }
  Map(int size)
    {
      mapSize = size;
      setSize(mapSize);
    }

  ~Map()
    {
      std::cout << "Freeing map memory and destroying" << std::endl;
      free(mapCells);
    }

  T getLocationAtCoord(int x, int y)
  {
    return mapCells[x][y];
  }

  void setLocationAtCoord(int x, int y, T value) 
  {
    mapCells[x][y] = value;
  }

  int getMapSize()
  {
    return mapSize;
  }
  void setSize(int size)
  {
    if (mapSize > 0)
      {
	std::cout << "Freeing old map" << std::endl;
	free(mapCells);
      }
    mapSize = size;
    if(mapCells = (T**)malloc(sizeof(T*)*mapSize))
      {
	for (int i = 0 ; i < mapSize; i++)
	  {
	    mapCells[i] = (T*)malloc(sizeof(T)*mapSize);
	  }
	std::cout << "Allocated Memory for map" << std::endl;
      }
    else
      {
	std::cout << "Failed to allocate memory for map" << std::endl;
      }
  }
  void reportMap()
  {
    
  }

 private:
  T** mapCells;
  int mapSize;
};

#endif //MAP_H
