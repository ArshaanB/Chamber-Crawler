#include "Goblin.h"
using namespace std;

Goblin::Goblin(int x, int y){
  setCoords(x,y);
  setHP(70);
  setAtk(5);
  setDef(10);
  setGold(1);
  setHostile();
  setMoved(false);
}

SubjectType Goblin::getSubject() {
	return SubjectType::Goblin;
}
