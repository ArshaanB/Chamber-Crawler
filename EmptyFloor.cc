#include "EmptyFloor.h"
using namespace std;

EmptyFloor::EmptyFloor(int x, int y) {
	setCoords(x, y);
}

EmptyFloor::~EmptyFloor(){}

SubjectType EmptyFloor::getSubject(){
  return SubjectType::EmptyFloor;
}

