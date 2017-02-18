#ifndef __DEFPOTION_H__
#define __DEFPOTION_H__
#include "Item.h"
class Character;

class DefPotion final: public Item{
  	int value;
	public:
    DefPotion(int x, int y, int value);
    ~DefPotion();
    SubjectType getSubject() override;
    void affectCharacter (Character & c) override;
};
#endif
