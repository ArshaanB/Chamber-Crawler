#include "Troll.h"
using namespace std;

Troll::Troll(int x, int y){
  setCoords(x,y);
  setHP(120);
  setAtk(25);
  setDef(15);
  setGold(1);
  setHostile();
  setMoved(false);
}

SubjectType Troll::getSubject() {
	return SubjectType::Troll;
}
