#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

 

#define DA_WIDTH 300

#define DA_HEIGHT 300

#define SCALE_FACTOR 1.2

#define PEN_MOVE  0
#define PEN_UP    1
#define PEN_DOWN  2


GdkPixmap *pixmap = NULL;
GtkWidget *window, *vbox, *tool_bar, *drawing_area;

gboolean status;
gboolean fdiscard = TRUE;

gint prev_x, prev_y;
GdkGC *my_gc_red;
GdkColor color;

struct ImageData {

  GtkWidget *drawing_area;

  int width, height;

  GdkPixbuf *pixbuf;

  float scale;

};

struct ImageData data;


static void expose_cb(GtkWidget *da, GdkEventExpose *event, struct ImageData *data)
{
gdk_pixbuf_render_to_drawable_alpha(data->pixbuf, da->window, 0, 0,

          0, 0, data->width, data->height,

          GDK_PIXBUF_ALPHA_FULL, 0,

          GDK_RGB_DITHER_NONE, 0, 0);

}


static void zoom(struct ImageData *data, float scale)

{

  GdkPixbuf *pixbuf;

  int width  = data->width  * scale;

  int height = data->height * scale;

 

  pixbuf = gdk_pixbuf_scale_simple(data->pixbuf, width, height,
GDK_INTERP_BILINEAR);

  if (pixbuf) {

    gdk_pixbuf_unref(data->pixbuf);

    data->pixbuf = pixbuf;

    data->width  = width;

    data->height = height;

  }

 

  gdk_window_clear(data->drawing_area->window);

  expose_cb(data->drawing_area, NULL, data);

}

 

static void zoom_in_cb(GtkWidget *widget, struct ImageData *data)

{

  zoom(data, SCALE_FACTOR);

}

 

static void zoom_out_cb(GtkWidget *widget, struct ImageData *data)

{

  zoom(data, 1.0 / SCALE_FACTOR);

}

static void clear(GtkWidget *widget)
{
int width, height;
gtk_window_get_size(GTK_WINDOW(window), &width, &height);
printf("width=%d, height=%d\n",width,height);
gdk_draw_rectangle(pixmap ,
drawing_area->style->white_gc ,
TRUE , 0 , 0 ,
width,height);    
//drawing_area->allocation.width ,
//drawing_area->allocation.height);
gtk_widget_queue_draw(drawing_area);
}


static gboolean configure_event( GtkWidget         *widget,
GdkEventConfigure *event )
{        
if (pixmap)
g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
widget->allocation.width,
widget->allocation.height,
-1);
gdk_draw_rectangle (pixmap,
widget->style->white_gc,
TRUE,
0, 0,
//1,1);
widget->allocation.width,
widget->allocation.height);

my_gc_red = gdk_gc_new(widget->window);
color.red = 0;
color.green = 0;
color.blue = 0;
gdk_gc_set_rgb_fg_color(my_gc_red , &color);

gint line_width =2;
GdkLineStyle line_style= GDK_LINE_SOLID;
GdkCapStyle cap_style=GDK_CAP_NOT_LAST;
GdkJoinStyle join_style=GDK_JOIN_MITER;
gdk_gc_set_line_attributes (my_gc_red,line_width, line_style, cap_style,join_style);
return TRUE;
}

static void draw_line(GtkWidget *widget, gint prev_x, gint prev_y, gint x, gint y) //Miao
{
GdkRectangle update_rect;
if(prev_x < x) update_rect.x = prev_x; else update_rect.x = x;
if(prev_y < y) update_rect.y = prev_y; else update_rect.y = y;

if(prev_x < x) update_rect.width = x-prev_x; else update_rect.width = prev_x-x;
if(prev_y < y) update_rect.height = y-prev_y; else update_rect.height = prev_y-y;

if(update_rect.width == 0 && update_rect.height == 0)
return;


gdk_draw_line(/*pixmap*/drawing_area->window, my_gc_red, prev_x, prev_y, x, y);
//    gtk_widget_queue_draw_area(widget ,
//                  update_rect.x-5 , update_rect.y-5 , update_rect.width+10, update_rect.height+10); 
}

static gboolean button_press_event( GtkWidget      *widget,
GdkEventButton *event )
{
status = PEN_DOWN;

prev_x =event->x; 
prev_y =event->y;

  return TRUE;
}

static gboolean button_release_event(GtkWidget       *widget,
GdkEventButton  *event)
{
status = PEN_UP;
//  printf("Up: x=%d, y=%d\n",(gint)prev_x,(gint)prev_y);

return TRUE;       
}                                    

static gboolean motion_notify_event( GtkWidget *widget,
GdkEventMotion *event )
{
int x, y;
GdkModifierType state;


  if (event->is_hint)
{
gdk_window_get_pointer (event->window, &x, &y, &state);
}
else
{
x = event->x;
y = event->y;
//state = event->state;
}

fdiscard = (fdiscard == FALSE ? TRUE: FALSE);
if(status == PEN_DOWN && pixmap != NULL)
{
if(fdiscard == TRUE)
{
draw_line(widget,prev_x, prev_y,x,y);
prev_x = x;
prev_y = y;
}

}

return TRUE;
}

int main(int argc, char *argv[])
{

//  GtkWidget *window, *vbox, *tool_bar, *drawing_area;

  GdkPixbuf *pixbuf;

//  struct ImageData data;

#ifdef DEBUG
int wid, heig;
#endif


/*
if (argc != 2) {

    printf("Usage: %s image_file\n", argv[0]);

    exit(1);

  }
*/

  gtk_init (&argc, &argv);

  /* Create top level window */   

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), "Laser Gesture Operation");
gtk_widget_set_size_request(GTK_WIDGET(window), 800, 800);

  gtk_signal_connect(GTK_OBJECT(window), "destroy",

  GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

#ifdef DEBUG
gtk_window_get_size(GTK_WINDOW(window), &wid, &heig);
printf("Top level window size: x=%d, y=%d\n",wid,heig);
#endif

  /* Create an image if any */

  pixbuf = gdk_pixbuf_new_from_file(/*argv[1]*/"1.jpg",NULL);

  if (pixbuf == NULL) {

    printf("Error: can't load picture file \"%s\"\n", argv[1]);

    exit(2);

  }

  data.pixbuf = pixbuf;

  data.width  = gdk_pixbuf_get_width(pixbuf);

  data.height = gdk_pixbuf_get_height(pixbuf);

  data.scale  = 1.0;

 

  /* Create box container */

  vbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(window), vbox);

 

  /* Create tool bar */

//  tool_bar = gtk_toolbar_new(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
tool_bar = gtk_toolbar_new();

  gtk_toolbar_set_style (GTK_TOOLBAR(tool_bar), GTK_TOOLBAR_TEXT);

//  gtk_toolbar_set_space_style (GTK_TOOLBAR(tool_bar), GTK_TOOLBAR_SPACE_LINE);

  gtk_box_pack_start(GTK_BOX(vbox), tool_bar, FALSE, FALSE, 2);

 

  /* Create zoom tools */

  gtk_toolbar_append_item(GTK_TOOLBAR(tool_bar), "+", "Zoom in",

     NULL, NULL, /* icon */

     GTK_SIGNAL_FUNC(zoom_in_cb), &data);

  gtk_toolbar_append_item(GTK_TOOLBAR(tool_bar), "-", "Zoom out",

     NULL, NULL, /* icon */

     GTK_SIGNAL_FUNC(zoom_out_cb), &data);

  gtk_toolbar_append_item(GTK_TOOLBAR(tool_bar), "Clear", "Clear",

     NULL, NULL, /* icon */

     GTK_SIGNAL_FUNC(clear), NULL);

gtk_toolbar_append_item(GTK_TOOLBAR(tool_bar), "Quit", NULL,

     NULL, NULL, /* icon */

     GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

 

  /* Create a drawing area. */

  drawing_area = gtk_drawing_area_new();

  #ifdef DEBUG
gtk_widget_set_size_request(GTK_WIDGET(drawing_area), wid, heig);
#else
gtk_widget_set_size_request(GTK_WIDGET(drawing_area), DA_WIDTH, DA_HEIGHT);
#endif

gtk_box_pack_start (GTK_BOX(vbox), drawing_area, TRUE, TRUE, 2);

gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
| GDK_LEAVE_NOTIFY_MASK
| GDK_BUTTON_PRESS_MASK
| GDK_POINTER_MOTION_MASK
| GDK_BUTTON_RELEASE_MASK
| GDK_POINTER_MOTION_HINT_MASK);

  gtk_signal_connect(GTK_OBJECT(drawing_area), "expose_event",
GTK_SIGNAL_FUNC(expose_cb), &data);

gtk_signal_connect(GTK_OBJECT(drawing_area), "configure_event",
G_CALLBACK(configure_event),NULL);

g_signal_connect (G_OBJECT(drawing_area), "motion_notify_event",
G_CALLBACK (motion_notify_event), NULL);

g_signal_connect (G_OBJECT(drawing_area), "button_press_event",
G_CALLBACK (button_press_event), drawing_area);

g_signal_connect (G_OBJECT(drawing_area), "button_release_event",
G_CALLBACK (button_release_event), drawing_area);

  data.drawing_area = drawing_area;




gtk_widget_show_all (window);

  gtk_main();

 

  return(0);

}

