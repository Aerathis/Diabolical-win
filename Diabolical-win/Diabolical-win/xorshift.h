#ifndef _XORSHIFT_H
#define _XORSHIFT_H

class ShiftRand
{
 public:
  ShiftRand();
  
  int next();

  void setSeed(int seed);
 private:
  int x;
  int y;
  int z;
  int w;
  
};

#endif //XORSHIFT_H
