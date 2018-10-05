/****************************
* class SysInfoTable
* Copyright (c) @ hust,maotianjiao
*
* This class defined a frame that shows 
* the system information(by the proc file-system). Include:
* (1) hostname
* (2) system start time
* (3) system uptime
* (4) system version
* (5) cpu information
****************************/

#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <iostream>
#include <string>
#include "AllStrings.h"
using namespace std;



class SysInfoTable
{
public:	
	//the main table
	GtkWidget * m_table;
public:
	SysInfoTable();
	~SysInfoTable();
	
	//show the window
	gint show();
	
	//callback of the timer
	static gint on_timer();
	
private:
	//initial the window
	gint init();
	
	//get system hostname
	GString * getHostname();
	
	//get system version
	GString * getVersion();
	
	//get system uptime(format as day:hour:minute:second)
	static GString * getUptime();
	
	//get system start time(format as day:hour:minute:second)
	GString * getStartTime();
	
	//update the system uptime
	static gint on_update_uptime(gpointer data);
	
	//get the cpu information
	GString * getCPUInfo();

	//call back of button_cpuInfo "clicked"
	static gint on_button_cpuInfo(GtkWidget *widget, gpointer data);	
		
private:
	//the hostname label
	GtkWidget * m_label_hostname;
	
	//the system version label
	GtkWidget * m_label_version;
	
	//the cpu-info label
	GtkWidget * m_label_cpuInfo;
	
	//the system start time label
	GtkWidget * m_label_startTime;
	
	//the system mission time
	GtkWidget * m_label_uptime;
	
};


