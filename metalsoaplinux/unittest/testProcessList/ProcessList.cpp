/*****************************
* class ProcessList
* Copyright (c) @ hust, maotianjiao
*
* description:
*	This class defined a scroll window to show
* details of every process which are running in the system
* and provide the ability to kill certain process.
*****************************/

#include "ProcessList.h"

GtkWidget * ProcessList::m_cList = NULL;
gint ProcessList::m_nProcess = 0;
gint ProcessList::m_nSelect = -1;

//constructor of ProcessList
ProcessList::ProcessList()
{

}

//destructor of ProcessList
ProcessList::~ProcessList()
{

}

//initial the list
gint ProcessList::init()
{
	//the horizon box
	GtkWidget *hbox;
	//the "find" label
	GtkWidget *labelFind;
	//the "kill process button"
	GtkWidget *buttonKill;
	//the "detial" button
	GtkWidget *buttonDetail;
	//the "find" button
	GtkWidget *buttonFind;
	//the "refresh" button
	GtkWidget *buttonRefresh;
	//the "find process" entry
	GtkWidget *entryFind;
	
	
	//create the scrolled window add set its attribute
	m_scrollWnd = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(m_scrollWnd),
		GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
		
	//create vbox(m_window) and hbox;
	m_window = gtk_vbox_new(FALSE, 0);
	hbox = gtk_hbox_new(FALSE, 10);
	
	//create the buttons and label and entry
	buttonKill = gtk_button_new_with_label(STRING_KILL_PROCESS);
	buttonDetail = gtk_button_new_with_label(STRING_DETAIL);
	buttonFind = gtk_button_new_with_label(STRING_FIND);
	buttonRefresh = gtk_button_new_with_label(STRING_REFRESH);
	labelFind = gtk_label_new(STRING_FIND);
	entryFind = gtk_entry_new();
	
	//add entry and label and buttons to hbox
	gtk_box_pack_start(GTK_BOX(hbox), labelFind, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), entryFind, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), buttonFind, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), buttonDetail, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), buttonKill, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), buttonRefresh, FALSE, TRUE, 0);
		
	//create the list	add set its attribute
	gchar *name[6] = {STRING_PID, STRING_NAME, STRING_STATUS,
		STRING_PPID, STRING_MEMORY, STRING_PRIORITY};
	m_cList = gtk_clist_new_with_titles(6, name);
	gtk_clist_set_shadow_type(GTK_CLIST(m_cList), GTK_SHADOW_IN);
	gtk_widget_show(m_cList);
	//set the columns' width
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 0, 40);
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 1, 70);
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 2, 70);
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 3, 40);
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 4, 80);		
	gtk_clist_set_column_width(GTK_CLIST(m_cList), 5, 40);
	
	//add the list to the scrolled window
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(m_scrollWnd), m_cList);
	
	
	//add the scroll window and hbox to vbox(m_window)
	gtk_box_pack_start(GTK_BOX(m_window), m_scrollWnd, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(m_window), hbox, FALSE, TRUE, 0);
	
	//connect signals to function
	gtk_signal_connect(GTK_OBJECT(buttonFind), "clicked",
		GTK_SIGNAL_FUNC(on_button_find), entryFind);
	gtk_signal_connect(GTK_OBJECT(buttonKill), "clicked",
		GTK_SIGNAL_FUNC(on_button_kill), NULL);
	gtk_signal_connect(GTK_OBJECT(buttonDetail), "clicked",
		GTK_SIGNAL_FUNC(on_button_detail), NULL);
	gtk_signal_connect(GTK_OBJECT(buttonRefresh), "clicked",
		GTK_SIGNAL_FUNC(on_button_refresh), m_cList);
	
	//update process infomation
	on_update_process_info(m_cList);
	
	return 0;
}

//show the list
gint ProcessList::show()
{	
	init();
	gtk_widget_show_all(m_window);
	return 0;
}

//update process information
gint ProcessList::on_update_process_info(gpointer data)
{
	//freeze the list
	gtk_clist_clear((GtkCList*)data);
	gtk_clist_freeze((GtkCList*)data);

	
	DIR * dir;
	struct dirent * ptr;
	int count = 0;
	dir = opendir("/proc");
	//get the number of pid directories
	while ((ptr = readdir(dir)) != NULL)
	{
		if (isNumber(ptr->d_name))
			count++;
	}
	closedir(dir);
	
	m_nProcess = count;
	//get the name of pid directories
	string strPidDir[count + 1];
	dir = opendir("/proc");
	count = 0;
	while ((ptr = readdir(dir)) != NULL)
	{
		if (isNumber(ptr->d_name))
		{
			strPidDir[count] = ptr->d_name;
			count++;
		}
	}
	closedir(dir);
	
	string strPidPathStat[count + 1];
	string strPidPathStatm[count + 1];
	for (int i = 0; i <= count; i++)
	{
		strPidPathStat[i] = "/proc/";
		strPidPathStat[i] += strPidDir[i];
		strPidPathStat[i] += "/stat";
		
		strPidPathStatm[i] = "/proc/";
		strPidPathStatm[i] += strPidDir[i];
		strPidPathStatm[i] += "/statm";
	}
	
	for (int j = 0; j <= count; j++)
	{
		string strColumn[6], strTemp;
		FILE * pFile;
		/***************************************
		*
		*read name, Pid, PPid, status from /proc/(pid)/stat
		*
		****************************************/

		if ((pFile = freopen(strPidPathStat[j].data(), "r", stdin)) == NULL)
		{
			//thaw the list
			gtk_clist_thaw((GtkCList*)data);
			return FALSE;
		}
			
	
		cin >> strColumn[0]; //read pid
		cin >> strColumn[1]; //read name
	
		//take out the "( )"
		strColumn[1].erase(0, 1);
		strColumn[1].erase(strColumn[1].length() - 1, 1);
		
		cin >> strColumn[2]; //read status
		cin >> strColumn[3]; //read ppid
		for (int i = 0; i < 13; i++) //pass a few entry
			cin >> strTemp;
		cin >> strColumn[5]; //read priority
	
		fclose(pFile);
	
		/***************************************
		*
		*read memory usage from /proc/(pid)/statm
		*
		****************************************/
		if ((pFile = freopen(strPidPathStatm[j].data(), "r", stdin)) == NULL)
		{
			//thaw the list
			gtk_clist_thaw((GtkCList*)data);
			return FALSE;
		}
		int iMem;
		cin >> iMem;
		iMem = iMem * 4;  //each page = 4KB
	
		char strmem[20];
		sprintf(strmem, "%d KB", iMem);
		strColumn[4] = strmem;	
	
		fclose(pFile);
	
	
		//add a row to the list
		gchar *rowData[6];
		for (int i = 0; i < 6; i++)
		{
			rowData[i] = new char[20];
			strncpy(rowData[i], strColumn[i].data(), 20);
		}
		gtk_clist_append((GtkCList*)data, rowData);
		
		//set row data
		list_key *key = new list_key;
		key->pid = rowData[0];
		key->name = rowData[1];
		gtk_clist_set_row_data((GtkCList*)data, j, key);
	
		//free the memory
		for (int i = 0; i < 6; i++)
			delete rowData[i];
	
	}
		
	//thaw the list
	gtk_clist_thaw((GtkCList*)data);
	return TRUE;
}

//judge if a string is a number
gboolean ProcessList::isNumber(char * str)
{
	int i = 0;
	while (*str != '\0')
	{
		if ((*str < 48) || (*str > 57))
			return FALSE;
		str++;
	}
	return TRUE;
}

//callback of buttonFind's "clicked" event
gint ProcessList::on_button_find(GtkWidget *widget, gpointer data)
{
	char strPidOrName[50];
	static list_key *key = new list_key;
	
	strcpy(strPidOrName, gtk_entry_get_text((GtkEntry*)data));
	
	for (int i =0; i< m_nProcess; i++)
	{
		//get the key
		key = (list_key*)gtk_clist_get_row_data((GtkCList*)m_cList, i);
		
		//compare the pid
		if (strcmp(key->pid.data(), strPidOrName) == 0)
		{
			//on_update_process_info(m_cList);
			gtk_clist_select_row((GtkCList*)m_cList, i, 0);
			gtk_clist_moveto((GtkCList*)m_cList, i, 0, 0.5, 0);
			m_nSelect = i;	
			break;
		}
		
		//compare the name
		if (strcmp(key->name.data(), strPidOrName) == 0)
		{
			gtk_clist_select_row((GtkCList*)m_cList, i, 0);
			gtk_clist_moveto((GtkCList*)m_cList, i, 0, 0.5, 0);
			m_nSelect = i;	
			break;
		}
	}
	
	
	return TRUE;
}

//callback of buttonKill's "clicked" event
gint ProcessList::on_button_kill(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	static list_key *key = new list_key;
	
	if (m_nSelect >= 0)
	{
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_OK_CANCEL,
			STRING_KILL_NOTICE);	
		if (gtk_dialog_run((GtkDialog*)dialog) == GTK_RESPONSE_OK)
		{

			key = (list_key*)gtk_clist_get_row_data(
				(GtkCList*)m_cList, m_nSelect);	
			kill(atoi(key->pid.data()), SIGKILL);
			on_update_process_info(m_cList);
		}
		gtk_widget_destroy(dialog);
	}
	return 0;
}

//callback of buttonDetail's "clicked" event
gint ProcessList::on_button_detail(GtkWidget *widget, gpointer data)
{
	if (m_nSelect >= 0)
	{
		FILE *pFile;
		string strPath, strRead, strTemp;
		static list_key *key = new list_key;
		key = (list_key*)gtk_clist_get_row_data(
			(GtkCList*)m_cList, m_nSelect);
	
		//get the file path
		strPath = "/proc/";
		strPath += key->pid;
		strPath += "/stat";
	
		if ((pFile = freopen(strPath.data(), "r", stdin)) == NULL)
			return -1;
	
		//read stat and format it to a string
		strRead = "pid:\t";
		cin >> strTemp;
		strRead += strTemp + "\t" + "exName: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "state: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "ppid: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "pgid: ";
		cin >> strTemp;	
		strRead += strTemp + "\t" + "sid: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "tty_nr: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "tty_pgrp: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "flags: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "min_flt: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "cmin_flt: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "maj_flt: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "cmaj_flt: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "ntime: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "stime: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "cutime: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "cstime: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "priority: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "nice: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "num_threads: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "it_real_value: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "start_time: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "vsize: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "rss: ";	
		cin >> strTemp;
		strRead += strTemp + "\t" + "rsslim: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "start_code: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "end_code: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "start_stack: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "esp: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "eip: ";	
		cin >> strTemp;	
		strRead += strTemp + "\t" + "pending: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "blocked: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "sigign: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "sigcatch: ";	
		cin >> strTemp;
		strRead += strTemp + "\t" + "wchan: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "zero1: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "zero2: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "exit_signal: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "cpu: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "rt_priority: ";
		cin >> strTemp;
		strRead += strTemp + "\t" + "policy: ";
		cin >> strTemp;
		strRead += strTemp;
		
		fclose(pFile);
	
		GtkWidget *dialog;
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
			GTK_MESSAGE_INFO, GTK_BUTTONS_OK, strRead.data());
		gtk_window_set_title(GTK_WINDOW(dialog), STRING_PROCESS_INFO);

		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);	
		
		return 0;
	}
	return -1;	
}

//callback of buttonRefresh's "clicked" event
gint ProcessList::on_button_refresh(GtkWidget *widget, gpointer data)
{
	m_nSelect = -1;
	on_update_process_info(data);
	return 0;
}







