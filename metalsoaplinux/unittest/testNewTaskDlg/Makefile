CPP = g++
test:main.o NewTaskDlg.o
	$(CPP) -g -o test -lpthread main.o NewTaskDlg.o `pkg-config --cflags --libs gtk+-2.0`
main.o:NewTaskDlg.h main.cpp
	$(CPP) -g -c main.cpp `pkg-config --cflags gtk+-2.0`
NewTaskDlg.o:NewTaskDlg.cpp NewTaskDlg.h
	$(CPP) -g -c NewTaskDlg.cpp `pkg-config --cflags gtk+-2.0`
clean:
	*.o


