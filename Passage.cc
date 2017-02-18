#include "Passage.h"
using namespace std;

Passage::Passage(int x, int y) {
	setCoords(x, y);
}

Passage::~Passage(){}

SubjectType Passage::getSubject(){
  return SubjectType::Passage;
}
