/**************************
* class TaskManager
* Copyright (c) @ hust,maotianjiao
*
* this class is designed to be the main window of
* taskmanager
***************************/

#include "TaskManager.h"

//constructor of TaskManager
TaskManager::TaskManager()
{
	//create main window
	m_mainWnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	//create the status bar
	m_statusbar = gtk_statusbar_new();
	on_update_statusbar(m_statusbar);
	
	//create system infomation table
	m_sysInfoTable = new SysInfoTable();
	m_sysInfoTable->show();
	
	//create the process information list
	m_processList = new ProcessList();
	m_processList->show();
	
	//create the graph window
	m_graphWindow = new GraphWindow();
	m_graphWindow->show();

}

//destructor of TaskManager
TaskManager::~TaskManager()
{
	//gtk_widget_destroy(GTK_WIDGET(m_mainWnd));
	delete m_sysInfoTable;
	delete m_processList;
	delete m_graphWindow;
}

//callback of the main window's delete event
gint TaskManager::on_delete_window(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(widget);
	gtk_main_quit();
	return TRUE;
}

//initial window
void TaskManager::init()
{
	
	GtkWidget * notebook;
	GtkWidget * table;
	GtkWidget * frame;
	GtkWidget * label;
	char *strPage[3] = {STRING_PROCESSES, STRING_PERFORMANCE, 
		STRING_SYSINFO};
	
	//set window property
	gtk_window_resize(GTK_WINDOW(m_mainWnd), 450, 500);
	//gtk_container_set_border_width(GTK_CONTAINER(m_mainWnd), 10);
	gtk_window_set_title(GTK_WINDOW(m_mainWnd), STRING_TASKMANAGER);
	
	//create the table control and set its property
	table = gtk_table_new(30, 4, FALSE);
	
	//add table to the main window
	gtk_container_add(GTK_CONTAINER(m_mainWnd), table);
	
	
	//create the notebook control and set its property
	//and add it to a frame(border width = 5)
	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
	gtk_container_set_border_width(GTK_CONTAINER(notebook), 10);
	
	//attach the menubar to table
	m_menubar = createMenubar();
	gtk_table_attach_defaults(GTK_TABLE(table), m_menubar,
		0, 4, 0, 1);
	
	//attach the notebook  to table
	gtk_table_attach_defaults(GTK_TABLE(table), notebook, 
		0, 4, 1, 29);
	
	//attah the status bar to table
	gtk_table_attach_defaults(GTK_TABLE(table), m_statusbar, 
		0, 4, 29, 30);
	
	//add some pages to the notebook
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), 
		m_graphWindow->m_vbox, gtk_label_new(STRING_PERFORMANCE));
	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), 
		m_processList->m_window, gtk_label_new(STRING_PROCESSES));
	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), 
		m_sysInfoTable->m_table, gtk_label_new(STRING_SYSINFO));
	
	
	//connect delete_event to callback on_delete_window
	gtk_signal_connect(GTK_OBJECT(m_mainWnd), "delete_event"
		,GTK_SIGNAL_FUNC(on_delete_window), NULL);
		
	//set a timer to update the status bar
	gtk_timeout_add(1000, on_update_statusbar, m_statusbar);
	
}

//show the window
gint TaskManager::show()
{
	init();
	gtk_widget_show_all(m_mainWnd);
	return 0;
}

//show the window at the expected position
gint TaskManager::show(gint x, gint y)
{
	init();
	gtk_widget_show_all(m_mainWnd);
	gtk_window_move(GTK_WINDOW(m_mainWnd), x, y);
	return 0;
}

//move the window to the expected position
gint TaskManager::move(gint x, gint y)
{
	gtk_window_move(GTK_WINDOW(m_mainWnd), x, y);
	return 0;
}

//update the information on statusbar
gint TaskManager::on_update_statusbar(gpointer data)
{
	/******************************
	*
	* update cpu usage
	*
	******************************/

	static int preTotal, preIdle, preBusy;//cpu information of last time
	int curTotal, curIdle, curBusy;//cpu information of current time
	int cputemp;
	char strtemp[80];
	float percent;
	FILE *pFile;
	string strCpuUsage;
	if((pFile = freopen("/proc/stat", "r", stdin)) == NULL)
		return -1;
	
	cin >> strtemp;  //pass the string "cpu"
	curTotal = 0;
	//read cpu information
	for (int i = 0; i < 7; i++)
	{
		cin >> cputemp;
		curTotal += cputemp;
		if (i == 3)
			curIdle = cputemp;
	}	
	fclose(pFile);
	
	//cpu usage = (curBusy - preBusy) / (curTotal - preTotal) * 100%
	curBusy = curTotal - curIdle;
	percent = ((float)(curBusy - preBusy) / 
		(float)(curTotal - preTotal)) * 100;
	
	preTotal = curTotal;
	preBusy = curBusy;
	preIdle = curIdle;
	
	int iPercent = (int)percent;
	char str[3];
	sprintf(str, "%d", iPercent);
	
	strCpuUsage += STRING_CPU_USAGE;
	strCpuUsage += ": ";
	strCpuUsage += str;
	strCpuUsage += "%";
	
	/*****************************
	*
	* update memory usage
	*
	*****************************/
	string sTempRead;
	int iTempRead;
	string strMemUsage;
	
	if ((pFile = freopen("/proc/meminfo", "r", stdin)) == NULL)
		return -1;
	
	while (sTempRead != "MemTotal:")
		cin >> sTempRead;

	//read total memory
	cin >> iTempRead;
	int memTotal = iTempRead;
	
	while (sTempRead != "MemFree:")
		cin >> sTempRead;
	//read free memory
	cin >> iTempRead;
	int memFree = iTempRead;	
	
	fclose(pFile);
	
	int memBusy = memTotal - memFree;
	int percentMem = ((float)memBusy / memTotal) * 100;
	
	char strmem[3];
	sprintf(strmem, "%d", percentMem);
	
	strMemUsage += STRING_MEM_USAGE;
	strMemUsage += ": ";
	strMemUsage += strmem;
	strMemUsage += "%";
	
	/***************************
	*
	* update time
	*
	****************************/
	string strTime;
	time_t seconds;
	struct tm* ptm;
	time(&seconds);
	ptm = localtime(&seconds);
	
	char strtm[80];
	sprintf(strtm, "%d:%d:%d", ptm->tm_hour, ptm->tm_min, 
		ptm->tm_sec);

	strTime = strtm;
	
	


	string strInfoAll;
	strInfoAll = strCpuUsage + "\t" + strMemUsage + "\t" + strTime; 
	
	gtk_statusbar_pop((GtkStatusbar*)data, 0);
	gtk_statusbar_push((GtkStatusbar*)data, 0, strInfoAll.data());
	
	return TRUE;
}

//create menubar
GtkWidget * TaskManager::createMenubar()
{
	static GtkItemFactoryEntry menu_items[] = 
	{
	 {STRING_FILE, "<ALT>F", NULL, 0, "<Branch>"},
	 {STRING_FILE_NEW_TASK, "<CTRL>N", on_menu_new_task, 0, "<Item>"},
	 {STRING_FILE_QUIT, "<CTRL>Q", on_menu_quit, 0, "<Item>"},
	 {STRING_SHUTDOWN, "<ALT>S", NULL, 0, "<Branch>"},
	 {STRING_SHUTDOWN_SHUTDOWN, "<CTRL>S", on_menu_shutdown, 0, "<Item>"},
	 {STRING_SHUTDOWN_REBOOT, "<CTRL>R", on_menu_reboot, 0, "<Item>"}, 
	 {STRING_HELP, "<ALT>H", NULL, 0, "<Branch>"},
	 {STRING_HELP_ABOUT, "<CTRL>A", on_menu_about, 0, "<Item>"}
	};
	
	static gint nmenu_items = sizeof (menu_items) / 
		sizeof (menu_items[0]);

	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;
	/* Make an accelerator group (shortcut keys) */
	accel_group = gtk_accel_group_new();
	/* Make an ItemFactory (that makes a menubar) */
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>",
	accel_group);
	/*This function generates the menu items. Pass the item factory,
	the number of items in the array, the array itself, and any
	callback data for the the menu items. */
	gtk_item_factory_create_items(item_factory, nmenu_items, 
		menu_items, NULL);
	//Attach the new accelerator group to the window.
	gtk_window_add_accel_group (GTK_WINDOW(m_mainWnd), accel_group);
	
	return gtk_item_factory_get_widget(item_factory, "<main>");
}

//callback of menu item "new task"
void TaskManager::on_menu_new_task()
{
	NewTaskDlg dialog;
	dialog.show();
}

//callback of menu item "quit"
void TaskManager::on_menu_quit()
{
	gtk_main_quit();
}

//callback of menu item "shutdown"
void TaskManager::on_menu_shutdown()
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_OK_CANCEL,
		STRING_SHUTDOWN_NOTICE);	
	if (gtk_dialog_run((GtkDialog*)dialog) == GTK_RESPONSE_OK)
		system("shutdown -h now");
	gtk_widget_destroy(dialog);
}	

//callback of menu item "shutdown"
void TaskManager::on_menu_reboot()
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_OK_CANCEL,
		STRING_REBOOT_NOTICE);	
	if (gtk_dialog_run((GtkDialog*)dialog) == GTK_RESPONSE_OK)
		system("reboot");
	gtk_widget_destroy(dialog);
}

//call back of menu item "about"
void TaskManager::on_menu_about()
{

	GtkWidget * aboutDialog;
	aboutDialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name((GtkAboutDialog*) aboutDialog,
		STRING_TASKMANAGER);
	gtk_about_dialog_set_version((GtkAboutDialog*) aboutDialog,
		STRING_TASKMANAGER_VERSION);
	gtk_about_dialog_set_copyright((GtkAboutDialog*) aboutDialog,
		STRING_COPYRIGHT);
	gtk_dialog_run((GtkDialog*)aboutDialog);
	gtk_widget_destroy(aboutDialog);
}








