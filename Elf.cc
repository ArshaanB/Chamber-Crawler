#include "Elf.h"
#include "ChamberFloor.h"
using namespace std;

Elf::Elf(int x, int y) {
  setCoords(x,y);
  setHP(140);
  setmaxHP(140);
  setAtk(30);
  setcAtk(30);
  setDef(10);
  setcDef(10);
  setGold(0);
  setcurrTile(new ChamberFloor(x, y));
}

Elf::~Elf(){}

SubjectType Elf::getSubject(){
  return SubjectType::Elf;
}
