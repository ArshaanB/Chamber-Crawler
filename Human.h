#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "Playable.h"

class Human final:public Playable{
  public:
    Human(int x, int y);
    ~Human();
    SubjectType getSubject() override;
};
#endif
