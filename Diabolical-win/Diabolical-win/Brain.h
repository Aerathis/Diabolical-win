#ifndef _BRAIN_H
#define _BRAIN_H

#include <list>

class Entity;

enum e_brainState
  {
    e_idle,
    e_getFood,
    e_getWater,
    e_takeNap,
    e_buildStuff,
    e_buildHome,
    e_makeHome
  };

class Brain
{
  // This brain is the very basicest of brains. It is only really meant to deal with the 
  // Most basic of survival stuff, other more complicated brains are likely to have more 
  // Interesting thought processes. 

 public:
  
  struct s_survival
  {
    int hunger;
    int thirst;
    int tired;
  };

  struct s_brainBox
  {
    s_survival survival;
    bool hasHome;
    bool homeBuilt;
    bool homeBuilding;
    int xPos;
    int yPos;
    std::list<e_brainState> exclusions;
  };

  Brain();
  ~Brain();

  e_brainState runFrame(s_brainBox situation);

 private:

  struct s_decisionFactors
  {
    int survival;
    int work;
    int entertainment;
  };

  e_brainState currentState;
  s_decisionFactors currentSituation;

  e_brainState makeDecision(s_brainBox situation);
  int evaluateSurvival(s_brainBox situation);
  int evaluateWork(s_brainBox situation);

  bool listContains(std::list<e_brainState> inList, e_brainState checkFor);
};

#endif //BRAIN_H
