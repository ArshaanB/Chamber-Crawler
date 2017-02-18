#include "WallH.h"
using namespace std;

WallH::WallH(int x, int y) {
	setCoords(x, y);
}

WallH::~WallH(){}

SubjectType WallH::getSubject(){
  return SubjectType::WallH;
}

