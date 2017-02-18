#ifndef __ORC_H__
#define __ORC_H__
#include "Playable.h"

class Orc final:public Playable{
	public:
    Orc(int x, int y);
    ~Orc();
    SubjectType getSubject() override;
};
#endif
