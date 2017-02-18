XXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = Subject.o Character.o Playable.o NonPlayable.o Human.o Orc.o Elf.o Dwarf.o Werewolf.o Vampire.o Goblin.o Dragon.o Merchant.o Troll.o Phoenix.o Item.o AtkPotion.o DefPotion.o HPPotion.o Gold.o Terrain.o ChamberFloor.o EmptyFloor.o Door.o WallH.o WallV.o Passage.o Stairs.o Observer.o TextDisplay.o Grid.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

 -include ${DEPENDS}

.PHONY: clean

clean: 
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
