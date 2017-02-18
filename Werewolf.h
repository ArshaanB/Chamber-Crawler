#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__
#include "NonPlayable.h"

class Werewolf final: public NonPlayable {
	public:
    Werewolf(int x, int y);
	SubjectType getSubject() override;
};
#endif
