#ifndef __GOLD_H__
#define __GOLD_H__
#include "Item.h"

class Character;
class Grid;

class Gold final: public Item{
  double value; 
  public:
    Gold(int x, int y, double value);
    ~Gold();
    SubjectType getSubject() override;
    void affectCharacter (Character & c) override;
	double getValue();
    bool pickupGold(Grid& g);
};
#endif

