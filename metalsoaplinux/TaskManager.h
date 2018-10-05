/**************************
* class TaskManager
* Copyright (c) @ hust,maotianjiao
*
* this class is designed to be the main window of
* taskmanager
***************************/

#include <gtk/gtk.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "SysInfoTable.h"
#include "ProcessList.h"
#include "NewTaskDlg.h"
#include "GraphWindow.h"
#include "AllStrings.h"

using namespace std;

class TaskManager
{
public:
	TaskManager();
	~TaskManager();
	
	//show the window at the default position(0, 0)
	gint show();
	
	//show the window at the expected position
	gint show(gint x, gint y);
	
	//move the window to the expected position
	gint move(gint x, gint y);
	
	//callback of the window's delete event
	static gint on_delete_window(GtkWidget *widget, gpointer data);
	
	//update the information on statusbar
	static gint on_update_statusbar(gpointer data);
	
	//callback of menu item "new task"
	static void on_menu_new_task();
	
	//callback of menu item "quit"
	static void on_menu_quit();
	
	//callback of menu item "about"
	static void on_menu_about();
	
	//callback of menu item "shutdown"
	static void on_menu_shutdown(); 
	
	//callback of menu item "shutdown"
	static void on_menu_reboot(); 
private:
	//initial window
	void init();
	
	//create menubar
	GtkWidget *createMenubar();

	
private:
	//the main window object
	GtkWidget * m_mainWnd;
	
	//the system information table
	SysInfoTable * m_sysInfoTable;
	
	//the process information list
	ProcessList * m_processList;
	
	//the graph window to show informations about cou,memory,swap
	GraphWindow * m_graphWindow;
	
	//the statusbar
	GtkWidget * m_statusbar;
	
	//the menubar
	GtkWidget * m_menubar;
};

















