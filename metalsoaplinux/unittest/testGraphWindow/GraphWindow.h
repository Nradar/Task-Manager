/****************************
* class GraphWindow
* Copyright (c) @ hust,maotianjiao
*
* This class defined a GtkDrawingArea that shows 
* the  cpu and swap usage by a graph.
****************************/

#include <gtk/gtk.h>
//#include <gdk/gdk.h>
#include <iostream>
#include <string>
#include "DataQueue.h"
#include "AllStrings.h"
using namespace std;



class GraphWindow
{
public:
	GtkWidget * m_vbox;
	
public:
	GraphWindow();
	~GraphWindow();
	
	//initial the window
	gint init();
	
	//show the window
	gint show();
	
	//callback of m_drawingAreaCPU's expose_event
	static gint on_expose_cpu_graph(GtkWidget *widget, 
		GdkEventExpose *event, gpointer data);
	
	//callback of m_drawingAreaCPU's expose_event
	static gint on_expose_mem_graph(GtkWidget *widget, 
		GdkEventExpose *event, gpointer data);

	//callback of m_drawingAreaCPU's expose_event
	static gint on_expose_swap_graph(GtkWidget *widget, 
		GdkEventExpose *event, gpointer data);
		
	//callback of m_drawingAreaMem's expose_event
		
	//update the graph of memory usage
	static gint on_update_graph_mem(gpointer data);
	
	//update the graph of swap usage
	static gint on_update_graph_swap(gpointer data);
	
	//update the graph of cpu usage
	static gint on_update_graph_cpu(gpointer data);
		
private:
	//queue to hold information from "/proc"
	static DataQueue *m_dataQueueMem;
	static DataQueue *m_dataQueueCPU;
	static DataQueue *m_dataQueueSwap;
	GtkWidget * m_drawingAreaMem;
	GtkWidget * m_drawingAreaCPU;
	GtkWidget * m_drawingAreaSwap;
	static GdkPixmap * m_pixmapCPU;
	static GdkPixmap * m_pixmapMem;
	static GdkPixmap * m_pixmapSwap;
};


