#ifndef __DWARF_H__
#define __DWARF_H__
#include "Playable.h"

class Dwarf final:public Playable{
	public:
    Dwarf(int x, int y);
    SubjectType getSubject() override;
};
#endif
