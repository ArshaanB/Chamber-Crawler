#include "Playable.h"
#include "NonPlayable.h"
#include "Item.h"
#include "HPPotion.h"
#include "AtkPotion.h"
#include "DefPotion.h"
#include "Gold.h"
#include "Grid.h"
#include "Dragon.h"
#include "Terrain.h"
#include "ChamberFloor.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

Playable::~Playable() {
	delete currTile;
}

double Playable::getmaxHP() {
	return maxHP;
}
void Playable::setmaxHP(double newmaxHP) {
	maxHP = newmaxHP;
}
int Playable::getcAtk() {
	return cAtk;
}
void Playable::setcAtk(int newcAtk) {
	cAtk = newcAtk;
}
int Playable::getcDef() {
	return cDef;
}
void Playable::setcDef(int newcDef) {
	cDef = newcDef;
}
void Playable::setValidPosition(bool newPosition) {
	validPosition = newPosition;
}
bool Playable::getValidPosition() {
	return validPosition;
}
Subject* Playable::getcurrTile() {
	return currTile;
}
void Playable::setcurrTile(Subject* s){
  currTile = s;
}

void Playable::move(Grid &g, string i, string j){
  int x, y;
  Subject* newPos;
  
    if (i == "no"){
      x = this->getX();
      y = this->getY() - 1;
    } 
    else if(i == "so"){
      x = this->getX();
      y = this->getY() + 1;
    }
    else if(i == "ea"){
      x = this->getX() + 1;
      y = this->getY();
    }
    else if(i == "we"){
      x = this->getX() - 1;
      y = this->getY();
    }
    else if(i == "ne"){
      x = this->getX() + 1;
      y = this->getY() - 1;
    }
    else if(i == "nw"){
      x = this->getX() - 1;
      y = this->getY() - 1;
    }
    else if(i == "se"){
      x = this->getX() + 1;
      y = this->getY() + 1;
    }
    else{
      x = this->getX() - 1;
      y = this->getY() + 1;
    }
    newPos = g.getXY(x,y);
    if((newPos->getSubject() == SubjectType::Gold || newPos->getSubject() == SubjectType::HPPotion || 
        newPos->getSubject() == SubjectType::AtkPotion || newPos->getSubject() == SubjectType::DefPotion)  && (j == "u")){
      if(newPos->getSubject() == SubjectType::Gold){
        if (!static_cast<Gold*>(newPos)->pickupGold(g)){
          return;
        }
        else{
          static_cast<Gold*>(newPos)->affectCharacter(*this);
        }
      }
      else if(newPos->getSubject() == SubjectType::HPPotion){
        static_cast<HPPotion*>(newPos)->affectCharacter(*this);
      }
      else if(newPos->getSubject() == SubjectType::DefPotion){
        static_cast<DefPotion*>(newPos)->affectCharacter(*this);
      }
      else{
        static_cast<AtkPotion*>(newPos)->affectCharacter(*this);
      }
      //Create a new chamber object that will eventually replace spot where gold was spawned
      Subject* NewChamberFloor = new ChamberFloor(x,y);
      NewChamberFloor->attachObserver(g.getTextDisplay());
      if (newPos->getSubject() == SubjectType::Gold){
        g.setAction("You picked up some Gold");
      }
      else{
        g.setAction("You used a Potion");
      }
      delete newPos;//delete item object
      g.setXY(currTile, this->getX(), this->getY());//set current location to terrain object is stepping 
      currTile->notifyObservers();
      g.setXY(this,x,y);//set new position to be occupied by playable character
	  this->setCoords(x,y);      
this->notifyObservers();//notify
      this->setcurrTile(NewChamberFloor);//set new chamber floor tile created to be current tile
      this->setValidPosition(true);
    }
    else if((newPos->getSubject() == SubjectType::ChamberFloor || newPos->getSubject() == SubjectType::Door ||
             newPos->getSubject() == SubjectType::Stairs || newPos->getSubject() == SubjectType::Passage) && (j == "m")){
      if(newPos->getSubject() == SubjectType::Stairs){
		    int newLevel = g.getLevel()+1;
		    if(newLevel == 5) {
			    g.success();
			    return;
		    } 
		    else {
			    g.setLevel(newLevel);
			    g.clearLevel();
				if (g.getDefaultLayout() == true){
            		g.populateDefaultGrid();
          		}
				else{
            		g.populateGivenGrid();
				}
			    this->setAtk(this->getcAtk());
			    this->setDef(this->getcDef());
          g.setAction("You made it to the next Level");
		      }
        this->setValidPosition(true);
      }
      else {
		g.setXY(currTile,this->getX(),this->getY());//set current position on grid to point to original subject
		currTile->setCoords(this->getX(), this->getY());
		currTile->notifyObservers();
        this->setcurrTile(newPos);//set next position to current tile being stepped 
        g.setXY(this,x,y);//set next position on grid to point at Character
		this->setCoords(x,y);
        this->notifyObservers();
		g.setAction("You moved");
        this->setValidPosition(true);
      }
    }
    else if (newPos->getSubject() != SubjectType::WallH && newPos->getSubject() != SubjectType::WallV && 
             newPos->getSubject() != SubjectType::EmptyFloor && j == "a"){
      this->attack(newPos, g);
      g.setAction("You have attacked");
	  this->setValidPosition(true);
	  }
    else{
      this->setValidPosition(false);
      return;
    }
    if(this->isDead()){
      g.setAction("You have been slain, enter r to Restart the game, or q to Quit.");
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
    vector<Subject *> charBlockRadius;
    vector<Subject *> goldBlockRadius;
    int currX = this->getX();
    int currY = this->getY();
    //Populate charBlockRadius, with the 8 possible positions.
    charBlockRadius.emplace_back(g.getXY(currX-1,currY+1));
    charBlockRadius.emplace_back(g.getXY(currX,currY+1));
    charBlockRadius.emplace_back(g.getXY(currX+1,currY+1));
    charBlockRadius.emplace_back(g.getXY(currX-1,currY));
    charBlockRadius.emplace_back(g.getXY(currX+1,currY));
    charBlockRadius.emplace_back(g.getXY(currX-1,currY-1));
    charBlockRadius.emplace_back(g.getXY(currX,currY-1));
    charBlockRadius.emplace_back(g.getXY(currX+1,currY-1));
    for (int i=0; i<8; ++i) {
	    if (charBlockRadius.at(i)->getSubject() == SubjectType::Gold) {
		    if (static_cast<Gold*>(charBlockRadius.at(i))->getValue() == 6) {
		        int dragHordeX = charBlockRadius.at(i)->getX();
            int dragHordeY = charBlockRadius.at(i)->getY();
            //Populate goldBlockRadius, with the 8 possible positions.
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX-1,dragHordeY+1));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX,dragHordeY+1));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX+1,dragHordeY+1));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX-1,dragHordeY));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX+1,dragHordeY));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX-1,dragHordeY-1));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX,dragHordeY-1));
  		      goldBlockRadius.emplace_back(g.getXY(dragHordeX+1,dragHordeY-1));
		        for (int i=0; i<8; ++i) {
              if (goldBlockRadius.at(i)->getSubject() == SubjectType::Dragon) {
		  	        static_cast <Dragon*>(goldBlockRadius.at(i))->setHostile();
			        }
			      }
			   }
	    } 
	  }
}    

void Playable::attack(Subject* s, Grid &g){
  int def = static_cast<Character*>(s)->getDef();
  int atk = this->getAtk();
  double dmgDealt = ceil((100.00/(100.00+def))*atk);
  int hp = static_cast<Character*>(s)->getHP();
  hp -= dmgDealt;
  static_cast<Character*>(s)->setHP(hp);
  static_cast<NonPlayable*>(s)->setHostile();
  if (static_cast<Character*>(s)->getSubject() == SubjectType::Merchant){
    g.setMerchantState(true);
    g.setMerchantsHostile();
  }
  if (static_cast<Character*>(s)->isDead()){
    Gold newGold = Gold{0, 0, static_cast<Character*>(s)->getGold()};
    newGold.affectCharacter(*this);
    ChamberFloor* cf = new ChamberFloor(static_cast<Character*>(s)->getX(), static_cast<Character*>(s)->getY());
    g.setXY(cf, static_cast<Character*>(s)->getX(), static_cast<Character*>(s)->getY());
    cf->attachObserver(g.getTextDisplay());
    cf->notifyObservers();
    delete s;
  }
}
