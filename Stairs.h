#ifndef __STAIRS_H__
#define __STAIRS_H__
#include "Terrain.h"

class Stairs final:public Terrain{
  public:
    Stairs(int x, int y);
    ~Stairs();
	SubjectType getSubject() override;
};
#endif
