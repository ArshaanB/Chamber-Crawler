#include "NonPlayable.h"
#include "Werewolf.h"

using namespace std;

Werewolf::Werewolf(int x, int y){
  setCoords(x,y);
  setHP(120);
  setAtk(30);
  setDef(5);
  setGold(1);
  setHostile();
  setMoved(false);
}

SubjectType Werewolf::getSubject() {
	return SubjectType::Werewolf;
}
