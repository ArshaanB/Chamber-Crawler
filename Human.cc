#include "Human.h"
#include "ChamberFloor.h"
using namespace std;

Human::Human(int x, int y) {
  setCoords(x,y);
  setHP(140);
  setmaxHP(140);
  setAtk(20);
  setcAtk(20);
  setDef(20);
  setcDef(20);
  setGold(0);
  setcurrTile(new ChamberFloor(x,y));
}

Human::~Human(){}

SubjectType Human::getSubject(){
  return SubjectType::Human;
}
