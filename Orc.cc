#include "Orc.h"
#include "ChamberFloor.h"
using namespace std;

Orc::Orc(int x, int y) {
  setCoords(x,y);
  setHP(180);
  setmaxHP(180);
  setAtk(30);
  setcAtk(30);
  setDef(25);
  setcDef(25);
  setGold(0);
  setcurrTile(new ChamberFloor(x, y));
}

Orc::~Orc(){}

SubjectType Orc::getSubject(){
  return SubjectType::Orc;
}

