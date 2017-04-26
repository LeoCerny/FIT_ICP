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

all: gui cli 

cli:
	@cd $(SOURCE) && $(CC) $(FLAGS) main-cli.cpp Cart.o ColumnOfCart.o Package.o Game.o -o $(OUTCLI)
	@mv $(SOURCE)$(OUTCLI) .

gui:
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
	@$(RM) *.o *.log *.list
	@$(RM) $(SOURCE)*.o
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

test-start: TestCart TestColumnOfCart
	./TestCart
	./TestColumnOfCart

TestCart: $(TEST)TestCart.o $(SOURCE)Cart.o
	$(CC) $^ -o $@

TestColumnOfCart: $(TEST)TestColumnOfCart.o $(SOURCE)Cart.o $(SOURCE)ColumnOfCart.o
	$(CC) $^ -o $@

# Universal rule
$(SOURCE)%.o: $(SOURCE)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(TEST)%.o: $(TEST)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

dep:
	$(CC) $(FLAGS) -MM $(SOURCE)*.cpp $(TEST)*.cpp >dep.list
-include dep.list
