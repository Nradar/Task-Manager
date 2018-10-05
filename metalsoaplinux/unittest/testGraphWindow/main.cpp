#include <gtk/gtk.h>
#include "GraphWindow.h"

gint on_delete(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	return TRUE;
}


int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);

	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GraphWindow *gWindow = new GraphWindow();
	gWindow->show();
	
	gtk_container_add(GTK_CONTAINER(window), gWindow->m_vbox);
	
	gtk_signal_connect(GTK_OBJECT(window), "delete_event", 
		GTK_SIGNAL_FUNC(on_delete), NULL);
	
	gtk_widget_show(window);
	
	gtk_window_resize(GTK_WINDOW(window), 400, 500);
	
	gtk_main();
	
	delete gWindow;
	return 0;
}
