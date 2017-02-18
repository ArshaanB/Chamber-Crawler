#ifndef __DOOR_H__
#define __DOOR_H__
#include "Terrain.h"

class Door final:public Terrain{
  public:
    Door(int x, int y);
    ~Door();
    SubjectType getSubject() override;
};
#endif
