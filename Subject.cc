#include "Subject.h"
#include "Observer.h"
#include "TextDisplay.h"

using namespace std;

Subject::~Subject() {}

int Subject::getX(){
  return x;
}

int Subject::getY(){
  return y;
}

void Subject::setCoords(int x, int y){
  this->x = x;
  this->y = y;
}

void Subject::notifyObservers(){
  int obsSize = observers.size();
  for (int i = 0; i < obsSize; ++i){
    observers.at(i)->notify(*this);
  }
}

void Subject::attachObserver(Observer *o){
  observers.emplace_back(o);
}

