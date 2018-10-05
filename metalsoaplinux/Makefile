CPP = g++
taskmgr:main.o TaskManager.o SysInfoTable.o ProcessList.o NewTaskDlg.o GraphWindow.o DataQueue.o
	$(CPP) -g -o taskmgr -lpthread main.o TaskManager.o SysInfoTable.o ProcessList.o NewTaskDlg.o GraphWindow.o DataQueue.o `pkg-config  --cflags  --libs gtk+-2.0`
main.o:main.cpp TaskManager.h
	$(CPP) -g -c main.cpp `pkg-config --cflags gtk+-2.0`
TaskManager.o:SysInfoTable.h TaskManager.cpp TaskManager.h NewTaskDlg.h GraphWindow.h
	$(CPP) -g -c TaskManager.cpp `pkg-config --cflags gtk+-2.0`
SysInfoTable.o:SysInfoTable.cpp SysInfoTable.h
	$(CPP) -g -c SysInfoTable.cpp `pkg-config --cflags gtk+-2.0`
ProcessList.o:ProcessList.cpp ProcessList.h
	$(CPP) -g -c ProcessList.cpp `pkg-config --cflags gtk+-2.0`
NewTaskDlg.o:NewTaskDlg.cpp NewTaskDlg.h
	$(CPP) -g -c NewTaskDlg.cpp `pkg-config --cflags gtk+-2.0`
GraphWindow.o:GraphWindow.cpp GraphWindow.h DataQueue.h
	$(CPP) -g -c GraphWindow.cpp `pkg-config --cflags gtk+-2.0`
DataQueue.o:DataQueue.cpp DataQueue.h
	$(CPP) -g -c DataQueue.cpp
