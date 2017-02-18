#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "Observer.h"
#include <vector>
class Subject;

class TextDisplay final: public Observer{
  std::vector <std::vector <char>> theDisplay;
  int gridSizeX;
  int gridSizeY;
  public:
    TextDisplay(int x, int y);
    ~TextDisplay();
    void notify(Subject & s);
	  void printTextDisplay();
};

#endif
