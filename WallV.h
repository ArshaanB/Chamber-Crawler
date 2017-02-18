#ifndef __WALL_H__
#define __WALL_H__
#include "Terrain.h"

class WallV final: public Terrain{
  public:
    WallV(int x, int y);
    ~WallV();
    SubjectType getSubject() override;
};
#endif
