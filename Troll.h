#ifndef __TROLL_H__
#define __TROLL_H__
#include "NonPlayable.h"

class Troll final: public NonPlayable {
	public:
	Troll(int x, int y);
	SubjectType getSubject() override;
};
#endif
