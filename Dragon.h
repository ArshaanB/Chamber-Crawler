#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "NonPlayable.h"

class Dragon final: public NonPlayable {
	public:
    Dragon(int x, int y);
	SubjectType getSubject() override;
};
#endif
