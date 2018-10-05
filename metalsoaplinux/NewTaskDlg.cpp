/****************************
* class NewTaskDlg
* Copyright (c) @ hust,maotianjiao
*
* This class defined dialog that can 
* start a new process.
****************************/

#include "NewTaskDlg.h"

//GtkWidget * NewTaskDlg::m_entry = gtk_entry_new();

//constructor of NewTaskDlg
NewTaskDlg::NewTaskDlg()
{

}

//destructor of NewTaskDlg
NewTaskDlg::~NewTaskDlg()
{

}

//initial the dialog
gint NewTaskDlg::init()
{
	GtkWidget * buttonOK;
	GtkWidget * buttonCancel;
	GtkWidget * label;
	GtkWidget * vbox;
	GtkWidget * hbox;
	
	//create all controls
	m_dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_move((GtkWindow*)m_dialog, 400, 200);
	gtk_window_set_title(GTK_WINDOW(m_dialog), STRING_RUN_PROGRAM);
	m_entry = gtk_entry_new();
	buttonOK = gtk_button_new_from_stock(GTK_STOCK_OK);
	buttonCancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	label = gtk_label_new(STRING_NOTICE);
	vbox = gtk_vbox_new(FALSE, 40);
	hbox = gtk_hbox_new(FALSE, 10);

	//set controls' size
	gtk_window_resize(GTK_WINDOW(m_dialog), 300, 150);
	gtk_button_set_alignment(GTK_BUTTON(buttonOK), 20, 20);
	
	//add the vbox to m_dialog
	gtk_container_add(GTK_CONTAINER(m_dialog), vbox);
		
	//add controls to vbox
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), m_entry, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	
	//add controls to hbox
	gtk_box_pack_start(GTK_BOX(hbox), buttonOK, TRUE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(hbox), buttonCancel, TRUE, FALSE, 10);

	//connect signals to functions
	gtk_signal_connect(GTK_OBJECT(m_dialog), "delete_event",
		GTK_SIGNAL_FUNC(on_delete), NULL);
	gtk_signal_connect(GTK_OBJECT(buttonCancel), "clicked",
		GTK_SIGNAL_FUNC(on_button_cancel), m_dialog);
	gtk_signal_connect(GTK_OBJECT(buttonOK), "clicked", 
		GTK_SIGNAL_FUNC(on_button_ok), m_entry);
	
	gtk_button_enter((GtkButton*)buttonOK);
	
	return 0;
}

//show the dialog
gint NewTaskDlg::show()
{
	init();
	gtk_widget_show_all(m_dialog);
	return 0;
}

//callback of "delete_event"
gint NewTaskDlg::on_delete(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(widget);
	return FALSE;
}

//callback of "clicked" event of buttonCancel
gint NewTaskDlg::on_button_cancel(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy((GtkWidget*)data);
	return FALSE;
}

//callback of "clicked" event of buttonOK
gint NewTaskDlg::on_button_ok(GtkWidget *widget, gpointer data)
{
	//create a new process
	int ret;
	pthread_t ntid;
	ret = pthread_create(&ntid, NULL, thread_func, 
		(void *)(gtk_entry_get_text((GtkEntry*)data)));
	if(ret != 0)
	{
		return FALSE;
	}

	return TRUE;
}

//new thread function
void* NewTaskDlg::thread_func(void * path)
{
	int pid;
	pid = fork();
	if(pid == 0)
		execv((char*)path, NULL);
}


