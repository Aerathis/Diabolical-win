#ifndef _OBJECT_H
#define _OBJECT_H

class Object
{
 public:

  enum e_objectType 
  {
    e_food,
    e_fire,
    e_tree,
    e_rock,
    e_structure
  };

  struct s_objVitals
  {
    int x;
    int y;
  };

  Object();
  Object(e_objectType type);
  void initObject(int x, int y, e_objectType inType);
  
  void placeObject(int x, int y);
  s_objVitals getObjVitals();

  e_objectType pollObject();

 private:
  e_objectType type;
  s_objVitals vitals;
};

#endif //OBJECT_H
