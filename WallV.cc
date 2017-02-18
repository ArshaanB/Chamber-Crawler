#include "WallV.h"
using namespace std;

WallV::WallV(int x, int y){
  setCoords(x,y);
}

WallV::~WallV(){}

SubjectType WallV::getSubject(){
  return SubjectType::WallV;
}
