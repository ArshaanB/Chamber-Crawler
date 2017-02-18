#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "NonPlayable.h"

class Goblin final: public NonPlayable {
	public:
    Goblin(int x, int y);
	SubjectType getSubject() override;
};
#endif
