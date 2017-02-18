#ifndef __ATKPOTION_H__
#define __ATKPOTION_H__
#include "Item.h"
class Character;

class AtkPotion final: public Item{
  	int value;
	public:
    AtkPotion(int x, int y, int value);
    ~AtkPotion();
    SubjectType getSubject() override;
    void affectCharacter(Character &c) override;
};
#endif
