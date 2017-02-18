#include "AtkPotion.h"
#include "Character.h"
#include <cmath>
#include <algorithm>
using namespace std;

AtkPotion::AtkPotion(int x, int y, int value): value{value} {
  setCoords(x, y);
}

AtkPotion::~AtkPotion(){}

SubjectType AtkPotion::getSubject(){
  return SubjectType::AtkPotion;
}

void AtkPotion::affectCharacter(Character &c){
  if(c.getSubject() == SubjectType::Elf){
    c.setAtk(max(c.getAtk() + abs(value), 0));
  }
  else{
    c.setAtk(max(c.getAtk() + value, 0));
  }
}


