#include "Character.h"
#include "Grid.h"
#include "NonPlayable.h"
#include "Playable.h"
#include "Terrain.h"
#include "Observer.h"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

NonPlayable::~NonPlayable() {}

void NonPlayable::setMoved(bool newMoved) {
	moved = newMoved;
}
bool NonPlayable::getMoved() {
	return moved;
}

void NonPlayable::move(Grid& g) {
	
	// Step 1: Create a vector<Subject*> with all 8 surrounding positions.
	// Step 2: Remove the vector<Subject*> which does not meet criteria: ChamberFloor.
	// Step 3: Generate a random number from 0 to vector.size()-1.
	// Step 4: Move NonPlayable character to the location vector[pos] holds.
	// Step 5: Call notifyObservers().
	int currX = this->getX();
	int currY = this->getY();
	vector <Subject *> availPos;
	//Populate availPos, with the 8 possible positions.
	availPos.emplace_back(g.getXY(currX-1,currY+1));
	availPos.emplace_back(g.getXY(currX,currY+1));
	availPos.emplace_back(g.getXY(currX+1,currY+1));
	availPos.emplace_back(g.getXY(currX-1,currY));
	availPos.emplace_back(g.getXY(currX+1,currY));
	availPos.emplace_back(g.getXY(currX-1,currY-1));
	availPos.emplace_back(g.getXY(currX,currY-1));
	availPos.emplace_back(g.getXY(currX+1,currY-1));
	for (int i=0; i<8; ++i) {
		if (availPos.at(i) == g.getCharacter() && this->isHostile()) {
			this->attack(static_cast<Subject*>(g.getCharacter()), g); //If attacked, moved set to true.
			g.setAction("You have been attacked");
		}
	}
	if (this->getMoved() || this->getSubject() == SubjectType::Dragon) return;
	size_t z=0;
	while (z < availPos.size()) {
		Subject* floor = availPos.at(z);
		if (floor->getSubject() != SubjectType::ChamberFloor) {
			availPos.erase(availPos.begin() + z);
			continue;
		}
		z++;
	}
	int pos = rand() % availPos.size();
	
	//Swaps the location of both Subject* on theGrid, and swaps their X, Y
	// 	coordinates.
	g.swap(this, availPos.at(pos));
	this->notifyObservers();
	availPos.at(pos)->notifyObservers();
	this->setMoved(true);
}

bool NonPlayable::isHostile() {
	return Hostile;
}

void NonPlayable::setHostile() {
	Hostile = true;
}

void NonPlayable::attack(Subject *s, Grid &g){
  int randNum = 1;
  randNum = rand() % 2;
  int def = static_cast<Character*>(s)->getDef();
  int atk = this->getAtk();
  double dmgDealt = ceil((100.00/(100.00+def))*atk);
  int hp = static_cast<Character*>(s)->getHP();
  hp -= (dmgDealt * randNum);
  static_cast<Character*>(s)->setHP(hp);
  setMoved(true);
  if (static_cast<Character*>(s)->isDead()){
    string answer;
    while(true){
      cin >> answer;
      if (answer == "q"){
        g.quit();
        break;
      }
      if(answer == "r"){
        g.restart();
        break;
      }
    }  
  }
}
