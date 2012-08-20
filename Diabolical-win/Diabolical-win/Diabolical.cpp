#include "stdafx.h"
#include "Diabolical.h"

#include <iostream>

Diabolical::Diabolical()
{
  running = true;
}

bool Diabolical::onInit()
{
  std::cout << "Starting initialization" << std::endl;
  std::cout << "World initialization" << std::endl;
  gameWorld.initWorld();
  std::cout << "World initialization complete" << std::endl;

  return true;
}

void Diabolical::onLoop()
{
  gameWorld.runFrame();
}

bool Diabolical::onEvent(Event event)
{
  if (event.type == input::e_keyEvent && event.key == DKeysym::DK_Escape)
    running = false;

  gameWorld.runFrameWithInput(&event);
  return true;
}

void Diabolical::onRender()
{
  if (gameWorld.im_getWorldMap()->getMapSize() > 0)
	{
		gameWorld.frameDraw();
	}
	else
	{
		//Renderer::renderer.testRender();
	}
}

void Diabolical::onExecute()
{           
  while (!eventQueue.empty())
    {
      onEvent(eventQueue.front());
      eventQueue.pop_front();
    }
  onLoop();
  onRender();
}