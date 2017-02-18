#include "Merchant.h"
using namespace std;

Merchant::Merchant(int x, int y){
  setCoords(x,y);
  setHP(30);
  setAtk(70);
  setDef(5);
  setGold(4);
  setMoved(false);
}

SubjectType Merchant::getSubject() {
	return SubjectType::Merchant;
}

