#include "Phoenix.h"
using namespace std;

Phoenix::Phoenix(int x, int y){
  setCoords(x,y);
  setHP(50);
  setAtk(35);
  setDef(20);
  setGold(1);
  setHostile();
  setMoved(false);
}

SubjectType Phoenix::getSubject(){
	return SubjectType::Phoenix;
}
