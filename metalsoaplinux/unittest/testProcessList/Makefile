CPP = g++
test:main.o ProcessList.o
	$(CPP) -g -o test main.o ProcessList.o `pkg-config --cflags --libs gtk+-2.0`
main.o:ProcessList.h main.cpp
	$(CPP) -g -c main.cpp `pkg-config --cflags gtk+-2.0`
ProcessList.o:ProcessList.cpp ProcessList.h
	$(CPP) -g -c ProcessList.cpp `pkg-config --cflags gtk+-2.0`
clean:
	*.o


