#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <vector>
#include <math.h>

#include "Brain.h"
#include "Map.h"
#include "Structure.h"

class World;

class Entity
{

 public:

  enum e_frameState
  {
    e_eatFood,
    e_drinkWater,
    e_nap,
    e_buildStructure,
    e_buildNewHome,
    e_collectStuff,
    e_idleFrame
  };

  struct s_position
  {
    float x;
    float y;
  };
  struct s_frameResolution
  {
    e_frameState resultState;
    void* target;
  };

  struct s_skills
  {
  };

  struct s_stats
  {
    int hunger;
    int thirst;
    int tired;
    int moveSpeed;
    s_skills skills;
  };

  struct s_vitals
  {
    int x;
    int y;
    int id;
    int timeAlive;
    int coreTemp;
    std::string name;
  };

  Entity();

  void initEntity(int x, int y, int id, std::string name);

  void runFrame(World* host);

  void moveToTargetLocation(float x, float y);
  void moveToTargetLocation(int x, int y);
  void moveToTarget(Entity* targ);

  s_vitals getVitals();
  s_stats getStats();
  s_skills getSkills();

  bool hasHome();
  Structure* getHomePtr();

 private:
  s_vitals vitals;
  s_stats stats;

  bool alive;
  bool nightyBye;
  bool hasTargetPosition;
  s_position targetPos;
  Entity* target;
  Brain smarts;
  e_brainState decision;
  s_frameResolution frameState;
  s_frameResolution priorFrameState;

  Structure* home;
  Structure::e_materialType carryingResource;

  void processDecision(e_brainState decision, World* host, s_frameResolution* result);
  void resolveFrame(s_frameResolution* frState, World* host);
  Brain::s_brainBox packBrainBox(World* host);

  s_position findNearestObjectOfType(World* host, Object::e_objectType checkType);
};

#endif //ENTITY_H
