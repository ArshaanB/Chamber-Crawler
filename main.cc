#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include "Grid.h"
#include "Observer.h"
#include "TextDisplay.h"
#include "Character.h"
#include "Playable.h"

using namespace std;

//loop when given invalid destination
void playerTurn(Grid& g, std::string x){
	while(!static_cast<Playable*>(g.getCharacter())->getValidPosition()){
		string j;
		cin >> j;
		if(j == "no" || j == "so" || j == "ea" || j == "we" ||
           j == "ne" || j == "nw" || j == "se" || j == "sw" ){
			static_cast<Playable*>(g.getCharacter())->move(g,j,x);
        }
        else {
			g.getTextDisplay()->printTextDisplay();
      		g.printGrid();
			continue;
		}
    }
    static_cast<Playable*>(g.getCharacter())->setValidPosition(false);
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	Grid* g;
  //sets up grid inluding asking user to select character
	if (argc == 2){
		g = new Grid(argv[1]);
	}
	else{
		g = new Grid();
	}
  //game sequence
	g->getTextDisplay()->printTextDisplay();
	g->printGrid();
	while(true){
	static_cast<Playable*>(g->getCharacter())->setValidPosition(false);
	  string i;
		cin >> i;
		if (i == "no" || i == "so" || i == "ea" || i == "we" ||
			i == "ne" || i == "nw" || i == "se" || i == "sw" ){
			static_cast<Playable*>(g->getCharacter())->move(*g,i,"m");
			if (static_cast<Playable*>(g->getCharacter())->getValidPosition() == false) {
				g->getTextDisplay()->printTextDisplay();
      			g->printGrid();
				playerTurn(*g,"m");
			}
      		g->getTextDisplay()->printTextDisplay();
      		g->printGrid();

		}
    else if(i == "u"){
      playerTurn(*g, "u");
      g->getTextDisplay()->printTextDisplay();
      g->printGrid();
    }
    else if(i == "a"){
      playerTurn(*g, "a");
      g->getTextDisplay()->printTextDisplay();
      g->printGrid();
    }
    else if(i == "r"){
      g->restart();
    }
    else if(i == "q"){
      g->quit();
      break;
    }
    else {
	  g->setAction("Invalid input, please try again.");
	  g->getTextDisplay()->printTextDisplay();
      g->printGrid();
      continue;
    }
    g->moveAllCharacters();
	g->getTextDisplay()->printTextDisplay();
	g->printGrid();
  }
}
