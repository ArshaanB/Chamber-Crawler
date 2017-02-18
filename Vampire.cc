#include "Vampire.h"
using namespace std;

Vampire::Vampire(int x, int y){
  setCoords(x,y);
  setHP(50);
  setAtk(25);
  setDef(25);
  setGold(1);
  setHostile();
  setMoved(false);
}

SubjectType Vampire::getSubject() {
    return SubjectType::Vampire;
}
