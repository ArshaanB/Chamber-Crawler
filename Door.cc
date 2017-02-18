#include "Door.h"
using namespace std;

Door::Door(int x, int y) {
	setCoords(x, y);
}

Door::~Door(){}

SubjectType Door::getSubject(){
  return SubjectType::Door;
}
