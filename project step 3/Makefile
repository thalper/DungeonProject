EXECUTABLE=Dungeon
CC = g++
RM=rm -f
CFLAGS = -Wall -g -std=c++11 -Werror -DTIXML_USE_STL
OBJECTS = Dungeon.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o attack.o condition.o container.o creature.o game.o item.o room.o trigger.o turnon.o XMLParser.o


run: $(EXECUTABLE) 
	./$(EXECUTABLE) Overview/sample.xml

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

.cpp.o: $(HEADERS) 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.txt
	$(RM) *.o
	$(RM) $(EXECUTABLE)
	

.PHONY : run clean