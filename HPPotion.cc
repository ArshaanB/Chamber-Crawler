#include "HPPotion.h"
#include "Character.h"
#include "Playable.h"
#include <cmath>
#include <algorithm>
using namespace std;

HPPotion::HPPotion(int x, int y, int value): value{value} {
  setCoords(x,y);
}

HPPotion::~HPPotion(){}

SubjectType HPPotion::getSubject(){
  return SubjectType::HPPotion;
}

void HPPotion::affectCharacter(Character & c){
  if(c.getSubject() == SubjectType::Elf){
    c.setHP(min(c.getHP() + abs(value), static_cast<Playable&>(c).getmaxHP()));
  }
  else {
	if (value < 0) c.setHP(max(c.getHP() + value, 0.00));
	else c.setHP(min(c.getHP() + value, static_cast<Playable&>(c).getmaxHP()));
  }
}
