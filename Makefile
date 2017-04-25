# Enviroment
CC=g++
SOURCE=src/
FLAGS=-std=c++11 -w -O3
OUTGUI = hra2017
OUTCLI = hra2017-cli
RM=rm -fr
ZIP=xcerny63-xcecho03.zip
#-----------------------------------------

all: dep cli gui

cli: main-cli.o
	$(CC) $(FLAGS) $^ -o $(OUTCLI)

gui:
	@cd $(SOURCE) && qmake -o Makefile && make
	@mv $(SOURCE)$(OUTGUI) $(OUTGUI)

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
#-----------------------------------------

# Universal rule
%.o: $(SOURCE)%.cpp $(SOURCE)%.h
	$(CC) $(FLAGS) -c $^ -o $(SOURCE)$@

main-cli.o:
	$(CC) $(FLAGS) -c $(SOURCE)main-cli.cpp -o $@

dep:
	$(CC) $(FLAGS) -MM $(SOURCE)*.cpp $(SOURCE)*.h >dep.list
-include dep.list
#-----------------------------------------

# TESTS
test: clean build test-start 
test-start: FLAGS=-std=c++11 -O3 -Wall -Wextra -Werror -pedantic-errors -pedantic
test-start: all

	
