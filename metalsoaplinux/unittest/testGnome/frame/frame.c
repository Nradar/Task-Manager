/* 框架构件示例开始frame.c */
#include <gtk/gtk.h>
int main( int argc, char *argv[] )
{
	/* 构件的存储类型是GtkWidget */
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *button;
	gint i;
	/* 初始化GTK */
	gtk_init(&argc, &argv);
	/* 创建一个新窗口*/
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Frame Example");
	/* 为窗口的" d e s t o r y "事件设置一个回调函数*/
	gtk_signal_connect (GTK_OBJECT (window), "destroy",
	GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	gtk_widget_set_usize(window, 300, 300);
	/* 设置窗口的边框宽度*/
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	/* 创建一个框架构件*/
	frame = gtk_frame_new(NULL);
	gtk_container_add(GTK_CONTAINER(window), frame);
	/* 设置框架的标签*/
	gtk_frame_set_label( GTK_FRAME(frame), "GTK Frame Widget" );
	/* 将标签在框架构件的右边对齐*/
	gtk_frame_set_label_align( GTK_FRAME(frame), 1.0, 0.0);
	/* 设置框架构件的风格*/
	gtk_frame_set_shadow_type( GTK_FRAME(frame), GTK_SHADOW_ETCHED_OUT);
	gtk_widget_show(frame);
	/* 显示窗口*/
	gtk_widget_show(window);
	/* 进入主循环*/
	gtk_main();
	return 0;
}
