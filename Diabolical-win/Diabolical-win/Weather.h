#ifndef _WEATHER_H
#define _WEATHER_H

#include "Creators.h"
#include "Map.h"
#include "World.h"

class World;

class Weather
{
 public:
  Weather();

  void initWeather(World* world);
  void setWeatherMapSize(int size);
  bool runFrame();

  Map<int>* getWeatherMap();
  Map<float>* getPrecipMap();
  
 private:
  Map<int> weatherMap;
  Map<float> precipMap;

  void initialSim(World* world);
};

#endif //WEATHER_H
