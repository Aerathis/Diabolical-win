#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#define COMPLETE 1000

#include <map>

#include "Object.h"

class Entity;

class Structure : public Object
{
 public:
  enum e_structType
  {
    e_home
  };

  enum e_materialType
  {
    e_wood,
    e_stone,
    e_none
  };

  Structure();
  
  void runFrame();
  bool canStartWork();
  bool isUnderConstruction();
  bool isCompleted();
  bool canHaveOwner();
  bool needsMats();
  void changeOwner(Entity* newOwner);
  void startConstruction();
  void pauseConstruction();
  std::map<e_materialType,int> getRemainingReq();
  void addMaterial(e_materialType res);
  
  void structureReport();

 private:
  e_structType structType;
  int completionPercent;
  int constructionTimeScale;
  int totalMats;
  bool completed;
  bool underConstruction;
  bool needMats;
  bool ownable;
  std::map<e_materialType,int> materialReqs;
  std::map<e_materialType,int> materialsPresent;
  
  Entity* owner;
};

#endif //STRUCTURE_H
