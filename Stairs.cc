#include "Stairs.h"
using namespace std;

Stairs::Stairs(int x, int y) {
	setCoords(x, y);
}

Stairs::~Stairs(){}

SubjectType Stairs::getSubject(){
  return SubjectType::Stairs;
}
