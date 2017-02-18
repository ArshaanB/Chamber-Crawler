#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>
#include "Observer.h"
#include "TextDisplay.h"

enum class SubjectType {Human, Orc, Dwarf, Elf, Werewolf, Goblin, Dragon, Merchant, Troll, Phoenix, Vampire, Door, WallH, WallV, Passage, Stairs, EmptyFloor, ChamberFloor, Gold, AtkPotion, HPPotion, DefPotion};

class Subject{
	int x, y;
  std::vector <Observer*> observers;
	public:
	virtual ~Subject() = 0;
	virtual SubjectType getSubject() = 0;
	int getX();
	int getY();
	void setCoords(int x, int y);
	void notifyObservers();
	void attachObserver(Observer *o);
};
#endif
    

