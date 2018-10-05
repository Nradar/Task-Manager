CPP = g++
test:main.o SysInfoTable.o
	$(CPP) -g -o test main.o SysInfoTable.o `pkg-config --cflags --libs gtk+-2.0`
main.o:SysInfoTable.h main.cpp
	$(CPP) -g -c main.cpp `pkg-config --cflags gtk+-2.0`
SysInfoTable.o:SysInfoTable.cpp SysInfoTable.h
	$(CPP) -g -c SysInfoTable.cpp `pkg-config --cflags gtk+-2.0`
clean:
	*.o


