/****************************
* class SysInfoTable
* Copyright (c) @ hust,maotianjiao
*
* This class defined a table that shows 
* the system information(by the proc file-system). Include:
* (1) hostname
* (2) system start time
* (3) system uptime
* (4) system version
* (5) cpu information
****************************/

#include "SysInfoTable.h"

//constructor of SysInfoTable
SysInfoTable::SysInfoTable()
{
	
	//create the main table
	m_table = gtk_table_new(10, 10, TRUE);
}

//destructor of SysInfoTable
SysInfoTable::~SysInfoTable()
{
	//gtk_widget_destroy(m_table);
}

//initial the window
gint SysInfoTable::init()
{
	
	//get the host name
	GString *strHostname = getHostname();
	m_label_hostname = gtk_label_new(strHostname->str);
	
	//get system type and version
	GString *strVersion = getVersion();
	m_label_version = gtk_label_new(strVersion->str);
	
	//get system start time
	GString *strStartTime = getStartTime();
	m_label_startTime = gtk_label_new(strStartTime->str);
	

	//get system uptime
	GString *strUptime = getUptime();
	m_label_uptime = gtk_label_new(strUptime->str);
	
	//update system uptime
	gtk_timeout_add(1000, on_update_uptime, m_label_uptime);
	
	//get the cpu information
	GString *strCPUInfo = getCPUInfo();
	m_label_cpuInfo = gtk_label_new(strCPUInfo->str);
	
	//get total information of CPU
	GtkWidget * button_cpuInfo;
	button_cpuInfo = gtk_button_new_with_label(STRING_MORE);

	//attach labels to the table
	GtkWidget * labelHostname = gtk_label_new(STRING_HOSTNAME);
	GtkWidget * labelVersion = gtk_label_new(STRING_VERSION);
	GtkWidget * labelUptime = gtk_label_new(STRING_UPTIME);
	GtkWidget * labelCPUInfo = gtk_label_new(STRING_PROCESSOR);
	GtkWidget * labelStartTime = gtk_label_new(STRING_START_TIME);
	
	gtk_table_attach_defaults(GTK_TABLE(m_table), labelHostname, 
		0, 2, 0, 2);
	gtk_table_attach_defaults(GTK_TABLE(m_table), labelVersion, 
		0, 2, 2, 4);
	gtk_table_attach_defaults(GTK_TABLE(m_table), labelUptime, 
		0, 2, 4, 6);		
	gtk_table_attach_defaults(GTK_TABLE(m_table), labelCPUInfo, 
		0, 2, 6, 8);
	gtk_table_attach_defaults(GTK_TABLE(m_table), labelStartTime, 
		0, 2, 8, 10);
			
	gtk_table_attach_defaults(GTK_TABLE(m_table), m_label_hostname, 
		2, 10, 0, 2);
	gtk_table_attach_defaults(GTK_TABLE(m_table), m_label_version,
		2, 10, 2, 4);
	gtk_table_attach_defaults(GTK_TABLE(m_table), m_label_uptime,
		2, 10, 4, 6);
	gtk_table_attach_defaults(GTK_TABLE(m_table), m_label_cpuInfo,
		2, 10, 6, 7);	
	gtk_table_attach_defaults(GTK_TABLE(m_table), m_label_startTime,
		2, 10, 8, 10);
	gtk_table_attach_defaults(GTK_TABLE(m_table), button_cpuInfo,
		4, 8, 7, 8);
		
	//set signal functions
	gtk_signal_connect(GTK_OBJECT(button_cpuInfo), "clicked",
		GTK_SIGNAL_FUNC(on_button_cpuInfo), NULL);

	return 0;
}

//show the window
gint SysInfoTable::show()
{
	init();
	gtk_widget_show_all(m_table);
	return 0;
}

//get the hostname(uses the proc file-system)
GString* SysInfoTable::getHostname()
{
	int fd, len;
	char buffer[80];
		
	if ((fd = open("/proc/sys/kernel/hostname", O_RDONLY)) < 0)
		return g_string_new("read hostname error!");
	
	len = read(fd, buffer, sizeof(buffer));
	
	close(fd);
	
	return g_string_new_len(buffer, len);
}

//get system version
GString* SysInfoTable::getVersion()
{
	int fd, len;
	char buffer[80];
	GString *strOstype;
	GString *strOsrelease;
	
	//read the os type
	if ((fd = open("/proc/sys/kernel/ostype", O_RDONLY)) < 0)
		return g_string_new("read ostype error!");
		
	len = read(fd, buffer, sizeof(buffer));
	
	close(fd);
	
	strOstype = g_string_new_len(buffer, len - 1);//-1 to take out '\n'
	
	//read the os release version
	if ((fd = open("/proc/sys/kernel/osrelease", O_RDONLY)) < 0)
		return g_string_new("read osrelease error!");
	
	len = read(fd, buffer, sizeof(buffer));
	
	close(fd);
	
	strOsrelease = g_string_new_len(buffer, len);
	
	//return informatioin
	g_string_append(strOstype, "  ");
	g_string_append(strOstype, strOsrelease->str);	
	
	return strOstype;
}

//get system uptime(format as year:hour:minute:second)
GString * SysInfoTable::getUptime()
{
	//int fd, len;
	FILE * pFile;
	char buffer[80];
	GString * strTime;
	float iTime;
	
	if ((pFile = freopen("/proc/uptime", "r", stdin)) == NULL)
		return g_string_new("read uptime error!");
	
	//read the number and convert it to string buffer
	cin >> iTime;
	sprintf(buffer, "%f", iTime);
	
	fclose(pFile);
	
	//cut the decimal off
	int i = 0;
	while ((buffer[i] != '.') && (buffer[i] != ' '))
	{
		i++;
	}
	strTime = g_string_new_len(buffer, i);
	
	//format  int to date
	int time = atoi(strTime->str);
	int day = time / 86400;
	time = time - day * 86400;
	int hour = time / 3600;
	time = time - hour * 3600;
	int minute = time / 60;
	time = time - minute * 60;
	int second = time;
	sprintf(buffer, "%d : %d : %d : %d", day, hour, minute, second);
	
	return g_string_new(buffer);
}

//get system start time
GString * SysInfoTable::getStartTime()
{
	//get current time
	time_t seconds;
	time(&seconds);
	
	//get uptime
	FILE *pFile;
	if ((pFile =freopen("/proc/uptime", "r", stdin)) == NULL)
		return g_string_new("read uptime error!");
		
	string strUptime;
	cin >> strUptime;
	
	fclose(pFile);
	
	//start time = total - uptime
	int time = atoi(strUptime.data());
	seconds -= time;
	
	//GString *strTime = g_string_new(ctime(&second));

	GString * strStartTime = g_string_new(ctime(&seconds));
	
	return strStartTime;
}

//update the system up time
gint SysInfoTable::on_update_uptime(gpointer data)
{
	gtk_label_set_text((GtkLabel*)data, getUptime()->str);
	return TRUE;
}

//get the cpu information
GString *SysInfoTable::getCPUInfo()
{
	FILE *pFile;
	//char buffer[80];
	string strTemp;
	GString * strInfo;
	if ((pFile = freopen("/proc/cpuinfo", "r", stdin)) == NULL)
		return g_string_new("read cpuinfo error!");
	
	cin >> strTemp;
	while (strTemp != "name")
		cin >> strTemp;
	cin >> strTemp;  //pass the ":"
	
	//read the information of processor
	strInfo = g_string_new("");
	cin >> strTemp;
	while (strTemp != "stepping")
	{
		g_string_append(strInfo, strTemp.data());
		g_string_append(strInfo, " ");
		cin >> strTemp;
	}
		
	fclose(pFile);
	
	return strInfo;
}

//callback of button_cpuInfo "clicked"
gint SysInfoTable::on_button_cpuInfo(GtkWidget *widget, gpointer data)
{	
	GtkWidget *dialog;
	int fd, nRead;
	char buffer[1024];
	GString *strInfo = g_string_new("");
	
	if ((fd = open("/proc/cpuinfo", O_RDONLY)) < 0)
		return FALSE;
		
	while ((nRead = read(fd, buffer, sizeof(buffer))) > 0)
		g_string_append_len(strInfo, buffer, nRead);
	
	
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
		GTK_MESSAGE_INFO, GTK_BUTTONS_OK, strInfo->str);
	gtk_window_set_title(GTK_WINDOW(dialog), "CPU Information");

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	return TRUE;
}






