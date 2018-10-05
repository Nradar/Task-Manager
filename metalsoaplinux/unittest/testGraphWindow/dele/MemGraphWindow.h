#include "GraphWindow.h"

class MemGraphWindow : public GraphWindow
{
public:
	MemGraphWindow();
	~MemGraphWindow();
	static gint on_update_graph(gpointer data);
public:
	static DataQueue * m_dataQueue;
};
