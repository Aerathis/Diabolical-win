#ifndef _WORLD_H
#define _WORLD_H

//#include <SDL/SDL.h>

#include <vector>
#include <stdlib.h>
//#include "btBulletDynamicsCommon.h"

#include "Creators.h"
#include "DudeGroup.h"
#include "Entity.h"
#include "Input.h"
#include "Map.h"
#include "Object.h"
//#include "Player.h"
#include "Structure.h"
#include "Weather.h"

typedef input::s_DEvent Event;

class World
{

 private:
  //btAlignedObjectArray<btCollisionShape*> collisionShapes;
  //btDefaultCollisionConfiguration* collisionConfiguration;
  //btCollisionDispatcher* dispatcher;
  //btBroadphaseInterface* overlappingPairCache;
  //btSequentialImpulseConstraintSolver* solver;
  //btDiscreteDynamicsWorld* dynamicsWorld;

  //Player* player;
  Entity* selected;

  std::vector<Entity> citizens;
  std::vector<Object> objects;
  std::vector<Structure> structures;
  std::vector<DudeGroup> organizations;
  Map<double> worldMap;
  Map<creators::e_terrainType> terrainMap;
  Weather worldWeather;

  bool worldCreated;

  void createNewFood();
  void createNewFire();

 public:
  World();
  void initWorld();
  
  //btDiscreteDynamicsWorld* getWorld();
  //Player* getPlayerPtr();
  Map<int>* im_getWeatherMap();
  Map<double>* im_getWorldMap();
  Map<creators::e_terrainType>* im_getTerrainMap();
  std::vector<Object>* getObjectList();
  std::vector<Structure>* getStructureList();

  //void registerPlayer();

  bool consumeObject(Object* consumed);
  bool collectResource(Object* resource);
  Structure* addNewHome(int x, int y);

  void runFrame();
  void runFrameWithInput(Event* Event);

};

#endif //WORLD_H
