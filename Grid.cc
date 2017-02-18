#include "Subject.h"
#include "Grid.h"
#include "Character.h"
#include "Playable.h"
#include "NonPlayable.h"
#include "Human.h"
#include "Orc.h"
#include "Elf.h"
#include "Dwarf.h"
#include "Vampire.h"
#include "Goblin.h"
#include "Werewolf.h"
#include "Dragon.h"
#include "Merchant.h"
#include "Phoenix.h"
#include "Troll.h"
#include "Terrain.h"
#include "ChamberFloor.h"
#include "EmptyFloor.h"
#include "Door.h"
#include "WallH.h"
#include "WallV.h"
#include "Passage.h"
#include "Stairs.h"
#include "Item.h"
#include "HPPotion.h"
#include "AtkPotion.h"
#include "DefPotion.h"
#include "Gold.h"
#include "Observer.h"
#include "TextDisplay.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Subject* Grid::getXY(int x, int y) {
	return theGrid[y][x];
}

void Grid::setXY(Subject* s, int x, int y) {
	theGrid[y][x] = s;
}

void Grid::setAction(std::string s){
  action = s;
}

std::string Grid::getAction(){
  return action;
}

void Grid::populateDragon(int x, int y) {
	vector<Subject *> dragonSpots;
  	//Populate dragonSpots, with the 8 possible positions.
  	dragonSpots.emplace_back(this->getXY(x-1,y+1));
  	dragonSpots.emplace_back(this->getXY(x,y+1));
  	dragonSpots.emplace_back(this->getXY(x+1,y+1));
  	dragonSpots.emplace_back(this->getXY(x-1,y));
  	dragonSpots.emplace_back(this->getXY(x+1,y));
  	dragonSpots.emplace_back(this->getXY(x-1,y-1));
  	dragonSpots.emplace_back(this->getXY(x,y-1));
  	dragonSpots.emplace_back(this->getXY(x+1,y-1));
	//Remove non-ChamberFloors.
	size_t z=0;
    while (z < dragonSpots.size()) {
		if (dragonSpots[z]->getSubject() == SubjectType::ChamberFloor) {
			z++;
			continue;
		} else {
			dragonSpots.erase(dragonSpots.begin()+z);
		}
	}
	//Random, Dragon().
	int randInt = rand() % dragonSpots.size();
	Subject* chosenSpot = dragonSpots[randInt];
	Dragon(chosenSpot->getX(), chosenSpot->getY());
}

void Grid::swap(Subject* first, Subject* second) {
	// Step 1: Take first, and set it to the position of second.
	// Step 2: Take second, and set it to the position of first.
	// Step 3: Swap their X, Y coordinates.
	int secondX = second->getX();
	int secondY = second->getY();
	int firstX = first->getX();
	int firstY = first->getY();
	second->setCoords(firstX, firstY);
	first->setCoords(secondX, secondY);
	Subject* temp = second;	
	
	this->setXY(first, secondX, secondY);
	this->setXY(temp, firstX, firstY);
}

void Grid::setMerchantState(bool b){
  merchantState = b;
}

bool Grid::getMerchantState(){
  return merchantState;
}

void Grid::setMerchantsHostile(){
	for (int y=0; y<gridSizeY; ++y){
		for (int x=0; x<gridSizeX; ++x){
			if (theGrid[y][x]->getSubject() == SubjectType::Merchant) {
				static_cast<NonPlayable*>(theGrid[y][x])->setHostile();
 			}
    	}
  	}
}

void Grid::moveAllCharacters() {
	//Step 2: Now search every element of theGrid[][]. If theGrid[][]->getMoved()
	//	== true then 'continue'. Test with, getSubject() if it's not Character,
	//	'continue'. If getCharacter() returns Character::NonPlayable then call 
	//	theGrid[][]->move() on it.
	//******: Be sure to navigate from left to right, and top to bottom.
	//Step 3: Apply to all Subject* (through a loop), which are of type 
	//	Character::NonPlayable a theGrid[][].setMoved(false).
	for (int y=0; y<gridSizeY; ++y) {
		for (int x=0; x<gridSizeX; ++x) {
			Subject* curr = theGrid[y][x];
			if (curr == static_cast<Subject*>(getCharacter())) continue;
			if ((curr->getSubject() == SubjectType::Goblin) ||
				(curr->getSubject() == SubjectType::Vampire) ||
				(curr->getSubject() == SubjectType::Merchant) ||
				(curr->getSubject() == SubjectType::Phoenix) ||
				(curr->getSubject() == SubjectType::Troll) ||
				(curr->getSubject() == SubjectType::Dragon) ||
				(curr->getSubject() == SubjectType::Werewolf)) { 
				static_cast<NonPlayable*>(curr)->move(*this);
			}
		}
	}
	for (int y=0; y<gridSizeY; ++y) {
		for (int x=0; x<gridSizeX; ++x) {
			Subject* curr = theGrid[y][x];
			if (curr == static_cast<Subject*>(getCharacter())) continue;
            if ((curr->getSubject() == SubjectType::Goblin) ||
                (curr->getSubject() == SubjectType::Vampire) ||
                (curr->getSubject() == SubjectType::Merchant) ||
                (curr->getSubject() == SubjectType::Phoenix) ||
                (curr->getSubject() == SubjectType::Troll) ||
                (curr->getSubject() == SubjectType::Dragon) ||
                (curr->getSubject() == SubjectType::Werewolf)) {  
            	static_cast<NonPlayable*>(theGrid[y][x])->setMoved(false);
			}
		}
	}
}

Subject* charToSubjectPtr (char c, int x, int y, Grid* g) {
	if (c == '|') return new WallV(x, y);
	else if (c == '-') return new WallH(x, y);
	else if (c == '+') return new Door(x, y);
	else if (c == '#') return new Passage(x, y);
	else if (c == '.') return new ChamberFloor(x, y);
	else if (c == ' ') return new EmptyFloor(x, y);
	else if (c == '\\') return new Stairs(x, y);
	else if (c == '@') {
		Subject* s = static_cast<Subject*>(g->getCharacter());
		s->setCoords(x, y);
		return s;
	}
	else if (c == 'V') return new Vampire(x, y);
	else if (c == 'W') return new Werewolf(x, y);
	else if (c == 'N') return new Goblin(x, y);
	else if (c == 'M') return new Merchant(x, y);
	else if (c == 'D') return new Dragon(x, y);
	else if (c == 'X') return new Phoenix(x, y);
	else if (c == 'T') return new Troll(x, y);
	else if (c == '0') return new HPPotion(x, y, 10);
	else if (c == '1') return new AtkPotion(x, y, 5);
	else if (c == '2') return new DefPotion(x, y, 5);
	else if (c == '3') return new HPPotion(x, y, -10);
    else if (c == '4') return new AtkPotion(x, y, -5);
    else if (c == '5') return new DefPotion(x, y, -5);
	else if (c == '6') return new Gold(x, y, 1);
    else if (c == '7') return new Gold(x, y, 2);
	else if (c == '8') return new Gold(x, y, 4);
    else return new Gold(x, y, 6);
}

//Finds all connected ChamberFloors, in one Chamber.
void findNextCF(vector<Subject *>& newChamber, Subject *s, vector<vector<Subject *>> copyGrid) {
    newChamber.emplace_back(s);
    int sX = s->getX();
    int sY = s->getY();
    copyGrid[sY][sX] = nullptr;
    //Check Bottom, Left, Top, Right. Apply findNextCF() with these new spots as the Subject *.
	if ((copyGrid[sY+1][sX] == nullptr || (copyGrid[sY+1][sX] != nullptr && copyGrid[sY+1][sX]->getSubject() != SubjectType::ChamberFloor)) ||
		(copyGrid[sY][sX-1] == nullptr || (copyGrid[sY][sX-1] != nullptr && copyGrid[sY][sX-1]->getSubject() != SubjectType::ChamberFloor)) ||
		(copyGrid[sY-1][sX] == nullptr || (copyGrid[sY-1][sX] != nullptr && copyGrid[sY-1][sX]->getSubject() != SubjectType::ChamberFloor)) ||
		(copyGrid[sY][sX+1] == nullptr || (copyGrid[sY][sX+1] != nullptr && copyGrid[sY][sX+1]->getSubject() != SubjectType::ChamberFloor))) { return; }
	if (copyGrid[sY+1][sX] != nullptr) {
		if (copyGrid[sY+1][sX]->getSubject() == SubjectType::ChamberFloor) {
        	findNextCF(newChamber, copyGrid[sY+1][sX], copyGrid);
    	}
	}
    if (copyGrid[sY][sX-1] != nullptr) {
		if (copyGrid[sY][sX-1]->getSubject() == SubjectType::ChamberFloor) {
        	findNextCF(newChamber, copyGrid[sY][sX-1], copyGrid);
    	}
	}
	if (copyGrid[sY-1][sX] != nullptr) {
    	if (copyGrid[sY-1][sX]->getSubject() == SubjectType::ChamberFloor) {
        	findNextCF(newChamber, copyGrid[sY-1][sX], copyGrid);
    	}
	}
	if (copyGrid[sY][sX+1] != nullptr) {
    	if (copyGrid[sY][sX+1]->getSubject() == SubjectType::ChamberFloor) {
        	findNextCF(newChamber, copyGrid[sY][sX+1], copyGrid);
    	}
	}
}

void addToGrid(Subject* s, Grid* g) {
	int chamberSelect;
	int floorTileSelect;
	Subject* target;
	int targetX, targetY;
	int amtChambers;
	
	//Stairway ONLY, picks non PC chamber.
	if (s->getSubject() == SubjectType::Stairs) {
		amtChambers = g->chambers.size()-1;
		chamberSelect = rand() % amtChambers;
		if (chamberSelect == g->chamberOfPC) chamberSelect += 1;
    } 
	else { //Every other scenario.
		amtChambers = g->chambers.size();
		chamberSelect = rand() % amtChambers;
	}
    floorTileSelect = rand() % g->chambers[chamberSelect].size();
    target = g->chambers[chamberSelect][floorTileSelect];
    targetX = target->getX();
    targetY = target->getY();
    delete g->theGrid[targetY][targetX];
	s->setCoords(targetX, targetY);
    g->theGrid[targetY][targetX] = s;
    g->chambers[chamberSelect].erase(g->chambers[chamberSelect].begin()+floorTileSelect);
    g->theGrid[targetY][targetX]->attachObserver(g->getTextDisplay());
	g->theGrid[targetY][targetX]->notifyObservers();
	//Playable ONLY
	if ((s->getSubject() == SubjectType::Human) || (s->getSubject() == SubjectType::Orc) ||
        (s->getSubject() == SubjectType::Elf) || (s->getSubject() == SubjectType::Dwarf)) {
    	g->chamberOfPC = chamberSelect;
		static_cast<Playable*>(s)->getcurrTile()->setCoords(targetX, targetY);
	}
	if (s->getSubject() == SubjectType::Gold) {
		if(static_cast<Gold*>(s)->getValue() == 6) g->populateDragon(targetX, targetY);
	}
}

void randomGeneration(Grid* g) {
	//Step 1: Now generate PlayerCharacter, Stairway, Potions, Gold, Enemies on Grid randomly.
	
	//Step 1a: Algorithm for PlayerCharacter
	addToGrid(static_cast<Subject*>(g->getCharacter()), g);
	//Step 1b: Algorithm for Stairs
	addToGrid(new Stairs(0, 0), g);
	//Step 1c: Algorithm for Potions x 10
	for (int i=0; i<10; ++i) {
		int typePotion = rand() % 6;
		if (typePotion == 0) addToGrid(new HPPotion(0, 0, 10), g);
		else if (typePotion == 1) addToGrid(new AtkPotion(0, 0, 5), g);
		else if (typePotion == 2) addToGrid(new DefPotion(0, 0, 5), g);
		else if (typePotion == 3) addToGrid(new HPPotion(0, 0, -10), g);
		else if (typePotion == 4) addToGrid(new AtkPotion(0, 0, -5), g);
        else addToGrid(new DefPotion(0, 0, -5), g);
	}
	//Step 1d: Algorithm for Gold x 10
	for (int i=0; i<10; ++i) {
		int typeGold = rand() % 8;
		if ((typeGold >= 0) && (typeGold <= 4)) addToGrid(new Gold(0, 0, 1), g);
		else if (typeGold == 5) addToGrid(new Gold(0, 0, 6), g);
		else addToGrid(new Gold(0, 0, 2), g);
	}
	//Step 1e: Algorithm for Enemies
	for (int i=0; i<20; ++i) {
		int typeEnemy = rand() % 18;
		if ((typeEnemy >= 0) && (typeEnemy <= 3)) addToGrid(new Werewolf(0, 0), g);
		else if ((typeEnemy >= 4) && (typeEnemy <= 6)) addToGrid(new Vampire(0, 0), g);
		else if ((typeEnemy >= 7) && (typeEnemy <= 11)) addToGrid(new Goblin(0, 0), g);
		else if ((typeEnemy >= 12) && (typeEnemy <= 13)) addToGrid(new Troll(0, 0), g);
		else if ((typeEnemy >= 14) && (typeEnemy <= 15)) addToGrid(new Phoenix(0, 0), g);
		else addToGrid(new Merchant(0, 0), g);
	}
}

void generateChambers(Grid* g) {
	//Step 1: Create chambers, which holds a vector<Subject*> for each chamber
	//	on the board.
	//Step 1a: Make a copy of theGrid call it copyGrid.
	vector<vector<Subject *>> copyGrid;
	copyGrid.resize(g->gridSizeY);
  	for (int y=0; y<g->gridSizeY; ++y){
		copyGrid[y].resize(g->gridSizeX);
	}
	for (int y=0; y<g->gridSizeY; ++y) {
        for (int x=0; x<g->gridSizeX; ++x) {
            copyGrid[y][x] = g->theGrid[y][x];
        }
    }
	//Step 1b: Find ChamberFloor type, if you find one, create a vector<Subject*> newChamber;
    //  on heap. Run findNextCF(*newChamber) which is going to populate all ChamberFloor's for
    //  that chamber.
    for (int y=0; y<g->gridSizeY; ++y) {
        for (int x=0; x<g->gridSizeX; ++x) {
			if (copyGrid[y][x] != nullptr) {
				if (copyGrid[y][x]->getSubject() == SubjectType::ChamberFloor) {
                	vector<Subject *>* newChamber = new vector<Subject *>();
					findNextCF(*newChamber, copyGrid[y][x], copyGrid);
					g->chambers.emplace_back(*newChamber);
				}
			}
        }
    }
}

void Grid::populateDefaultGrid() {
	//Step 1: Turn 'file'.txt into a vector<vector<Subject*>> for theGrid.
    ifstream ifs{fileName};
    string line;
	for (int j=0; j<25; ++j) {
        getline(ifs, line);
        vector<Subject*> lineSubjectPtrs;
        int lineLength = line.length();
        for (int k=0; k<lineLength; ++k) {
            lineSubjectPtrs.emplace_back(charToSubjectPtr(line[k], k, j, this));
        }
        theGrid.emplace_back(lineSubjectPtrs);
    }
	//Step 2: Now do the random generation of PC, Gold, Items etc. in Chambers.
	generateChambers(this);
	randomGeneration(this);

	//Step 3: Attach TextDisplay for all Subject*, and notifyObservers().
	for (int y=0; y<gridSizeY; ++y) {
        for (int x=0; x<gridSizeX; ++x) {
            theGrid[y][x]->attachObserver(td);
            theGrid[y][x]->notifyObservers();
        }
    }
	//Step 4: Merchants all hostile, if MerchantHostile is true.
    if (getMerchantState() == true) {
        setMerchantsHostile();
    }
}

void Grid::populateGivenGrid() {
    //Step 1: Turn 'file'.txt into a vector<vector<Subject*>> for theGrid.
    ifstream ifs{fileName};
    string line;
	//int x,y;
    for (int j=0; j<25; ++j) {
        getline(ifs, line);
        vector<Subject*> lineSubjectPtrs;
        int lineLength = line.length();
        for (int k=0; k<lineLength; ++k) {
            lineSubjectPtrs.push_back(charToSubjectPtr(line.at(k), k, j, this));
			//if (lineSubjectPtrs[k]->getSubject() == SubjectType::Human){
			//	x = c->getX();
			//	y = c->getY();
			//}
		}
        theGrid.push_back(lineSubjectPtrs);
    }
	//c->setCoords(x, y);
	//setXY(static_cast<Subject*>(c),x,y);
	static_cast<Subject*>(c)->notifyObservers();
	//Step 3: Attach TextDisplay for all Subject*, and notifyObservers().
	for (int y=0; y<gridSizeY; ++y) {
        for (int x=0; x<gridSizeX; ++x) {
			if (theGrid[y][x] != c) {
				theGrid[y][x]->attachObserver(td);
	            theGrid[y][x]->notifyObservers();
			}
		}
    }
	//Step 4: Merchants all hostile, if MerchantHostile is true.
    if (getMerchantState() == true) {
        setMerchantsHostile();
    }
}

Grid::Grid(string file): fileName{file} {
	td = new TextDisplay(gridSizeX, gridSizeY);
	level = 0;
	choosePlayableCharacter();
	//Step 1a: If the file == "defaultLayout.txt".
	if (file == "defaultLayout.txt") {
		defaultLayout = true;
		populateDefaultGrid();
	}
	//Step 1b: If user entered a layout file.
	else {
		defaultLayout = false;
		populateGivenGrid();
	}
}

void Grid::choosePlayableCharacter() {
	cout << "Please select your character!" << endl;
	cout << "Enter (h) for Human, (o) for Orc, (d) for Dwarf, (e) for Elf." << endl;
	string answer;
    while(true){
    	cin >> answer;
     	if (answer == "h"){
        	c = new Human(0, 0);
			static_cast<Subject*>(c)->attachObserver(td);
			static_cast<Playable*>(c)->getcurrTile()->attachObserver(td);
			setAction("You have been spawned as a Human.");
			break;
      	}
		else if (answer == "o"){
        	c = new Orc(0, 0);
			static_cast<Subject*>(c)->attachObserver(td);
			static_cast<Playable*>(c)->getcurrTile()->attachObserver(td);
        	setAction("You have been spawned as an Orc.");
			break;
      	}
		else if (answer == "d"){
            c = new Dwarf(0, 0);
			static_cast<Subject*>(c)->attachObserver(td);
			static_cast<Playable*>(c)->getcurrTile()->attachObserver(td);
            setAction("You have been spawned as a Dwarf.");
			break;
        }
		else {
			c = new Elf(0, 0);
			static_cast<Subject*>(c)->attachObserver(td);
			static_cast<Playable*>(c)->getcurrTile()->attachObserver(td);
			setAction("You have been spawned as an Elf.");
			break;
		}
	}
}

void Grid::printGrid() {
	string race;
	if (c->getSubject() == SubjectType::Human) race = "Human";
	else if (c->getSubject() == SubjectType::Orc) race = "Orc";
	else if (c->getSubject() == SubjectType::Elf) race = "Elf";
	else race = "Dwarf";
	cout << "Race: " << race << " Gold: "  << c->getGold() << "                       Floor: " << level+1 << endl;
	cout << "HP: " << c->getHP() << endl;
    cout << "Atk: " << c->getAtk() << endl;
    cout << "Def: " << c->getDef() << endl;
    cout << "Action: " << getAction() << endl;
}

//If you go down a level.
void Grid::clearLevel() {
	int y = 0;
	while (theGrid.size()) {
		int x = 0;
		while (theGrid[0].size()) {
			if ((y == c->getY()) && x == c->getX()) {
				delete static_cast<Playable*>(c)->getcurrTile();
				static_cast<Playable*>(c)->setcurrTile(new ChamberFloor(0, 0));
				theGrid[0].erase(theGrid[0].begin());
				continue;
			}
			delete theGrid[0][0];
			theGrid[0].erase(theGrid[0].begin());
			x++;
		}
		theGrid.erase(theGrid.begin());
		y++;
	}
	theGrid.clear();
}

int Grid::getLevel() {
	return level;
}
void Grid::setLevel(int newLevel) {
	level = newLevel;
}
Subject* Grid::getCharacter() {
	return c;
}
TextDisplay* Grid::getTextDisplay() {
	return td;
}
void Grid::setTextDisplay(TextDisplay* newtd) {
	td = newtd;
}
string Grid::getfileName() {
	return fileName;
}
bool Grid::getDefaultLayout() {
	return defaultLayout;
}

void Grid::restart() {
	clearLevel();
	delete c;
	choosePlayableCharacter();
	if (getDefaultLayout() == true) populateDefaultGrid();
	else populateGivenGrid();
	level = 0;
	setMerchantState(false);
}
void Grid::quit() {
	clearLevel();
	delete c;
}
void Grid::success() {
	double score;
	if (c->getSubject() == SubjectType::Human) score = 1.5*c->getGold();
	else score = c->getGold();
	cout << "You finished the game! Congratulations!" << endl;
	cout << "Your score is: " << score << "." << endl;
	cout << "Enter r to Restart the game, or q to Quit." << endl;
	string answer;
    while(true){
      cin >> answer;
      if (answer == "q"){
        quit();
        break;
      }
      if(answer == "r"){
        restart();
         break;
      }
    }
}
