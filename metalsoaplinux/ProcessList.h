/*****************************
* class ProcessList
* Copyright (c) @ hust, maotianjiao
*
* description:
*	This class defined a scroll window to show
* details of every process which are running in the system
* and provide the ability to kill certain process.
*****************************/

#include <gtk/gtk.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "AllStrings.h"
using namespace std;

typedef struct list_key
{
	string pid;
	string name;
};

class ProcessList
{
public:
	ProcessList();
	~ProcessList();
	
	//show the list
	gint show();
	
	//update process information
	static gint on_update_process_info(gpointer data);
	
	//callback of buttonFind's "clicked" event
	static gint on_button_find(GtkWidget *widget, gpointer data);
	
	//callback of buttonKill's "clicked" event
	static gint on_button_kill(GtkWidget *widget, gpointer data);
	
	//callback of buttonDetail's "clicked" event
	static gint on_button_detail(GtkWidget *widget, gpointer data);
	
	//callback of buttonRefresh's "clicked" event
	static gint on_button_refresh(GtkWidget *widget, gpointer data);
	
private:
	//initial the list
	gint init();	
	
	//judge if a string is a number
	static gboolean isNumber(char *str);
public:
	//the main window
	GtkWidget *m_window;
private:
	//the scroll window
	GtkWidget *m_scrollWnd;

	//the list
	static GtkWidget *m_cList;
	
	//the number of processes
	static gint m_nProcess;
	
	//the row number of clist which is selected 
	static gint m_nSelect;
};	



