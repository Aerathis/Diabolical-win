#include "stdafx.h"
#include "Object.h"

Object::Object()
{
  vitals.x = 0;
  vitals.y = 0;
  type = Object::e_food;
}

Object::Object(Object::e_objectType inType)
{
  Object();
  type = inType;
}

void Object::initObject(int x, int y, Object::e_objectType inType)
{
  vitals.x = x;
  vitals.y = y;
  type = inType;
}

void Object::placeObject(int x, int y)
{
  vitals.x = x; 
  vitals.y = y;
}

Object::s_objVitals Object::getObjVitals()
{
  return vitals;
}

Object::e_objectType Object::pollObject()
{
  return type;
}
