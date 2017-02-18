#include "Dwarf.h"
#include "ChamberFloor.h"
using namespace std;

Dwarf::Dwarf(int x, int y) {
  setCoords(x,y);
  setHP(100);
  setmaxHP(100);
  setAtk(20);
  setcAtk(20);
  setDef(30);
  setcDef(30);
  setGold(0);
  setcurrTile(new ChamberFloor(x, y));
}

SubjectType Dwarf::getSubject(){
  return SubjectType::Dwarf;
}
