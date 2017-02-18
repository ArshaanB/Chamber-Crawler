#ifndef __ELF_H__
#define __ELF_H__
#include "Playable.h"

class Elf final:public Playable{
	public:
    Elf(int x, int y);
    ~Elf();
    SubjectType getSubject() override;
};
#endif
