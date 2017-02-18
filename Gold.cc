#include "Gold.h"
#include "Grid.h"
#include "Character.h"
#include "Playable.h"
#include "NonPlayable.h"
using namespace std;

Gold::Gold(int x, int y, double value): value{value} {
  setCoords(x, y);
}

Gold::~Gold(){}

SubjectType Gold::getSubject(){
  return SubjectType::Gold;
}

void Gold::affectCharacter(Character &c){
  if(c.getSubject() == SubjectType::Dwarf){
    c.setGold(c.getGold() + (value * 2));
  }
  else if(c.getSubject() == SubjectType::Orc){
    c.setGold(c.getGold() + (value / 2));
  }
  else{
    c.setGold(c.getGold() + value);
  }
}

double Gold::getValue() {
	return value;
}

bool Gold::pickupGold(Grid& g){
	if(value == 6){
    	vector<Subject *> goldBlockRadius;
    	int currX = this->getX();
    	int currY = this->getY();
    	goldBlockRadius.emplace_back(g.getXY(currX-1,currY+1));
    	goldBlockRadius.emplace_back(g.getXY(currX,currY+1));
    	goldBlockRadius.emplace_back(g.getXY(currX+1,currY+1));
    	goldBlockRadius.emplace_back(g.getXY(currX-1,currY));
    	goldBlockRadius.emplace_back(g.getXY(currX+1,currY));
    	goldBlockRadius.emplace_back(g.getXY(currX-1,currY-1));
    	goldBlockRadius.emplace_back(g.getXY(currX,currY-1));
		goldBlockRadius.emplace_back(g.getXY(currX+1,currY-1));
  
		for (int i=0; i<8; ++i) {
			if (goldBlockRadius.at(i)->getSubject() == SubjectType::Dragon) return false;
		}
	}
	return true;
}

