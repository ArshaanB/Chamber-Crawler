#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include "NonPlayable.h"

class Phoenix final: public NonPlayable {
	public:
    Phoenix(int x, int y);
    SubjectType getSubject() override;
};
#endif
