#include "stdafx.h"
#include "xorshift.h"

ShiftRand::ShiftRand()
{
  x = 123456789;
  y = 362436069;
  z = 521288629;
  w = 88675123;
}

int ShiftRand::next()
{
  int t;
  
  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

void ShiftRand::setSeed(int seed)
{
  w = seed;
}
