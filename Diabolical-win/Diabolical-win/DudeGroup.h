#ifndef _DUDEGROUP_H
#define _DUDEGROUP_H

#include <vector>
#include <list>

#include "Entity.h"

class DudeGroup
{
 public:

  DudeGroup();
  
  bool requestEntry(Entity* supplicant);
  void addToGroup(Entity* supplicant);
  void removeFromGroup(Entity* trouble);

 private:

  enum e_ruleType
  {   
  };


  bool isInGroup(Entity* dude);

  std::vector<Entity*> members;
  std::list<e_ruleType> rules;
};

#endif //DUDEGROUP_H
