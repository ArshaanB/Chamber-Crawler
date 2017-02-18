#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "Subject.h"
#include <cstdlib>
class Grid;

class Character: public Subject {
  double HP;
  int mAtk, mDef;
  double gold;

  public:
    void setHP(double newHP);
    double getHP();
    void setAtk(int newAtk);
    int getAtk();
    void setDef(int newDef);
    int getDef();
    void setGold(double newGold);
    double getGold();
    bool isDead();
    SubjectType getSubject() = 0;
};

#endif
