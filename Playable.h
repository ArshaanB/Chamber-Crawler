#ifndef __PLAYABLE_H__
#define __PLAYABLE_H__
#include "Character.h"
#include <string>
class HPPotion;
class AtkPotion;
class DefPotion;
class Gold;
class Grid;
class NonPlayable;

class Playable: public Character{
  double maxHP;
  int cAtk;
  int cDef;
  Subject* currTile;
  bool validPosition = false;
  public:
  virtual ~Playable() = 0;
	  double getmaxHP();
	  void setmaxHP(double newmaxHP);
	  int getcAtk();
	  void setcAtk(int newcAtk);
	  int getcDef();
    void setcDef(int newcDef);
	  void setValidPosition(bool newPosition);
	  bool getValidPosition();
    void move(Grid &g, std::string i, std::string j);
    void setcurrTile(Subject* s);
    Subject* getcurrTile();
    void attack(Subject* s, Grid &g);
};
#endif

