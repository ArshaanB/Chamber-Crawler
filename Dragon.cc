#include "Dragon.h"
using namespace std;

Dragon::Dragon(int x, int y){
  setCoords(x,y);
  setHP(150);
  setAtk(20);
  setDef(20);
  setGold(0);
  setHostile();
  setMoved(false);
}

SubjectType Dragon::getSubject(){
  return SubjectType::Dragon;
}

