/****************************
* class GraphWindow
* Copyright (c) @ hust,maotianjiao
*
* This class defined a GtkDrawingArea that shows 
* the  cpu and swap usage by a graph.
****************************/

#include "GraphWindow.h"

DataQueue *GraphWindow::m_dataQueueMem = new DataQueue();
DataQueue *GraphWindow::m_dataQueueCPU = new DataQueue();
DataQueue *GraphWindow::m_dataQueueSwap = new DataQueue();
GdkPixmap *GraphWindow::m_pixmapCPU = NULL;
GdkPixmap *GraphWindow::m_pixmapMem = NULL;
GdkPixmap *GraphWindow::m_pixmapSwap = NULL;

//constructor of GraphWindow
GraphWindow::GraphWindow()
{

}

//destructor GraphWindow
GraphWindow::~GraphWindow()
{
	delete m_dataQueueMem;
}

//initial the window
gint GraphWindow::init()
{
	GtkWidget * frameCPU;
	GtkWidget * frameMem;
	GtkWidget * frameSwap;
	//creat vbox
	m_vbox = gtk_vbox_new(FALSE, 0);
	
	//create drawing areas
	m_drawingAreaMem = gtk_drawing_area_new();
	m_drawingAreaCPU = gtk_drawing_area_new();
	m_drawingAreaSwap = gtk_drawing_area_new();
	gtk_widget_set_size_request(m_drawingAreaMem, 480 ,110);
	gtk_widget_set_size_request(m_drawingAreaCPU, 480 ,110);
	gtk_widget_set_size_request(m_drawingAreaSwap, 480 ,110);
		
	//create frames and add drawing areas to frames
	frameCPU = gtk_frame_new(STRING_CPU_USAGE_GRAPH);
	frameMem = gtk_frame_new(STRING_MEM_USAGE_GRAPH);
	frameSwap = gtk_frame_new(STRING_SWAP_USAGE_GRAPH);

	
	//add drawing areas to frames
	gtk_container_add(GTK_CONTAINER(frameCPU), m_drawingAreaCPU);
	gtk_container_add(GTK_CONTAINER(frameMem), m_drawingAreaMem);	  
	gtk_container_add(GTK_CONTAINER(frameSwap), m_drawingAreaSwap);
	
	//add frames to vbox
	gtk_box_pack_start(GTK_BOX(m_vbox), frameCPU,
		TRUE, TRUE ,0); 
	gtk_box_pack_start(GTK_BOX(m_vbox), frameMem,
		TRUE, TRUE ,0); 
	gtk_box_pack_start(GTK_BOX(m_vbox), frameSwap,
		TRUE, TRUE ,0); 


	gtk_signal_connect(GTK_OBJECT(m_drawingAreaCPU), "expose_event",  
		GTK_SIGNAL_FUNC(on_expose_cpu_graph), NULL);
	gtk_signal_connect(GTK_OBJECT(m_drawingAreaMem), "expose_event",  
		GTK_SIGNAL_FUNC(on_expose_mem_graph), NULL);
	gtk_signal_connect(GTK_OBJECT(m_drawingAreaSwap), "expose_event",  
		GTK_SIGNAL_FUNC(on_expose_swap_graph), NULL);
	//set timers to update graphs
	gtk_timeout_add(1000, on_update_graph_mem, m_drawingAreaMem);
	gtk_timeout_add(1000, on_update_graph_cpu, m_drawingAreaCPU);
	gtk_timeout_add(1000, on_update_graph_swap, m_drawingAreaSwap);
	
}

//show the window
gint GraphWindow::show()
{
	init();
	gtk_widget_show_all(m_vbox);
	//on_update_graph_mem(m_drawingAreaMem);
	return 0;
}

//callback of m_drawingAreaCpu's expose_event
gint GraphWindow::on_expose_cpu_graph(GtkWidget *widget, 
	GdkEventExpose *event, gpointer data)
{
	//on_update_graph_mem(widget);

	GdkGC *gc = gdk_gc_new(widget->window);
	if (m_pixmapCPU)
	{
		gdk_draw_pixmap(widget->window, gc, m_pixmapCPU, 
			0, 0, 0, 0, 480, 110);
	}
	else
	{
		GdkColor black, red;
		black.red = 0;
		black.blue = 0;
		black.green = 0;
		red.red = 30000;
		red.blue = 0;
		red.green = 0;
		gdk_gc_set_rgb_fg_color(gc, &black);  
		gdk_draw_rectangle(widget->window, gc, TRUE,
			0, 0, 480, 110);           
		gdk_gc_set_rgb_fg_color(gc, &red);
		gdk_draw_line(widget->window, gc, 0, 100, 479, 100);  
	}
	g_object_unref(gc);
	return TRUE;
}

//callback of m_drawingAreaMem's expose_event
gint GraphWindow::on_expose_mem_graph(GtkWidget *widget, 
	GdkEventExpose *event, gpointer data)
{
	//on_update_graph_mem(widget);

	GdkGC *gc = gdk_gc_new(widget->window);
	if (m_pixmapMem)
	{
		gdk_draw_pixmap(widget->window, gc, m_pixmapMem, 
			0, 0, 0, 0, 480, 110);
	}
	else
	{
		GdkColor black, red;
		black.red = 0;
		black.blue = 0;
		black.green = 0;
		red.red = 30000;
		red.blue = 0;
		red.green = 0;
		gdk_gc_set_rgb_fg_color(gc, &black);  
		gdk_draw_rectangle(widget->window, gc, TRUE,
			0, 0, 480, 110);           
		gdk_gc_set_rgb_fg_color(gc, &red);
		gdk_draw_line(widget->window, gc, 0, 100, 479, 100);  
	}
	g_object_unref(gc);
	return TRUE;
}

//callback of m_drawingAreaSwap's expose_event
gint GraphWindow::on_expose_swap_graph(GtkWidget *widget, 
	GdkEventExpose *event, gpointer data)
{
	//on_update_graph_mem(widget);

	GdkGC *gc = gdk_gc_new(widget->window);
	if (m_pixmapSwap)
	{
		gdk_draw_pixmap(widget->window, gc, m_pixmapSwap, 
			0, 0, 0, 0, 480, 110);
	}
	else
	{
		GdkColor black, red;
		black.red = 0;
		black.blue = 0;
		black.green = 0;
		red.red = 30000;
		red.blue = 0;
		red.green = 0;
		gdk_gc_set_rgb_fg_color(gc, &black);  
		gdk_draw_rectangle(widget->window, gc, TRUE,
			0, 0, 480, 110);           
		gdk_gc_set_rgb_fg_color(gc, &red);
		gdk_draw_line(widget->window, gc, 0, 100, 479, 100);  
	}
	g_object_unref(gc);
	return TRUE;
}

//update the graph
gint GraphWindow::on_update_graph_mem(gpointer data)
{
	/***********************
	* get the memory usage
	*
	************************/
	FILE * pFile;
	string strTemp;
	int iMemTotal, iMemFree, iMemUsage;
	int iSwapTotal, iSwapFree, iSwapUsage;
	
	if ((pFile = freopen("/proc/meminfo", "r", stdin)) == NULL)
		return FALSE;
	
	while (strTemp != "MemTotal:")
		cin >> strTemp;
	cin >> iMemTotal;  //read memtotal
	
	while (strTemp != "MemFree:")
		cin >> strTemp;
	cin >> iMemFree;  //read memfree

	fclose(pFile);
		
	iMemUsage = (float)(iMemTotal - iMemFree) / iMemTotal * 100;
	
	//push usage to the data queue
	m_dataQueueMem->push(iMemUsage);
	
	/******************************
	* redraw the memory usage graph
	*
	*******************************/

	GdkGC *gc = gdk_gc_new(GTK_WIDGET(data)->window);
	if (m_pixmapMem)
		gdk_pixmap_unref(m_pixmapMem);
	m_pixmapMem = gdk_pixmap_new(GTK_WIDGET(data)->window, 
		480, 110, -1);
	GdkColor blue, black, red;
	blue.red = 0;
	blue.blue = 0;
	blue.green = 65535;
	black.red = 0;
	black.blue = 0;
	black.green = 0;
	red.red = 30000;
	red.blue = 0;
	red.green = 0;
	gdk_gc_set_rgb_fg_color(gc, &black);  
	gdk_draw_rectangle(m_pixmapMem, gc, TRUE,
		0, 0, 480, 110);           
	gdk_gc_set_rgb_fg_color(gc, &red);
	gdk_draw_line(m_pixmapMem, gc, 0, 100, 479, 100);    
	gdk_gc_set_rgb_fg_color(gc, &blue);

	
	int qsize = m_dataQueueMem->size();
	for (int i = 1; i < qsize; i++)
	{
		gdk_draw_line(m_pixmapMem, gc, 479 - ((i - 1) * 4), 
			100 - m_dataQueueMem->getAt(qsize - i), 479 - (i * 4), 
			100 - m_dataQueueMem->getAt(qsize - i - 1));
	}
	gdk_draw_pixmap(GTK_WIDGET(data)->window, gc, m_pixmapMem, 
		0, 0, 0, 0, 480, 110);
	
	g_object_unref(gc);

	return TRUE;
	
}

//update the graph of swap usage
gint GraphWindow::on_update_graph_swap(gpointer data)
{
	/***********************
	* get the swap usage
	*
	************************/
	FILE * pFile;
	string strTemp;
	int iSwapTotal, iSwapFree, iSwapUsage;
	
	if ((pFile = freopen("/proc/meminfo", "r", stdin)) == NULL)
		return FALSE;
	

	
	while (strTemp != "SwapTotal:")
		cin >> strTemp;
	cin >> iSwapTotal;  //read swaptotal
	
	while (strTemp != "SwapFree:")
		cin >> strTemp;
	cin >> iSwapFree;  //read swapfree 
	
	fclose(pFile);
		
	iSwapUsage = (float)(iSwapTotal - iSwapFree) / iSwapTotal * 100;
	
	//push usage to the data queue
	m_dataQueueSwap->push(iSwapUsage);
	
	/******************************
	* redraw the swap usage graph
	*
	*******************************/
	GdkGC *gc = gdk_gc_new(GTK_WIDGET(data)->window);
	if (m_pixmapSwap)
		gdk_pixmap_unref(m_pixmapSwap);
	m_pixmapSwap = gdk_pixmap_new(GTK_WIDGET(data)->window, 
		480, 110, -1);
	
	GdkColor blue, black, red;
	blue.red = 0;
	blue.blue = 0;
	blue.green = 65535;
	black.red = 0;
	black.blue = 0;
	black.green = 0;
	red.red = 30000;
	red.blue = 0;
	red.green = 0;
	gdk_gc_set_rgb_fg_color(gc, &black);  
	gdk_draw_rectangle(m_pixmapSwap, gc, TRUE,
		0, 0, 480, 110);           
	gdk_gc_set_rgb_fg_color(gc, &red);
	gdk_draw_line(m_pixmapSwap, gc, 0, 100, 479, 100);    
	gdk_gc_set_rgb_fg_color(gc, &blue);

	
	
	int qsize = m_dataQueueSwap->size();
	for (int i = 1; i < qsize; i++)
	{
		gdk_draw_line(m_pixmapSwap, gc, 479 - ((i - 1) * 4), 
			100 - m_dataQueueSwap->getAt(qsize - i), 479 - (i * 4), 
			100 - m_dataQueueSwap->getAt(qsize - i - 1));
	}
	
	gdk_draw_pixmap(GTK_WIDGET(data)->window, gc, m_pixmapSwap, 
		0, 0, 0, 0, 480, 110);

	g_object_unref(gc);

	return TRUE;
}

//update the graph of cpu usage
gint GraphWindow::on_update_graph_cpu(gpointer data)
{
	/***********************
	* get the swap usage
	*
	************************/
	static int preTotal, preIdle, preBusy;//cpu information of last time
	int curTotal, curIdle, curBusy;//cpu information of current time
	int cputemp;
	char strtemp[80];
	int percent;
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
	percent = (float)(curBusy - preBusy) / 
		(curTotal - preTotal) * 100;
		
	preTotal = curTotal;
	preBusy = curBusy;
	preIdle = curIdle;
	
	m_dataQueueCPU->push(percent);
	/******************************
	* redraw the cpu usage graph
	*
	*******************************/
	GdkGC *gc = gdk_gc_new(GTK_WIDGET(data)->window);
	if (m_pixmapCPU)
		gdk_pixmap_unref(m_pixmapCPU);
	m_pixmapCPU = gdk_pixmap_new(GTK_WIDGET(data)->window, 480, 110, -1);
	
	GdkColor blue, black, red;
	blue.red = 0;
	blue.blue = 0;
	blue.green = 65535;
	black.red = 0;
	black.blue = 0;
	black.green = 0;
	red.red = 30000;
	red.blue = 0;
	red.green = 0;
	gdk_gc_set_rgb_fg_color(gc, &black);  
	gdk_draw_rectangle(m_pixmapCPU, gc, TRUE,
		0, 0, 480, 110);           
	gdk_gc_set_rgb_fg_color(gc, &red);
	gdk_draw_line(m_pixmapCPU, gc, 0, 100, 479, 100);    
	gdk_gc_set_rgb_fg_color(gc, &blue);

	
	int qsize = m_dataQueueCPU->size();
	for (int i = 1; i < qsize; i++)
	{
		gdk_draw_line(m_pixmapCPU, gc, 479 - ((i - 1) * 4), 
			100 - m_dataQueueCPU->getAt(qsize - i), 479 - (i * 4), 
			100 - m_dataQueueCPU->getAt(qsize - i - 1));
	}
	
	gdk_draw_pixmap(GTK_WIDGET(data)->window, gc, m_pixmapCPU, 
		0, 0, 0, 0, 480, 110);

	g_object_unref(gc);

	return TRUE;
}









