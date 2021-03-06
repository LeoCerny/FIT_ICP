# Enviroment
CC=g++
SOURCE=src/
FLAGS=-std=c++11 -w -O3
OUTGUI = hra2017
OUTCLI = hra2017-cli
RM=rm -fr
TEST = tests/
ZIP=xcerny63-xcecho03.zip
#-----------------------------------------

all: gui _cli 

cli: dep _cli
	
gui: _gui	
	
_cli_start: dep _cli
_cli: $(SOURCE)Cart.o $(SOURCE)ColumnOfCart.o $(SOURCE)Package.o $(SOURCE)Game.o $(SOURCE)main-cli.cpp
	$(CC) $(FLAGS) $^ -o $(OUTCLI)

_gui:
	@cd $(SOURCE) && qmake -o Makefile && make
	@mv $(SOURCE)$(OUTGUI) .

run:
	@./$(OUTGUI)	 

zip: clean build
	find ./ -path '*/.*' -prune -o -type f -print | zip $(ZIP) -@

unzip:
	unzip $(ZIP) -d ./temp

clean:
	@$(RM) $(OUTCLI)
	@$(RM) $(OUTGUI)
	@$(RM) *.o *.log *.list TestCart TestColumnOfCart TestPackage TestGame
	@$(RM) $(SOURCE)*.o $(TEST)*.o
	@$(RM) $(ZIP)
	@$(RM) doc/* temp/

doxygen:
	doxygen ./Doxyfile	

build: clean
	@echo BUILD - START
	cd $(SOURCE) && qmake -project -o $(OUTGUI).pro
	python3 generator.py
	@echo BUILD - END

test: clean dep test-start

test-start: FLAGS=-std=c++11 -O3 -Wall -Wextra -Werror -pedantic-errors -pedantic

test-start: TestCart TestColumnOfCart TestPackage TestGame
	./TestCart
	./TestColumnOfCart
	./TestPackage
	./TestGame

TestCart: $(TEST)TestCart.o $(SOURCE)Cart.o
	$(CC) $^ -o $@

TestColumnOfCart: $(TEST)TestColumnOfCart.o $(SOURCE)Cart.o $(SOURCE)ColumnOfCart.o
	$(CC) $^ -o $@

TestPackage: $(TEST)TestPackage.o $(SOURCE)Package.o $(SOURCE)Cart.o
	$(CC) $^ -o $@

TestGame: $(TEST)TestGame.o $(SOURCE)Game.o $(SOURCE)Package.o $(SOURCE)Cart.o $(SOURCE)ColumnOfCart.o
	$(CC) $^ -o $@

# Universal rule
$(SOURCE)%.o: $(SOURCE)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(TEST)%.o: $(TEST)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

dep:
	$(CC) $(FLAGS) -MM $(SOURCE)*.cpp $(TEST)*.cpp >dep.list
-include dep.list
