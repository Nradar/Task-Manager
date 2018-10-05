#include <gtk/gtk.h>

gboolean expose_event_callback (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	  gdk_draw_arc(widget->window, 
	  	widget->style->fg_gc[GTK_WIDGET_STATE(widget)], TRUE,
		0, 0, widget->allocation.width, widget->allocation.height,
		0,  64 * 360);
	 
	  return TRUE;
}


int main(int argc, char **argv)
{
	GtkWidget * window;
	GtkWidget * drawingArea;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawingArea = gtk_drawing_area_new();
	
	gtk_container_add(GTK_CONTAINER(window), drawingArea);
	
	gtk_widget_set_size_request (drawingArea, 100, 100);
  	gtk_signal_connect(GTK_OBJECT(drawingArea), "expose_event",  
		GTK_SIGNAL_FUNC(expose_event_callback), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "delete_event",
		GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
                  
	gtk_widget_show_all(window);
	
	gtk_main();

	return 0;
}
