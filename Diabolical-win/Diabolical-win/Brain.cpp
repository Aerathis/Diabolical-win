#include "stdafx.h"
#include "Brain.h"

#include <iostream>
#include "Entity.h"

Brain::Brain()
{
  currentSituation.survival = 0;
  currentSituation.work = 0;
  currentSituation.entertainment = 0;
}

Brain::~Brain()
{
}

int Brain::evaluateSurvival(Brain::s_brainBox situation)
{
  int food = situation.survival.hunger;
  int water = situation.survival.thirst;
  int sleepy = situation.survival.tired;
  return food+water+sleepy;
}

int Brain::evaluateWork(Brain::s_brainBox situation)
{
  int needHome = (situation.hasHome ? 0 : 1500);
  int buildHome = (situation.homeBuilt ? 0 : 1000);
  return needHome + buildHome;
}

e_brainState Brain::runFrame(Brain::s_brainBox situation)
{

  currentSituation.survival = evaluateSurvival(situation);
  currentSituation.work = evaluateWork(situation);
  currentSituation.entertainment = 0;

  e_brainState newState = currentState;

  //std::cout << "Surival rating: " << currentSituation.survival << std::endl;
  //std::cout << "Work rating: " << currentSituation.work << std::endl;
  if ( currentSituation.survival >= currentSituation.work)
    {     
      if (situation.survival.tired < 370)
	newState = e_idle;
      if (situation.survival.thirst > 500)
	newState = e_getWater;
      if (situation.survival.hunger > 500)
	newState = e_getFood;
      if (situation.survival.thirst < 500 && situation.survival.hunger < 500)
	newState = e_idle;
      if (situation.survival.tired > 800)
	newState = e_takeNap;     
    }
  else
    {      
      newState = makeDecision(situation);
    }

  if (situation.exclusions.size() != 0)
    {
      if (listContains(situation.exclusions,newState))
	{
	  newState = e_idle;
	}
    }
  // If the brain has changed its mind since the last time it made a decision
  // it announces that change and applies it to the current decision
  if (newState != currentState)
    {
      std::cout << "Brain state changed" << std::endl;
      std::cout << "New State: " << newState << std::endl;
      currentState = newState;
    }
  return currentState;
}

e_brainState Brain::makeDecision(s_brainBox situation)
{
  if (situation.hasHome)
    {
      if (!situation.homeBuilt || situation.homeBuilding)
	{
	  return e_buildHome;
	}
      else
	{
	  return e_idle;
	}
    }
  else
    {
      return e_makeHome;
    }
}

bool Brain::listContains(std::list<e_brainState> inList, e_brainState checkFor)
{
  bool results = false;
  std::list<e_brainState>::iterator it;
  for (it = inList.begin(); it != inList.end(); ++it)
    {
      if (*it == checkFor)
	{
	  results = true;
	}
    }

  return results;
}
