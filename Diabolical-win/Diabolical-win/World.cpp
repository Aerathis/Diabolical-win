#include "stdafx.h"
#include "World.h"

World* World::gameWorld;

World::World()
{
  // Normal constructor business. Nulling things out and all that.
  worldCreated = false;
}

void World::initWorld()
{
  // Initializing the world parameters, at the moment there's no method to use anything but these defaults. 

  worldMap.setSize(0);
  terrainMap.setSize(0);
  worldWeather.setWeatherMapSize(0);
	
  
  srand(0);

  selected = NULL;
}

// Returns a pointer to the weatherMap, which shouldn't be modified outside of this file
Map<int>* World::im_getWeatherMap()
{
  // This is only to be used as immutable
  return worldWeather.getWeatherMap();
}

Map<creators::e_terrainType>* World::im_getTerrainMap()
{
  return &terrainMap;
}
// Returns a pointer to the list of objects in the world.
std::vector<Object>* World::getObjectList()
{
  return &objects;
}

std::vector<Structure>* World::getStructureList()
{
  return &structures;
}

// Returns a pointer to the worldMap, which shouldn't be modified outside of this file
Map<double>* World::im_getWorldMap()
{
  // This is only to be used as immutable
  return &worldMap;
}

bool World::consumeObject(Object* consumed)
{
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    {
      if (&*it == consumed)
	{
	  objects.erase(it);
	  return true;
	}
    }
  return false;
}

bool World::collectResource(Object* resource)
{
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    {
      if (&*it == resource)
	{
	  objects.erase(it);
	  return true;
	}
    }
  return false;
}

Structure* World::addNewHome(int x, int y)
{
  Structure home;
  home.placeObject(x,y);
  structures.push_back(home);
  return &structures.back();
}
 
void World::runFrame()
{
  
  // The update function, this is going to be run when there's no input
  //worldWeather.runFrame();
  if (rand()%10000000 == 1)
    {
      createNewFood();
    }
  std::vector<Entity>::iterator it;
  for (it = citizens.begin(); it != citizens.end(); ++it)
    {
      it->runFrame(this);
    }
  std::vector<Structure>::iterator structIt;
  for (structIt = structures.begin(); structIt != structures.end(); ++structIt)
    {
      structIt->runFrame();
    }
}

void World::runFrameWithInput(Event* Event)
{
  // The other update function, this is going to be run when there is input. 
  // If the event is a click on a unit or structure then we set it as the selected entity

  // Most of the code in this function is pretty much solely for testing purposes
  // Actual input will be handled in a much more sane fashion in a separate location
  if (Event->type == input::e_keyEvent)
  {
    // Handle when the "C" key is pressed
    if(Event->key == DKeysym::DK_Key_c)
	  {
	    if (!worldCreated)
	    {
	      worldMap.setSize(4);
	      terrainMap.setSize(4);
	      creators::fillTerrain(&worldMap);
	      std::cout << std::endl;
	      creators::fillTerrainDetails(&terrainMap, &worldMap);
	      std::cout << std::endl;
	      creators::placeResources(&objects, &terrainMap);

				worldModel = creators::createWorldModel(&worldMap);
        worldWeather.initWeather(this);
	      worldCreated = true;
	    }
	    else if(worldCreated)
	    {
	      Entity newEnt;
	      newEnt.initEntity(0,0,0,"test");
	      std::cout << "New Entity created" << std::endl;
	      citizens.push_back(newEnt);
	      std::cout << "Entity added to citizens" << std::endl;
	    }
	  }
      // Handle when the "P" key is pressed
    else if (Event->key == DKeysym::DK_Key_p)
	  {
	    if (selected)
	    {
	      std::cout << "Selected report" << std::endl;
	      std::cout << "Position: (";
	      std::cout << selected->getVitals().x << "," << selected->getVitals().y << ")";
	      std::cout << " Time Alive: " << selected->getVitals().timeAlive;
	      std::cout << " Hungry: " << selected->getStats().hunger;
	      std::cout << " Tired: " << selected->getStats().tired << std::endl;
	    }
	    else
	    {
	      std::vector<Object>::iterator it;
	      for (it = objects.begin(); it != objects.end(); ++it)
		    {
		      std::cout << it->pollObject() << std::endl;
		    }
	    }
	  }
    // Handle when the "S" key is pressed
    else if (Event->key == DKeysym::DK_Key_s)
	  {
	    if (selected)
	    {
	      std::cout << "Clearing Selection" << std::endl;
	      selected = NULL;
	    }
	    else
	    {
	      std::cout << "Creating new structure" << std::endl;
	      Structure temp;
	      temp.placeObject(0,0);
	      structures.push_back(temp);
	      std::cout << "Structure added to list" << std::endl;
	    }
	  }
    // Handle when the "1" key is pressed
    else if (Event->key == DKeysym::DK_Key_1)
	  {
	    if (citizens.size() >= 1 && selected != &citizens[0])
	    {
	      selected = &citizens[0];
	      std::cout << "First entity selected" << std::endl;
	    }
	  }
    // Handle when the "2" key is pressed
    else if (Event->key == DKeysym::DK_Key_2)
	  {
	    if (citizens.size() >= 2 && selected != &citizens[1])
	    {
	      selected = &citizens[1];
	      std::cout << "Second entity selected" << std::endl;
	    }
	  }
    // Handle when the "W" key is pressed
    else if (Event->key == DKeysym::DK_Key_w)
	  {
	    worldWeather.getWeatherMap()->setLocationAtCoord(0,0,33);
	  }
    // Handle when the "T" key is pressed
    else if (Event->key == DKeysym::DK_Key_t)
	  {
	    if (selected != &citizens[1])
	    {
	      std::cout << "Moving selected entity to entity 1" << std::endl;
	      selected->moveToTarget(&citizens[1]);
	    }
	  }
    // Handle when the "M" key is pressed
    else if (Event->key == DKeysym::DK_Key_m)
	  {
	    if (structures.size() > 0)
	    {
	      std::cout << "Starting construction on first structure" << std::endl;
	      structures[0].startConstruction();	      
	    }
	  }
    else if (Event->key == DKeysym::DK_Key_r)
	  {
	    if (selected)
	    {	   
	      organizations[0].removeFromGroup(selected);
	    }
	    else
	    {
	      std::vector<Structure>::iterator it;
	      for (it = structures.begin(); it != structures.end(); ++it)
		    {
		      Structure temp = *it;
		      temp.structureReport();
		    }
	    }
	  }
    else if (Event->key == DKeysym::DK_Key_o)
	  {	 
	    createNewFood();
	  }
    else if (Event->key == DKeysym::DK_Key_f)
	  {
	    createNewFire();
	  }
    else if (Event->key == DKeysym::DK_Key_g)
	  {
	    if (selected)
	    {
	      if (organizations[0].requestEntry(selected))
		    {
		      organizations[0].addToGroup(selected);
		    }		  	    
	    }
	    else
	    {
	      DudeGroup newGroup;
	      organizations.push_back(newGroup);
	    }
	  }
		// Handle when the up cursor key is pressed
		else if (Event->key == DKeysym::DK_Up)
		{
			Rotation camRot = Renderer::renderer.getRenderCamera()->getViewRotation();
			float yrotrad = camRot.getY();
			float xrotrad = camRot.getX();
			yrotrad = yrotrad/180.0f*M_PI;
			xrotrad = xrotrad/180.0f*M_PI;
			Vector3 trans = Vector3((float)(sin(yrotrad)),-(float)(sin(xrotrad)),-(float)(cos(yrotrad)));
			Renderer::renderer.getRenderCamera()->moveCamera(camRot, trans);
		}
		// Handle when the down cursor key is pressed
		else if (Event->key == DKeysym::DK_Down)
		{
			Rotation camRot = Renderer::renderer.getRenderCamera()->getViewRotation();
			float yrotrad = camRot.getY();
			float xrotrad = camRot.getX();
			yrotrad = yrotrad/180.0f*M_PI;
			xrotrad = xrotrad/180.0f*M_PI;
			Vector3 trans = Vector3(-(float)(sin(yrotrad)), (float)(sin(xrotrad)), (float)(cos(yrotrad)));
			Renderer::renderer.getRenderCamera()->moveCamera(camRot, trans);
		}
		// Handle when the left cursor key is pressed
		else if (Event->key == DKeysym::DK_Left)
		{
			Rotation camRot = Renderer::renderer.getRenderCamera()->getViewRotation();
			float yrotrad = camRot.getY();
			float xrotrad = camRot.getX();
			yrotrad = yrotrad/180.0f*M_PI;
			xrotrad = xrotrad/180.0f*M_PI;
			Vector3 trans = Vector3(-(float)(cos(yrotrad)), Renderer::renderer.getRenderCamera()->getViewPosition().getY(),-(float)(sin(yrotrad)));
			Renderer::renderer.getRenderCamera()->moveCamera(camRot, trans);
		}
		// Handle when the right cursor key is pressed
		else if (Event->key == DKeysym::DK_Right)
		{
			Rotation camRot = Renderer::renderer.getRenderCamera()->getViewRotation();
			float yrotrad = camRot.getY();
			float xrotrad = camRot.getX();
			yrotrad = yrotrad/180.0f*M_PI;
			xrotrad = xrotrad/180.0f*M_PI;
			Vector3 trans = Vector3((float)(cos(yrotrad)),Renderer::renderer.getRenderCamera()->getViewPosition().getY(),(float)(sin(yrotrad)));
			Renderer::renderer.getRenderCamera()->moveCamera(camRot, trans);
		}
  }
	// Handle any mouse input
  else if (Event->type == input::e_mouseEvent)
  {
    if (Event->mouseEvent.button == input::e_rButton)
    {
			Rotation rot = Rotation((float)Event->mouseEvent.xPos, (float)Event->mouseEvent.yPos,0.0f);
    }
  }
  // Finally run the standard frame
  runFrame();
}

void World::createNewFood()
{
  int objX = (rand()%20);
  int objY = (rand()%20);
  Object newObj;
  newObj.initObject(objX,objY,Object::e_food);
  std::cout << "New food object created" << std::endl;
  objects.push_back(newObj);
  std::cout << "Object added to world at " << objX << "," << objY << std::endl;
}

void World::createNewFire()
{
  int objX = (rand()%20);
  int objY = (rand()%20);
  Object newObj;
  newObj.initObject(objX,objY,Object::e_fire);
  std::cout << "New fire created" << std::endl;
  objects.push_back(newObj);
  std::cout << "Object added to world at " << objX << "," << objY << std::endl;
}
