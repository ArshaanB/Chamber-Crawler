#ifndef __EMPTYFLOOR_H__
#define __EMPTYFLOOR_H__
#include "Terrain.h"

class EmptyFloor final:public Terrain{
  public:
    EmptyFloor(int x, int y);
    ~EmptyFloor();
    SubjectType getSubject() override;
};
#endif
