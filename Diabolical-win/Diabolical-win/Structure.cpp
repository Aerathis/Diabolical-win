#include "stdafx.h"
#include "Structure.h"

#include <iostream>

Structure::Structure() : Object(Object::e_structure)
{
  structType = e_home;
  completionPercent = 0;
  constructionTimeScale = 1;
  completed = false;
  underConstruction = false;
  needMats = false;
  ownable = true;
  owner = NULL;
  materialReqs[e_wood] = 10;
  materialReqs[e_stone] = 1;
  totalMats = materialReqs[e_wood] + materialReqs[e_stone];
  materialsPresent[e_wood] = 0;
  materialsPresent[e_stone] = 0;
}

void Structure::runFrame()
{
  if (underConstruction)
    {
      completionPercent += 1 * constructionTimeScale;
      int currentOutMats = materialReqs[e_wood] + materialReqs[e_stone];
      int remainScale = totalMats - currentOutMats;
      int perc = int((float)COMPLETE/(float)totalMats);      
      if (completionPercent >= (perc * remainScale) && completionPercent != COMPLETE -1)
	{	  
	  if (materialsPresent[e_wood] == 0 && materialsPresent[e_stone] == 0 && 
	      remainScale != totalMats)
	    {
	      std::cout << "Construction Paused: Need materials" << std::endl;
	      std::cout << completionPercent << std::endl;
	      std::cout << perc << std::endl;
	      std::cout << remainScale << std::endl;
	      underConstruction = false;
	      needMats = true;
	    }
	  else
	    {
	      bool needWood = (materialReqs[e_wood] > 0 ? true : false);
	      bool hasWood = (materialsPresent[e_wood] > 0 ? true : false);
	      bool needStone = (materialReqs[e_stone] > 0 ? true : false);
	      bool hasStone = (materialsPresent[e_stone] > 0 ? true : false);
	      if (needWood && needStone)
		{
		  if(!hasWood)
		    {
		      materialsPresent[e_stone] -= 1;
		      materialReqs[e_stone] -= 1;
		      std::cout << "Used 1 stone in construction" << std::endl;		      
		    }
		  else
		    {
		      materialsPresent[e_wood] -= 1;
		      materialReqs[e_wood] -= 1;
		      std::cout << "Used 1 wood in construction" << std::endl;
		      std::cout << materialReqs[e_wood] << std::endl;
		    }
		}
	      else if (needWood && !needStone)
		{
		  if (hasWood)
		    {
		      materialsPresent[e_wood] -= 1;
		      materialReqs[e_wood] -= 1;
		      std::cout << "Used 1 wood in construction" << std::endl;
		      std::cout << materialReqs[e_wood] << std::endl;
		    }
		  else
		    {
		      std::cout << "Construction Paused: Need wood" << std::endl;
		      underConstruction = false;
		      needMats = true;
		    }
		}
	      else if (needStone && !needWood)
		{
		  if (hasStone)
		    {
		      materialsPresent[e_stone] -= 1;
		      materialReqs[e_stone] -= 1;
		      std::cout << "Used 1 stone in construction" << std::endl;
		      std::cout << materialReqs[e_stone] << std::endl;
		    }
		  else
		    {
		      std::cout << "Construction Pause: Need stone" << std::endl;
		      underConstruction = false;
		      needMats = true;
		    }
		}
	    }
	}
      if (completionPercent >= COMPLETE - 1)
	{
	  completionPercent = COMPLETE;
	  completed = true;
	  underConstruction = false;
	  std::cout << "Construction completed" << std::endl;
	}
    }
}

bool Structure::canStartWork()
{
  if (completed || underConstruction || needMats)
    {
      return false;
    }
  else
    {
      return true;
    }
}

bool Structure::isUnderConstruction()
{
  return underConstruction;
}

bool Structure::isCompleted()
{
  return completed;
}

bool Structure::canHaveOwner()
{
  if (ownable)
    {
      if (owner == NULL)
	{
	  return true;
	}
      else
	{
	  return false;
	}
    }
  else
    {
      return false;
    }
}

bool Structure::needsMats()
{
  return needMats;
}

void Structure::changeOwner(Entity* newOwner)
{
  owner = newOwner;
}

void Structure::structureReport()
{
  std::cout << "Type: " << structType << std::endl;
  if (completed)
    {
      std::cout << "Built" << std::endl;
    }
  else
    {
      std::cout << completionPercent << "% completed" << std::endl;
    }
}

void Structure::startConstruction()
{
  if (!completed)
    {
      if (completionPercent == 0)
	{
	  std::cout << "Starting construction" << std::endl;
	}
      else
	{
	  std::cout << "Resuming construction" << std::endl;
	}
      underConstruction = true;
    }
  else
    {
      std::cout << "Can't build this, it's already built" << std::endl;
    }
}

void Structure::pauseConstruction()
{
  if (underConstruction)
    {
      underConstruction = false;
    }
  else
    {
      std::cout << "Can't pause construction: Object not currently under construction" << std::endl;
    }
}

std::map<Structure::e_materialType,int> Structure::getRemainingReq()
{
  std::map<e_materialType,int> remain;
  remain[e_wood] = materialReqs[e_wood] - materialsPresent[e_wood];
  remain[e_stone] = materialReqs[e_stone] - materialsPresent[e_stone];
  return remain;
}

void Structure::addMaterial(e_materialType resource)
{
  materialsPresent[resource] += 1;
  if (materialsPresent[e_wood] == materialReqs[e_wood] && materialsPresent[e_stone] == materialReqs[e_stone])
    {
      needMats = false;
    }
}
