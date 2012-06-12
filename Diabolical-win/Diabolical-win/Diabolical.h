#ifndef _DIABOLICAL_H
#define _DIABOLICAL_H

#include <queue>

#include "Input.h"
#include "Renderer.h"
#include "World.h"

typedef input::s_DEvent Event;

class Diabolical
{
 private:
  bool running;
  World gameWorld;
  Renderer renderer;
  std::deque<Event> eventQueue;

 public:
  Diabolical();
  
  bool isRunning()
  {
    return running;
  }

  void addEvent(Event newEvent)
  {
    eventQueue.push_back(newEvent);
  }

  void onExecute();
  bool onInit();
  bool onEvent(Event);
  void onLoop();
  void onRender();
  void onCleanup();

  void newEvent(Event);
};

#endif //DIABOLICAL_H
