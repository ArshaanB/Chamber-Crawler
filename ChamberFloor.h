#ifndef __CHAMBERFLOOR_H__
#define __CHAMBERFLOOR_H__
#include "Terrain.h"

class ChamberFloor final: public Terrain{
  public:
   ChamberFloor(int x, int y);
   ~ChamberFloor();
   SubjectType getSubject() override;
  };
#endif

