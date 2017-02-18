#include "Subject.h"
#include "Character.h"
#include "Grid.h"
#include "NonPlayable.h"
#include <cmath>

using namespace std;

void Character::setHP(double newHP) {
	HP = newHP;
}
double Character::getHP() {
	return HP;
}
void Character::setAtk(int newAtk) {
	mAtk = newAtk;
}
int Character::getAtk() {
	return mAtk;
}
void Character::setDef(int newDef) {
	mDef = newDef;
}
int Character::getDef() {
	return mDef;
}
void Character::setGold(double newGold) {
	gold = newGold;
}
double Character::getGold() {
	return gold;
}
bool Character::isDead() {
	return HP <= 0;
}



