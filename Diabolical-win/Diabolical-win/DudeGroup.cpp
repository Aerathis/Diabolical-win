#include "stdafx.h"
#include "DudeGroup.h"

#include <iostream>

DudeGroup::DudeGroup()
{
  std::cout << "Creating new dudegroup" << std::endl;  
}

bool DudeGroup::requestEntry(Entity* supplicant)
{

  if (isInGroup(supplicant))
    {
      std::cout << "Dude already in group" << std::endl;
      return false;
    }
  if (rules.size() == 0)
    return true;

  std::cout << "Group entry denied" << std::endl;
  return false;
}

void DudeGroup::addToGroup(Entity* supplicant)
{
  std::cout << "Adding dude to group" << std::endl;
  members.push_back(supplicant);
  std::cout << members.size() << std::endl;
}

void DudeGroup::removeFromGroup(Entity* trouble)
{

  bool found = false;
  std::vector<Entity*>::iterator it;
  std::cout << "Searching for trouble in members" << std::endl;
  for (it = members.begin(); it != members.end(); ++it)
    {
      if (found)
	break;
      Entity* temp = *it;
      if (temp == trouble)
	{
	  found = true;
	  members.erase(it);
	}         
    }
  if (found)
    {
      std::cout << "Dude removed from group" << std::endl;
    }
  else
    {
      std::cout << "Dude not found in group" << std::endl;
    }
}

bool DudeGroup::isInGroup(Entity* dude)
{
  std::cout << "Searching for dude in group" << std::endl;
  bool found = false;
  std::vector<Entity*>::iterator it;
  for (it = members.begin(); it != members.end(); ++it)
    {
      if (found)
	break;
      Entity* temp = *it;
      if (temp == dude)
	{
	  found = true;
	}
    }
  return found;
}
