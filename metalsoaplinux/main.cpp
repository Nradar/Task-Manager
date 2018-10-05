#include <gtk/gtk.h>
#include "TaskManager.h"


int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);
	
	TaskManager * taskmgr = new TaskManager();
	taskmgr->show();
		
	gtk_main();
	
	delete taskmgr;
	return 0;
}
