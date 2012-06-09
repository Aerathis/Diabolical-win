#include "stdafx.h"
#include "Weather.h"

Weather::Weather()
{
}

void Weather::setWeatherMapSize(int size)
{
  weatherMap.setSize(size);
}

Map<int>* Weather::getWeatherMap()
{
  return &weatherMap;
}

bool Weather::runFrame()
{
  return true;
}
