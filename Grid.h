#ifndef __GRID_H__
#define __GRID_H__
#include <vector>
#include <string>
class Subject;
class Character;
class TextDisplay;

class Grid {
	//std::vector<std::vector<Subject *>> theGrid;
	//std::vector<std::vector<Subject *>> chambers;
	TextDisplay *td;
	Character *c;
	//int gridSizeX = 79;
	//int gridSizeY = 25;
	int level;
	bool defaultLayout;
	bool merchantState = false;
	//int chamberOfPC;
	std::string fileName;
	std::string action;
	public:
	  std::vector<std::vector<Subject *>> theGrid;
	  std::vector<std::vector<Subject *>> chambers;
	  Subject* getXY(int x, int y);
	  void setXY(Subject* s, int x, int y);
	  void swap(Subject* first, Subject* second);
	  void moveAllCharacters();
	  Grid(std::string file="defaultLayout.txt");
	  void choosePlayableCharacter();
	  void restart();
	  void quit();
	  void success();
	  void populateDefaultGrid();
	  void populateGivenGrid();
	  void clearLevel();
	  int getLevel();
	  void setLevel(int newLevel);
    void setMerchantState(bool b);
    bool getMerchantState();
    void setMerchantsHostile();
    std::string getAction();
    void setAction(std::string s);
	  Subject* getCharacter();
	  TextDisplay* getTextDisplay();
	  void setTextDisplay(TextDisplay* newtd);
	  std::string getfileName();
	  bool getDefaultLayout();
	  void printGrid();
	  void populateDragon(int x, int y);
	  int chamberOfPC;
	int gridSizeX = 79;
    int gridSizeY = 25;
};
#endif
