#ifndef __NONPLAYABLE_H__
#define __NONPLAYABLE_H__
#include "Character.h"
class Grid;

class NonPlayable: public Character {
	bool moved;
	bool Hostile = false;
	public:
		virtual ~NonPlayable() = 0;
		void setMoved(bool newMoved);
		bool getMoved();
 		bool isHostile();
   		void setHostile();
		void move(Grid &g);
    	void attack(Subject* s, Grid&g);
};
#endif
