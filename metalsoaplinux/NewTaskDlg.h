/****************************
* class NewTaskDlg
* Copyright (c) @ hust,maotianjiao
*
* This class defined dialog that can 
* start a new process.
****************************/

#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include "AllStrings.h"



class NewTaskDlg
{
public:	
	//the main table
	GtkWidget * m_dialog;
	
	//the pathname entry
	GtkWidget * m_entry;

public:
	NewTaskDlg();
	~NewTaskDlg();
	//show the dialog
	gint show();

	//callback of "delete_event"
	static gint on_delete(GtkWidget *widget, gpointer data);
	
	//callback of "clicked" event of buttonCancel
	static gint on_button_cancel(GtkWidget *widget, gpointer data);
	
	//callback of "clicked" event of buttonOK
	static gint on_button_ok(GtkWidget *widget, gpointer data);
	
	//new thread function
	static void* thread_func(void * path);
private:
	//initial dialog
	gint init();
};


