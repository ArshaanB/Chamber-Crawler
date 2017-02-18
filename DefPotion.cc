#include "DefPotion.h"
#include "Character.h"
#include <cmath>
#include <algorithm>
using namespace std;

DefPotion::DefPotion(int x, int y, int value): value{value} {
  setCoords(x, y);
}

DefPotion::~DefPotion(){}

SubjectType DefPotion::getSubject(){
  return SubjectType::DefPotion;
}

void DefPotion::affectCharacter(Character &c){
  if(c.getSubject() == SubjectType::Elf){
    c.setDef(max(c.getDef() + abs(value), 0));
  }
  else{
    c.setDef(max(c.getDef() + value, 0));
  }
}


