#include "stdafx.h"
#include "Weather.h"

Weather::Weather()
{
}

void Weather::initWeather(World* world)
{
  weatherMap.setSize(world->im_getWorldMap()->getMapSize());
  precipMap.setSize(world->im_getWorldMap()->getMapSize());
  creators::fillWeather(&weatherMap);
  creators::fillPrecipitation(&precipMap);
  initialSim(world);
}

void Weather::setWeatherMapSize(int size)
{
  weatherMap.setSize(size);
}

Map<int>* Weather::getWeatherMap()
{
  return &weatherMap;
}

Map<float>* Weather::getPrecipMap()
{
  return &precipMap;
}

bool Weather::runFrame()
{
  return true;
}

void Weather::initialSim(World* world)
{

}