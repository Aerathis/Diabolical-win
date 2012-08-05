#include <iostream>

#include "stdafx.h"

#include "Entity.h"
#include "Object.h"
#include "World.h"

Entity::Entity()
{
  initEntity(0,0,0,"hrk");
}

void Entity::initEntity(int inX, int inY, int inId, std::string inName)
{
  vitals.x = inX;
  vitals.y = inY;
  targetPos.x = (float)inX;
  targetPos.y = (float)inY;
  target = NULL;
  vitals.id = inId;
  vitals.timeAlive = 0;
  vitals.coreTemp = 37;
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
  stats.moveSpeed = 5;

  alive = true;
  nightyBye = false;

  home = NULL;
  priorFrameState.resultState = e_idleFrame;

  carryingResource = Structure::e_none;
}

// A function that sets in the course of action based on the decision made by the brain
void Entity::processDecision(e_brainState decision, World* host, s_frameResolution* resPointer)
{
  switch (decision)
  {
  case e_idle:
    break;
  case e_getFood:
    {
			Object* targetObj = 0;
			float closeDist = (float)100000000000;
			std::vector<Object>::iterator it;
			for (it = host->getObjectList()->begin(); it != host->getObjectList()->end(); ++it)
			{	    
				Object tempObj = *it;
				if (tempObj.pollObject() == Object::e_food)
	      {	      
					float diffX = (float)abs(tempObj.getObjVitals().x - vitals.x);
					float diffY = (float)abs(tempObj.getObjVitals().y - vitals.y);
					float len = sqrt(diffX*diffX+diffY*diffY);
					if (len < closeDist)
					{	
						closeDist = len;
						targetObj = &*it;
					}
	      }
				if (targetObj)
	      {
					resPointer->resultState = e_eatFood;
					resPointer->target = (void*)targetObj;
				}
			}
		}
		break;
  case e_getWater:
    {
			int terSize = host->im_getTerrainMap()->getMapSize();
			int iterCount = 0;
			bool targetPicked = false;
			while (!targetPicked)
			{
				for (int i = iterCount*(-1); i <= iterCount; i++)
				{
					// There's a bug in here with at least one of the getLocationAtCoord params	  
					int y = vitals.y - iterCount;
					y = (y >= 0 ? y : 0);
					int x = vitals.x + i;
					x = (x >= 0 ? x : 0);
					x = (x < terSize ? x : terSize-1);
					creators::e_terrainType terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
					if (terr == creators::e_shallowWater || terr == creators::e_water)
					{
						targetPicked = true;
						s_position* targPos = new s_position();
						targPos->x = (float)x;
						targPos->y = (float)y;
						resPointer->target = (void*)targPos;
					}
					y = vitals.y + iterCount;
					y = (y < terSize ? y : terSize-1);
					terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
					if (terr == creators::e_shallowWater || terr == creators::e_water)
					{
						targetPicked = true;
						s_position* targPos = new s_position();
						targPos->x = (float)x;
						targPos->y = (float)y;
						resPointer->target = (void*)targPos;
					}
					x = vitals.x - iterCount;
					x = (x >= 0 ? x : 0);
					y = vitals.y + i;
					y = (y >= 0 ? y : 0);
					y = (y < terSize ? y : terSize-1);
					terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
					if (terr == creators::e_shallowWater || terr == creators::e_water)
					{
						targetPicked = true;
						s_position* targPos = new s_position();
						targPos->x = (float)x;
						targPos->y = (float)y;
						resPointer->target = (void*)targPos;
					}
					x = vitals.x + iterCount;
					x = (x < terSize ? x : terSize-1);
					terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
					if (terr == creators::e_shallowWater || terr == creators::e_water)
					{
						targetPicked = true;
						s_position* targPos = new s_position();
						targPos->x = (float)x;
						targPos->y = (float)y;
						resPointer->target = (void*)targPos;
					}
	      }
				iterCount++;
			}
			resPointer->resultState = e_drinkWater;
    }
    break;
  case e_takeNap:
    {
			resPointer->resultState = e_nap;
			resPointer->target = NULL;
    }
    break;
  case e_buildStuff:
    {
			std::vector<Structure>* structList = host->getStructureList();
			if (structList->size() > 0)
			{
				std::vector<Structure>::iterator structIt;
				for (structIt = structList->begin(); structIt != structList->end(); ++structIt)
				{
					if (structIt->canStartWork() || structIt->isUnderConstruction())
					{
						resPointer->resultState = e_buildStructure;
						resPointer->target = (void*)&*structIt;
					}		
	      }
			}
			else
			{
				resPointer->resultState = e_idleFrame;
				resPointer->target = NULL;
			}
    }
    break;
  case e_makeHome:
    {       
			resPointer->resultState = e_buildNewHome;
			resPointer->target = NULL;
    }
    break;
  case e_buildHome:
    {
			if (home->needsMats())
			{	   
				resPointer->resultState = e_collectStuff;
				resPointer->target = (void*)home;
			}
			else
			{
				resPointer->resultState = e_buildStructure;
				resPointer->target = (void*)home;
			}
    }
    break;
  }
}

void Entity::resolveFrame(s_frameResolution* resultState, World* host)
{
  switch(resultState->resultState)
    {
    case e_eatFood:
      {
	if (!nightyBye)
	  {
	    Object* targetFood = (Object*)resultState->target;
	    if (vitals.x == targetFood->getObjVitals().x && vitals.y == targetFood->getObjVitals().y)
	      {
		std::cout << "Eat Da Food at " << targetFood->getObjVitals().x << "," << targetFood->getObjVitals().y << "!!" << std::endl;
		stats.hunger = 0;
		host->consumeObject(targetFood);
	      }
	    else
	      {
		moveToTargetLocation(targetFood->getObjVitals().x, targetFood->getObjVitals().y);
	      }
	  }
	else
	  {
	    if (stats.hunger > 800)
	      {
		nightyBye = false;
		std::cout << "Waking up: Extremely hungry" << std::endl;
	      }
	  }
      }
      break;
    case e_drinkWater:
      {
	if (!nightyBye)
	  {
	    s_position* waterPos = (s_position*)resultState->target;      
	    if (vitals.x == waterPos->x && vitals.y == waterPos->y)
	      {
		std::cout << "Drink da watah at " << waterPos->x << "," << waterPos->y << "!!" << std::endl;
		stats.thirst = 0;
	      }
	    else
	      {
		moveToTargetLocation(waterPos->x, waterPos->y);
	      }
	  }
	else
	  {
	    if (stats.thirst > 800)
	      {
		nightyBye = false;
		std::cout << "Waking up: Extremely thirsty" << std::endl;
	      }	  
	  }
      }
      break;
    case e_nap:
      {
	if (!nightyBye)
	  {
	    if (stats.thirst < 800 && stats.hunger < 800)
	      {	      
		std::cout << "Taking a nap" << std::endl;
		nightyBye = true;
	      }
	    else
	      {
		if (stats.thirst > 800)
		  {
		    std::cout << "Can't sleep: Too thirsty" << std::endl;
		    stats.tired = 760;
		  }
		if (stats.hunger > 800)
		  {
		    std::cout << "Can't sleep: Too hungry" << std::endl;
		    stats.tired = 760;
		  }
	      }
	  }
	else if (nightyBye)
	  {
	    if (stats.thirst > 800)
	      {
		std::cout << "Wakes up: Thirsty" << std::endl;
		nightyBye = false;
	      }
	    if (stats.hunger > 800)
	      {
		std::cout << "Wakes up: Hungry" << std::endl;
		nightyBye = false;
	      }
	    if (vitals.coreTemp > 42)
	      {
		std::cout << "Wakes up: Too hot" << std::endl;
		nightyBye = false;
	      }
	    if (vitals.coreTemp < 25)
	      {
		std::cout << "Wakes up: Too cold" << std::endl;
		nightyBye = false;
	      }
	  }
      }
      break;
    case e_buildStructure:
      {
	Structure* buildTarget = (Structure*)resultState->target;       
	if (buildTarget->getObjVitals().x == vitals.x && buildTarget->getObjVitals().y == vitals.y)
	  {	    
	    if (buildTarget->canStartWork())
	      {
		std::cout << "At build target location" << std::endl;
		buildTarget->startConstruction();		
	      }	   
	  }
	else
	  {	    
	    moveToTargetLocation(buildTarget->getObjVitals().x, buildTarget->getObjVitals().y);	    
	  }
      }
      break;
    case e_buildNewHome:
      {
	std::cout << "Building new home" << std::endl;
	home = host->addNewHome(vitals.x, vitals.y);
      }
      break;
    case e_collectStuff:
      {	
	bool headingHome = (carryingResource == Structure::e_none ? false : true);
	if (!headingHome)
	  {
	    std::map<Structure::e_materialType,int> matties = home->getRemainingReq();
	    int numWoods = matties[Structure::e_wood];
	    int numStones = matties[Structure::e_stone];
	    if (!hasTargetPosition)
	      {
		if (numWoods >= numStones)
		  {
		    std::cout << "Going to nearest wood" << std::endl;
		    s_position temp = findNearestObjectOfType(host, Object::e_tree);
		    moveToTargetLocation(temp.x,temp.y);
		    hasTargetPosition = true;
		  }
		else
		  {
		    std::cout << "Going to nearest stone" << std::endl;
		    s_position tempStone = findNearestObjectOfType(host, Object::e_rock);
		    moveToTargetLocation(tempStone.x,tempStone.y);
		    hasTargetPosition = true;
		  }
	      }
	    else
	      {
		if (targetPos.x == vitals.x && targetPos.y == vitals.y)
		  {
		    std::vector<Object>::iterator it;
		    for (it = host->getObjectList()->begin(); it != host->getObjectList()->end(); ++it)
		      {
			Object testObj = *it;
			if (testObj.getObjVitals().x == vitals.x && testObj.getObjVitals().y == vitals.y)
			  {
			    if (testObj.pollObject() == Object::e_tree || testObj.pollObject() == Object::e_rock)
			      {
				carryingResource = (testObj.pollObject() == Object::e_tree ? Structure::e_wood : Structure::e_stone);			   
				hasTargetPosition = false;
			      }
			  }
		      }		  
		  }
	      }
	  }
	else
	  {
	    if (vitals.x == home->getObjVitals().x && vitals.y == home->getObjVitals().y)
	      {
		home->addMaterial(carryingResource);
		carryingResource = Structure::e_none;
		hasTargetPosition = false;	       
	      }
	    else
	      {
		moveToTargetLocation(home->getObjVitals().x, home->getObjVitals().y);
	      }
	  }
      }
      break;
    default:
      break;
    }
}

Brain::s_brainBox Entity::packBrainBox(World* host)
{
  Brain::s_brainBox packed;
  packed.survival.hunger = stats.hunger;
  packed.survival.thirst = stats.thirst;
  packed.survival.tired = stats.tired;
  packed.hasHome = hasHome();
  if (hasHome())
    {
      packed.homeBuilt = getHomePtr()->isCompleted();
      packed.homeBuilding = getHomePtr()->isUnderConstruction();
    }
  else
    {
      packed.homeBuilt = false;
    }
  packed.xPos = vitals.x;
  packed.yPos = vitals.y;
  return packed;
}

void Entity::runFrame(World* host)
{
  // Check to see if the character is alive at all, if not no need to do anything else
  if (alive)
    {
      frameState.resultState = e_idleFrame;
      frameState.target = 0;
      // Runs the decision making and then processes that decision to select a course of action
      Brain::s_brainBox situation = packBrainBox(host);
      processDecision(smarts.runFrame(situation), host, &frameState);      
      if (frameState.resultState != priorFrameState.resultState)
	{
	  std::cout << "resultState changed between frames" << std::endl;
	  std::cout << "Old result state: " << priorFrameState.resultState << std::endl;  	  
	  if (priorFrameState.resultState == e_buildStructure)
	    {	    
	      Structure* oldStruct = (Structure*)priorFrameState.target;
	      if (oldStruct->isCompleted())
		{
		  std::cout << "Stopping construction: Finished" << std::endl;
		}
	      else
		{
		  oldStruct->pauseConstruction();
		  std::cout << "Pausing construction" << std::endl;
		}
	    }	  	  
	}
      // Doing the various vital statistics updating first
      vitals.timeAlive += 1;
      if (vitals.timeAlive % 1 == 0)
	{
	  // The hunger section
	  stats.hunger += 1;
	  if (stats.hunger == 500)
	    {
	      std::cout << "Getting hungry" << std::endl;
	    }
	  else if (stats.hunger == 700)
	    {
	      std::cout << "Getting very hungry" << std::endl;
	    }
	  else if (stats.hunger == 970)
	    {
	      std::cout << "Starving!!" << std::endl;
	    }

	  // The thirsty section
	  stats.thirst += 1;
	  if (stats.thirst == 750)
	    {
	      std::cout << "Is extremely thirsty" << std::endl;
	    }
	  if (stats.thirst == 930)
	    {
	      std::cout << "Is dying of thirst" << std::endl;
	    }

	  // The hot/cold section
	  if (host->im_getWeatherMap()->getLocationAtCoord(vitals.x, vitals.y) != vitals.coreTemp)
	    {
	      vitals.coreTemp = 
		(host->im_getWeatherMap()->getLocationAtCoord(vitals.x, vitals.y) > vitals.coreTemp ? 
		 vitals.coreTemp + 1 : vitals.coreTemp - 1);
	    }
	  if (vitals.coreTemp == 35)
	    {
	      std::cout << "Is feeling cold" << std::endl;
	    }
	  else if (vitals.coreTemp == 32)
	    {
	      std::cout << "Is shivering" << std::endl;
	    }
	  else if (vitals.coreTemp == 28)
	    {
	      std::cout << "Is freezing!!" << std::endl;
	    }
	  if (vitals.coreTemp == 39)
	    {
	      std::cout << "Is feeling warm" << std::endl;
	    }
	  else if (vitals.coreTemp == 42)
	    {
	      std::cout << "Is burning up" << std::endl;
	    }

	  // The sleepy section
	  if (nightyBye)
	    stats.tired -= 50;
	  else
	    stats.tired += 1;
	  if (nightyBye && stats.tired <= 0)
	    {
	      std::cout << "Waking up" << std::endl;
	      nightyBye = false;
	    }
	}

      // The movement section
      if (vitals.timeAlive % stats.moveSpeed == 0)
	{
	  if (vitals.x != targetPos.x)
	    vitals.x = (targetPos.x > vitals.x ? vitals.x + 1 : vitals.x - 1);
	  if (vitals.y != targetPos.y)
	    vitals.y = (targetPos.y > vitals.y ? vitals.y + 1 : vitals.y - 1);
	}
      if (target != NULL)
	{
	  if (vitals.x != target->getVitals().x && vitals.y != target->getVitals().y)
	    {
	      moveToTargetLocation(target->getVitals().x, target->getVitals().y);
	    }
	  else
	    {
	      std::cout << "Target Entity Reached" << std::endl;
	      target = NULL;
	    }
	}

      // Check to see for any adverse effects based on the current situation
      if (stats.hunger == 1000)
	{
	  std::cout << "Has starved to death" << std::endl;
	  alive = false;
	}
      if (stats.thirst == 1000)
	{
	  std::cout << "Has died of dehydration" << std::endl;
	  alive = false;
	}
      if (vitals.coreTemp == 20)
	{
	  std::cout << "Has frozen to death" << std::endl;
	  alive = false;
	}
      if (vitals.coreTemp == 46)
	{
	  std::cout << "Has died from the heat" << std::endl;
	  alive = false;
	}
      if (vitals.timeAlive == 10000000000)
	{
	  std::cout << "Has passed away of old age" << std::endl;
	  alive = false;
	}

      if (vitals.timeAlive % 1 == 0)
	resolveFrame(&frameState, host);
      priorFrameState = frameState;
    }
}

void Entity::moveToTargetLocation(float x, float y)
{
  targetPos.x = x;
  targetPos.y = y;
}

void Entity::moveToTargetLocation(int x, int y)
{
  targetPos.x = (float)x;
  targetPos.y = (float)y;
}

void Entity::moveToTarget(Entity* targ)
{
  target = targ;
}

Entity::s_vitals Entity::getVitals()
{
  return vitals;
}

Entity::s_stats Entity::getStats()
{
  return stats;
}

bool Entity::hasHome()
{
  if (home == NULL)
    {
      return false;
    }
  else
    {
      return true;
    }
}

Structure* Entity::getHomePtr()
{
  return home;
}

Entity::s_position Entity::findNearestObjectOfType(World* host, Object::e_objectType checkType)
{
  s_position temp;
  float nearDist = 10000000;
  std::vector<Object>::iterator it;
  for (it = host->getObjectList()->begin(); it != host->getObjectList()->end(); ++it)
    {
      Object obj = *it;
      if (obj.pollObject() == checkType)
	{
	  float diffX = (float)abs(obj.getObjVitals().x - vitals.x);
	  float diffY = (float)abs(obj.getObjVitals().y - vitals.y);
	  float len = sqrt(diffX*diffX+diffY*diffY);
	  if (len < nearDist)
	    {
	      nearDist = len;
	      temp.x = (float)obj.getObjVitals().x;
	      temp.y = (float)obj.getObjVitals().y;
	    }
	}
    }
  return temp;
}
