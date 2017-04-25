# Enviroment
CC=g++
SOURCE=src/

FLAGS=-std=c++11 -w -O3
OUTGUI = hra2017
OUTCLI = hra2017-cli
RM=rm -fr
TAR=xcerny63_xcecho03.tar
#-----------------------------------------

all: clean main.o
	$(CC) $(SOURCE)main.o -o $(OUTGUI)

tar: clean
	tar -cvf $(TAR) .*

clean:
	$(RM) $(OUTCLI)
	$(RM) $(OUTGUI)
	$(RM) *.o
	$(RM) $(TAR)
#-----------------------------------------

# Universal rule
%.o: $(SOURCE)%.cpp $(SOURCE)%.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: $(SOURCE)main.cpp
	$(CC) $(FLAGS) -c $(SOURCE)main.cpp -o $@


dep:
	$(CC) $(FLAGS) -MM $(SOURCE)*.cpp $(SOURCE)*.h >dep.list
-include dep.list
#-----------------------------------------

# TESTS
test: clean test-start 

test-start: FLAGS=-std=c++11 -O3 -Wall -Wextra -pedantic-errors
test-start: all

	
