#ifndef __HPPOTION_H__
#define __HPPOTION_H__
#include "Item.h"
class Character;

class HPPotion final: public Item{
  	int value;
	public:
    HPPotion(int x, int y, int value);
    ~HPPotion();
    SubjectType getSubject() override;
    void affectCharacter(Character & c) override;
};
#endif
