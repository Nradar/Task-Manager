#include <gnome.h>
//#include <libgnomeui/gnome-app.h>

int main(int argc, char **argv)
{

	GtkWidget * gnomeApp;


//	GtkWidget* gnome_app_new(gchar* app_id, gchar* title)

	gnome_init("gnometest", "1.0", argc, &argv);


	gnomeApp = gnome_app_new("gnometest", "1.0");
	gtk_window_show(gnomeApp);

	gtk_main();

	return 0;
}


