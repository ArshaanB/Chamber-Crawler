#ifndef __ITEM_H__
#define __ITEM_H__
#include "Subject.h"
class Character;

class Item: public Subject {
  public:
    virtual ~Item() = 0;
    virtual void affectCharacter(Character &c) = 0;
};

#endif
