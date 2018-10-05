#include <gtk/gtk.h>
#include "NewTaskDlg.h"


int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);

	NewTaskDlg *dialog = new NewTaskDlg();
	dialog->show();
	
	gtk_main();
	
	delete dialog;
	return 0;
}
