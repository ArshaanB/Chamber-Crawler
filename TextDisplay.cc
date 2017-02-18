#include "TextDisplay.h"
#include "Subject.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(int x, int y): gridSizeX{x}, gridSizeY{y} {
	theDisplay.resize(y);
  for (int i = 0; i < y; ++i){
    theDisplay[i].resize(x);
  }
}

TextDisplay::~TextDisplay(){}

void TextDisplay::notify(Subject & s){
	if ((s.getSubject() == SubjectType::Human) || (s.getSubject() == SubjectType::Orc) || 
	    (s.getSubject() == SubjectType::Elf) || (s.getSubject() == SubjectType::Dwarf)) {
		theDisplay[s.getY()][s.getX()] = '@';
	}
    else if (s.getSubject() == SubjectType::Werewolf) {
		theDisplay[s.getY()][s.getX()] = 'W';
	}
	else if(s.getSubject() == SubjectType::Vampire) {
		theDisplay[s.getY()][s.getX()] = 'V';
	}
	else if(s.getSubject() == SubjectType::Goblin) {
		theDisplay[s.getY()][s.getX()] = 'N';
	}
	else if(s.getSubject() == SubjectType::Troll) {
		theDisplay[s.getY()][s.getX()] = 'T';
	}
	else if(s.getSubject() == SubjectType::Phoenix) {
		theDisplay[s.getY()][s.getX()] = 'X';
	}
	else if(s.getSubject() == SubjectType::Merchant) {
		theDisplay[s.getY()][s.getX()] = 'M';
	}
	else if(s.getSubject() == SubjectType::Dragon) {
		theDisplay[s.getY()][s.getX()] = 'D';
	}
	else if(s.getSubject() == SubjectType::ChamberFloor) {
		theDisplay[s.getY()][s.getX()] = '.';
	}
    else if(s.getSubject() == SubjectType::EmptyFloor) {
		theDisplay[s.getY()][s.getX()] = ' ';
	}
	else if(s.getSubject() == SubjectType::Passage){
		theDisplay[s.getY()][s.getX()] = '#';
	}
	else if (s.getSubject() == SubjectType::WallH){
		theDisplay[s.getY()][s.getX()] = '-';
	}
	else if(s.getSubject() == SubjectType::WallV){
		theDisplay[s.getY()][s.getX()] = '|';
	}
    else if(s.getSubject() == SubjectType::Door){
      	theDisplay[s.getY()][s.getX()] = '+';
    }
    else if (s.getSubject() == SubjectType::Stairs) {
      	theDisplay[s.getY()][s.getX()] = '\\';
    }
    else if ((s.getSubject() == SubjectType::HPPotion) || (s.getSubject() == SubjectType::AtkPotion) ||
			 (s.getSubject() == SubjectType::DefPotion)) {
		theDisplay[s.getY()][s.getX()] = 'P';
    }
    else {
      theDisplay[s.getY()][s.getX()] = 'G';
	}
}

void TextDisplay::printTextDisplay() {
	for (int y=0; y<gridSizeY; ++y) {
		for (int x=0; x<gridSizeX; ++x) {
			cout << theDisplay[y][x];
		}
		cout << "\n";
	}
}
