#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "NonPlayable.h"

class Vampire final: public NonPlayable {
  public:
    Vampire(int x, int y);
    SubjectType getSubject() override;
};
#endif
