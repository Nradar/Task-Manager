CPP = g++
test:main.o GraphWindow.o DataQueue.o
	$(CPP) -g -o test main.o GraphWindow.o DataQueue.o `pkg-config --cflags --libs gtk+-2.0`
main.o:GraphWindow.h main.cpp
	$(CPP) -g -c main.cpp `pkg-config --cflags gtk+-2.0`
GraphWindow.o:GraphWindow.cpp GraphWindow.h DataQueue.h
	$(CPP) -g -c GraphWindow.cpp `pkg-config --cflags gtk+-2.0`
DataQueue.o:DataQueue.cpp DataQueue.h
	$(CPP) -g -c DataQueue.cpp
clean:
	*.o


