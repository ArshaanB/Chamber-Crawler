#include "ChamberFloor.h"
using namespace std;

ChamberFloor::ChamberFloor(int x, int y) {
	setCoords(x, y);
}

ChamberFloor::~ChamberFloor(){}

SubjectType ChamberFloor::getSubject(){
  return SubjectType::ChamberFloor;
}
