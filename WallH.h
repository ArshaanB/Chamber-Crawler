#ifndef __WALLH_H__
#define __WALLH_H__
#include "Terrain.h"

class WallH final: public Terrain{
	public:
	WallH(int x, int y);
	~WallH();
	SubjectType getSubject() override;
};
#endif
