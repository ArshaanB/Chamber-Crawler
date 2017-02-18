#ifndef __PASSAGE_H__
#define __PASSAGE_H__
#include "Terrain.h"

class Passage final: public Terrain{
  public:
    Passage(int x, int y);
    ~Passage();
    SubjectType getSubject() override;
};
#endif
