#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <string.h>

GtkWidget *ssslabel;
GtkWidget *rrrlabel;
char *txt_pid=NULL;
char *txt_pid2=NULL;

void restart(void)
{
	system("reboot");
}

void shutdown(void)
{
	system("halt");
}

void kill_proc(void)
{
        char buf[20];
	sprintf(buf,"kill -9 %s",txt_pid);
        system(buf);
}

void uninst_mod(void)
{
	char buf[20];
        sprintf(buf,"rmmod %s",txt_pid2);
        system(buf);
}

gint delete_event( GtkWidget *widget,
             GdkEvent *event,
             gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

void get_cpu_rate(float *temp)
{	
	FILE * fp;
        int i=0;
        float cpu,sum,user,nice,system,idle,iowait,irq,softirq;
        char _buf1[256];
	char *buf1 = _buf1;
	char *buf2,*buf3,*buf4,*buf5,*buf6,*buf7;
        
        fp=fopen("/proc/stat","r");
        fgets(buf1,256,fp);

        for(i=0;i<256;i++){
   	if(buf1[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf1[i]!=' ') break;
	}
        buf1+=i;
        user=atof(buf1);

	buf2=buf1;
        for(i=0;i<256;i++){
   	if(buf2[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf2[i]!=' ') break;
	}
        buf2+=i;
        nice=atof(buf2);

	buf3=buf2;
        for(i=0;i<256;i++){
   	if(buf3[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf3[i]!=' ') break;
	}
        buf3+=i;
        system=atof(buf3);

	buf4=buf3;
        for(i=0;i<256;i++){
   	if(buf4[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf4[i]!=' ') break;
	}
        buf4+=i;
        idle=atof(buf4);

	buf5=buf4;
        for(i=0;i<256;i++){
   	if(buf5[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf5[i]!=' ') break;
	}
        buf5+=i;
        iowait=atof(buf5);

	buf6=buf5;
        for(i=0;i<256;i++){
   	if(buf6[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf6[i]!=' ') break;
	}
        buf6+=i;
        irq=atof(buf6);

	buf7=buf6;
        for(i=0;i<256;i++){
   	if(buf7[i]==' ') break;
	}
        for(;i<256;i++){
   	if(buf7[i]!=' ') break;
	}
        buf7+=i;
        softirq=atof(buf7);
        
        cpu=user+nice+system+idle+iowait+irq+softirq;
        sum=user+nice+system;
        temp[2]=(sum-temp[0])/(cpu-temp[1]);
        temp[0]=sum;
        temp[1]=cpu;
        sprintf(buf1,"CPU使用率：%.2f%%",temp[2]*100);
        gtk_label_set_text(GTK_LABEL(ssslabel),buf1);
        return;
}

void get_mem_info(void)
{
	FILE * fp;
        int i=0;
        char _buf1[100],_buf2[100],_buf3[100],_buf4[100];
        char *buf1=_buf1;
        char *buf2=_buf2;
        char *buf3=_buf3;
        char *buf4=_buf4;
        char buffer[1000];

        fp=fopen("/proc/meminfo","r");
        fgets(buf1,50,fp);
        for(i=0;i<50;i++){
   	if(buf1[i]==' ') break;
	}
        for(;i<50;i++){
   	if(buf1[i]!=' ') break;
	}
        buf1+=i;   
        buf1[12]='\0';
        
        fgets(buf2,50,fp);
        for(i=0;i<50;i++){
   	if(buf2[i]==' ') break;
	}
        for(;i<50;i++){
   	if(buf2[i]!=' ') break;
	}
        buf2+=i;   
        buf2[12]='\0';

        for(i=0;i<10;i++){
   	fgets(buf3,50,fp);
	}
        for(i=0;i<50;i++){
   	if(buf3[i]==' ') break;
	}
        for(;i<50;i++){
   	if(buf3[i]!=' ') break;
	}
        buf3+=i;   
        buf3[12]='\0';

        fgets(buf4,50,fp);
        for(i=0;i<50;i++){
   	if(buf4[i]==' ') break;
	}
        for(;i<50;i++){
   	if(buf4[i]!=' ') break;
	}
        buf4+=i;   
        buf4[12]='\0';

        fclose(fp);

        sprintf(buffer,"总内存：%s 剩余内存：%s\n总Swap：%s 剩余Swap：%s\n",buf1,buf2,buf3,buf4);        
        gtk_label_set_text(GTK_LABEL(rrrlabel),buffer);

        return;
}

gint func(gpointer temp)
{
        get_cpu_rate((float *)temp);
        get_mem_info();
	return TRUE;
}
    
char *get_cpu_name(char *_buf1)
{

	FILE * fp;
	int i=0;
	char *buf1=_buf1;

    	fp=fopen("/proc/cpuinfo","r");
	for(i=0;i<5;i++){
   	fgets(buf1,256,fp);
	}
	for(i=0;i<256;i++){
   	if(buf1[i]==':') break;
	}
	i+=2;
	buf1+=i;
	buf1[31]='\0';
	fclose(fp);
   	return buf1;
}

char *get_cpu_type(char *_buf2)
{

	FILE * fp;
	int i=0;
	char *buf2=_buf2;

    	fp=fopen("/proc/cpuinfo","r");
	for(i=0;i<2;i++){
   	fgets(buf2,256,fp);
	}
	for(i=0;i<256;i++){
   	if(buf2[i]==':') break;
	}
	i+=2;
	buf2+=i;
	buf2[12]='\0';
	fclose(fp);
   	return buf2;
}

char *get_cpu_f(char *_buf3)
{

	FILE * fp;
	int i=0;
	char *buf3=_buf3;

    	fp=fopen("/proc/cpuinfo","r");
	for(i=0;i<7;i++){
   	fgets(buf3,256,fp);
	}
	for(i=0;i<256;i++){
   	if(buf3[i]==':') break;
	}
	i+=2;
	buf3+=i;
	buf3[8]='\0';
	fclose(fp);
   	return buf3;
}

char *get_cache_size(char *_buf4)
{

	FILE * fp;
	int i=0;
	char *buf4=_buf4;

    	fp=fopen("/proc/cpuinfo","r");
	for(i=0;i<8;i++){
   	fgets(buf4,256,fp);
	}
	for(i=0;i<256;i++){
   	if(buf4[i]==':') break;
	}
	i+=2;
	buf4+=i;
	buf4[10]='\0';
	fclose(fp);
   	return buf4;
}

char *get_system_type(char *_buf1)
{
	FILE * fp;
        int i=0;
	char *buf1=_buf1;

        fp=fopen("/proc/version","r");
        fgets(buf1,256,fp);
        for(i=0;i<256;i++){
   	if(buf1[i]==' ') break;
	}
        buf1[i]='\0';
        fclose(fp);
        return buf1;
}

char *get_system_version(char *_buf2)
{
	FILE * fp;
        int i=0;
	char *buf2=_buf2;

        fp=fopen("/proc/version","r");
        fgets(buf2,256,fp);
        for(i=0;i<256;i++){
   	if(buf2[i]=='2') break;
	}
        buf2+=i;
        for(i=0;i<256;i++){
   	if(buf2[i]==' ') break;
	}
        buf2[i]='\0';
        fclose(fp);
        return buf2;
}

char *get_gcc_version(char *_buf3)
{
	FILE * fp;
        int i=0;
        int j=0;
	char *buf3=_buf3;

        fp=fopen("/proc/version","r");
        fgets(buf3,256,fp);
        for(i=0,j=0;i<256&&j<6;i++){
   	if(buf3[i]==' ') j++;
	}
        buf3+=i;
        for(i=0;i<256;i++){
   	if(buf3[i]==')') break;
	}
        buf3[i+1]='\0';
        fclose(fp);
        return buf3;
}

void get_proc_info(GtkWidget *clist,int *p,int *q,int *r,int *s)
{
        DIR *dir;
        struct dirent *ptr;
        int i,j;
        FILE *fp;
        char buf[1024];
        char _buffer[1024];
        char *buffer=_buffer;
        char *buffer2;
        char proc_pid[1024];
        char proc_name[1024];
        char proc_stat[1024];
        char proc_pri[1024];
        char proc_takeup[1024];
        char text[5][1024];
        gchar *txt[5];

        gtk_clist_set_column_title(GTK_CLIST(clist),0,"PID");
        gtk_clist_set_column_title(GTK_CLIST(clist),1,"名称");
	gtk_clist_set_column_title(GTK_CLIST(clist),2,"状态"); 
	gtk_clist_set_column_title(GTK_CLIST(clist),3,"优先级"); 
	gtk_clist_set_column_title(GTK_CLIST(clist),4,"占用内存"); 
        gtk_clist_set_column_width(GTK_CLIST(clist),0,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),1,150);
        gtk_clist_set_column_width(GTK_CLIST(clist),2,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),3,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),4,55);
        gtk_clist_column_titles_show(GTK_CLIST(clist)); 
        dir=opendir("/proc");

        while(ptr=readdir(dir)){
                if((ptr->d_name)[0]>=48&&(ptr->d_name)[0]<=57){
                        (*p)++;
                        sprintf(buf,"/proc/%s/stat",ptr->d_name);
				
                	fp=fopen(buf,"r");
                        fgets(buffer,1024,fp);
                        fclose(fp);

                        for(i=0;i<1024;i++){
                        	if(buffer[i]==' ') break;
                        }
                        buffer[i]='\0';
                        strcpy(proc_pid,buffer);
                        i+=2;
                        buffer+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer[i]==')') break;
                        }
                        buffer[i]='\0';
                        strcpy(proc_name,buffer);
                        i+=2;
                        buffer2=buffer+i;
                        buffer2[1]='\0';
                        strcpy(proc_stat,buffer2);
                        for(i=0,j=0;i<1024&&j<15;i++){
                        	if(buffer2[i]==' ') j++;
                        }
                        buffer2+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer2[i]==' ') break;
                        }
                        buffer2[i]='\0';
                        strcpy(proc_pri,buffer2);
                        for(j=0;i<1024&&j<4;i++){
                        	if(buffer2[i]==' ') j++;
                        }
                        buffer2+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer2[i]==' ') break;
                        }
                        buffer2[i]='\0';
                        strcpy(proc_takeup,buffer2);
                        
                        if(!strcmp(proc_stat,"R")) (*q)++;
                        if(!strcmp(proc_stat,"S")) (*r)++;
			if(!strcmp(proc_stat,"Z")) (*s)++;
                                
                        sprintf(text[0],"%s",proc_pid);
                        sprintf(text[1],"%s",proc_name);
                        sprintf(text[2],"%s",proc_stat);
                        sprintf(text[3],"%s",proc_pri);
			sprintf(text[4],"%s",proc_takeup);

			txt[0]=text[0];
			txt[1]=text[1];
			txt[2]=text[2];
			txt[3]=text[3];
			txt[4]=text[4];

                        gtk_clist_append(GTK_CLIST(clist),txt);
                }
        } 

        closedir(dir);
}

void get_module_info(GtkWidget *clist2)
{
	FILE *fp;
        int i;
        char _buffer[1024];
        char *buffer=_buffer; 
        char *buffer2; 
        char mod_name[1024];
        char mod_takeup[1024];
        char mod_times[1024]; 
	char text[3][1024];
        gchar *txt[3];     

        gtk_clist_set_column_title(GTK_CLIST(clist2),0,"模块名称");
	gtk_clist_set_column_title(GTK_CLIST(clist2),1,"占用内存");
	gtk_clist_set_column_title(GTK_CLIST(clist2),2,"使用次数");
	gtk_clist_set_column_width(GTK_CLIST(clist2),0,150);
	gtk_clist_set_column_width(GTK_CLIST(clist2),1,150);
	gtk_clist_set_column_width(GTK_CLIST(clist2),2,150);
	gtk_clist_column_titles_show(GTK_CLIST(clist2));

	fp=fopen("/proc/modules","r");

        fgets(buffer,1024,fp);

        while(!feof(fp)){
        	for(i=0;i<1024;i++){
        		if(buffer[i]==' ') break;
        	}
        	buffer[i]='\0';
        	strcpy(mod_name,buffer);
        	i++;
        	buffer+=i;
        	for(i=0;i<1024;i++){
        		if(buffer[i]==' ') break;
        	}
        	buffer[i]='\0';
        	strcpy(mod_takeup,buffer);
        	i++;
        	buffer2=buffer+i;
        	for(i=0;i<1024;i++){
        		if(buffer2[i]==' ') break;
        	}
        	buffer2[i]='\0';
		strcpy(mod_times,buffer2);
	
        	sprintf(text[0],"%s",mod_name);
        	sprintf(text[1],"%s",mod_takeup);
        	sprintf(text[2],"%s",mod_times);
	
		txt[0]=text[0];
		txt[1]=text[1];
		txt[2]=text[2];
	
		gtk_clist_append(GTK_CLIST(clist2),txt);
		fgets(buffer,1024,fp);
	}
	fclose(fp);
}	

/*设置select_row信号的回调函数*/
void select_row_callback(GtkWidget *clist,gint row,gint column,GdkEventButton *event,gpointer data)
{
	
	gtk_clist_get_text(GTK_CLIST(clist),row,column,&txt_pid);
	printf("%s\n",txt_pid);
}

void select_row_callback2(GtkWidget *clist,gint row,gint column,GdkEventButton *event,gpointer data)
{
	
	gtk_clist_get_text(GTK_CLIST(clist),row,column,&txt_pid2);
	printf("%s\n",txt_pid2);
}

void refresh(GtkWidget *clist)
{
        DIR *dir;
        struct dirent *ptr;
        int i,j;
        FILE *fp;
        char buf[1024];
        char _buffer[1024];
        char *buffer=_buffer;
        char *buffer2;
        char proc_pid[1024];
        char proc_name[1024];
        char proc_stat[1024];
        char proc_pri[1024];
        char proc_takeup[1024];
        char text[5][1024];
        gchar *txt[5];

	gtk_clist_clear(GTK_CLIST(clist));
        gtk_clist_set_column_title(GTK_CLIST(clist),0,"PID");
        gtk_clist_set_column_title(GTK_CLIST(clist),1,"名称");
	gtk_clist_set_column_title(GTK_CLIST(clist),2,"状态"); 
	gtk_clist_set_column_title(GTK_CLIST(clist),3,"优先级"); 
	gtk_clist_set_column_title(GTK_CLIST(clist),4,"占用内存"); 
        gtk_clist_set_column_width(GTK_CLIST(clist),0,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),1,150);
        gtk_clist_set_column_width(GTK_CLIST(clist),2,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),3,50);
        gtk_clist_set_column_width(GTK_CLIST(clist),4,55);
        gtk_clist_column_titles_show(GTK_CLIST(clist)); 
        dir=opendir("/proc");

        while(ptr=readdir(dir)){
                if((ptr->d_name)[0]>=48&&(ptr->d_name)[0]<=57){
                        sprintf(buf,"/proc/%s/stat",ptr->d_name);
				
                	fp=fopen(buf,"r");
                        fgets(buffer,1024,fp);
                        fclose(fp);

                        for(i=0;i<1024;i++){
                        	if(buffer[i]==' ') break;
                        }
                        buffer[i]='\0';
                        strcpy(proc_pid,buffer);
                        i+=2;
                        buffer+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer[i]==')') break;
                        }
                        buffer[i]='\0';
                        strcpy(proc_name,buffer);
                        i+=2;
                        buffer2=buffer+i;
                        buffer2[1]='\0';
                        strcpy(proc_stat,buffer2);
                        for(i=0,j=0;i<1024&&j<15;i++){
                        	if(buffer2[i]==' ') j++;
                        }
                        buffer2+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer2[i]==' ') break;
                        }
                        buffer2[i]='\0';
                        strcpy(proc_pri,buffer2);
                        for(j=0;i<1024&&j<4;i++){
                        	if(buffer2[i]==' ') j++;
                        }
                        buffer2+=i;
                        for(i=0;i<1024;i++){
                        	if(buffer2[i]==' ') break;
                        }
                        buffer2[i]='\0';
                        strcpy(proc_takeup,buffer2);
                                
                        sprintf(text[0],"%s",proc_pid);
                        sprintf(text[1],"%s",proc_name);
                        sprintf(text[2],"%s",proc_stat);
                        sprintf(text[3],"%s",proc_pri);
			sprintf(text[4],"%s",proc_takeup);

			txt[0]=text[0];
			txt[1]=text[1];
			txt[2]=text[2];
			txt[3]=text[3];
			txt[4]=text[4];

                        gtk_clist_append(GTK_CLIST(clist),txt);
                }
        } 

        closedir(dir);
}

void refresh2(GtkWidget *clist2)
{
	FILE *fp;
        int i;
        char _buffer[1024];
        char *buffer=_buffer; 
        char *buffer2; 
        char mod_name[1024];
        char mod_takeup[1024];
        char mod_times[1024]; 
	char text[3][1024];
        gchar *txt[3];  
  
	gtk_clist_clear(GTK_CLIST(clist2));
        gtk_clist_set_column_title(GTK_CLIST(clist2),0,"模块名称");
	gtk_clist_set_column_title(GTK_CLIST(clist2),1,"占用内存");
	gtk_clist_set_column_title(GTK_CLIST(clist2),2,"使用次数");
	gtk_clist_set_column_width(GTK_CLIST(clist2),0,150);
	gtk_clist_set_column_width(GTK_CLIST(clist2),1,150);
	gtk_clist_set_column_width(GTK_CLIST(clist2),2,150);
	gtk_clist_column_titles_show(GTK_CLIST(clist2));

	fp=fopen("/proc/modules","r");

        fgets(buffer,1024,fp);

        while(!feof(fp)){
        	for(i=0;i<1024;i++){
        		if(buffer[i]==' ') break;
        	}
        	buffer[i]='\0';
        	strcpy(mod_name,buffer);
        	i++;
        	buffer+=i;
        	for(i=0;i<1024;i++){
        		if(buffer[i]==' ') break;
        	}
        	buffer[i]='\0';
        	strcpy(mod_takeup,buffer);
        	i++;
        	buffer2=buffer+i;
        	for(i=0;i<1024;i++){
        		if(buffer2[i]==' ') break;
        	}
        	buffer2[i]='\0';
		strcpy(mod_times,buffer2);
	
        	sprintf(text[0],"%s",mod_name);
        	sprintf(text[1],"%s",mod_takeup);
        	sprintf(text[2],"%s",mod_times);
	
		txt[0]=text[0];
		txt[1]=text[1];
		txt[2]=text[2];
	
		gtk_clist_append(GTK_CLIST(clist2),txt);
		fgets(buffer,1024,fp);
	}
	fclose(fp);
}

int main( int argc,char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *frame2;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *label;
    GtkWidget *clist,*clist2;
    GtkWidget *scrolled_window;
    char bufferf1[1000];
    char bufferf2[1000];
    char bufferl[10];
    char buf1[256],buf2[256],buf3[256],buf4[256];
    float temp[3]={0.0,0.0,0.0};  
    int p=0,q=0,r=0,s=0;  

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "系统监视器");  
    gtk_widget_set_size_request (window, 550, 400);  

    g_signal_connect (G_OBJECT (window), "delete_event",
	              G_CALLBACK (delete_event), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    table = gtk_table_new (3, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);    

    /* 创建一个新的笔记本，将标签页放在顶部 */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show (notebook);
    
    /* 建立内存资源选项卡 */
    sprintf(bufferf1, "CPU");
    sprintf(bufferf2,"内存和交换分区");
    sprintf(bufferl, "内存资源");

    vbox = gtk_vbox_new(FALSE,0);

    frame = gtk_frame_new (bufferf1);
    gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
    gtk_widget_set_size_request (frame, 500, 150);

    ssslabel = gtk_label_new ("");
    gtk_container_add (GTK_CONTAINER (frame), ssslabel);
    gtk_widget_show (ssslabel);

    gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,5);
    gtk_widget_show (frame);

    frame2 = gtk_frame_new (bufferf2);
    gtk_container_set_border_width (GTK_CONTAINER (frame2), 10);
    gtk_widget_set_size_request (frame2, 500, 150);

    rrrlabel = gtk_label_new ("");
    gtk_container_add (GTK_CONTAINER (frame2), rrrlabel);
    gtk_widget_show (rrrlabel);

    gtk_box_pack_start(GTK_BOX(vbox),frame2,FALSE,FALSE,5);
    gtk_widget_show (frame2);

    gtk_widget_show (vbox);

    label = gtk_label_new (bufferl);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, label);

    /*建立进程信息选项卡*/
    sprintf(bufferl, "进程信息");

    hbox=gtk_hbox_new(FALSE, 5);
    
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_size_request (scrolled_window, 300, 300);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);   
    clist=gtk_clist_new(5);
    get_proc_info(clist,&p,&q,&r,&s);
    gtk_signal_connect(GTK_OBJECT(clist),"select_row",GTK_SIGNAL_FUNC(select_row_callback),NULL);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window),clist); 
    gtk_box_pack_start(GTK_BOX(hbox), scrolled_window, TRUE, TRUE, 5);

    vbox=gtk_vbox_new(FALSE, 5); 
    frame = gtk_frame_new (bufferl);
    gtk_widget_set_size_request (frame, 100, 215);
    sprintf(bufferf1,"总进程数：%d\n\n运行进程：%d\n\n睡眠进程：%d\n\n僵死进程：%d\n",p,q,r,s);
    label = gtk_label_new (bufferf1);
    gtk_container_add (GTK_CONTAINER (frame), label);
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 10);
    button1 = gtk_button_new_with_label("结束进程");
    g_signal_connect (G_OBJECT (button1), "clicked",G_CALLBACK (kill_proc), "结束进程");
    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 10);
    button2 = gtk_button_new_with_label("刷新");
    g_signal_connect_swapped (G_OBJECT (button2), "clicked",G_CALLBACK (refresh), clist);
    gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 5);

    gtk_widget_show_all(hbox);

    label = gtk_label_new (bufferl);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), hbox, label);

    /*建立模块信息选项卡*/
    sprintf(bufferl, "模块信息");
    
    vbox = gtk_vbox_new(FALSE,0);
    
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_size_request (scrolled_window, 500, 250);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);   
    clist2=gtk_clist_new(3);
    get_module_info(clist2);
    gtk_signal_connect(GTK_OBJECT(clist2),"select_row",GTK_SIGNAL_FUNC(select_row_callback2),NULL);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window),clist2); 
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 5);

    hbox=gtk_hbox_new(FALSE, 5);
    button1 = gtk_button_new_with_label("装载模块");
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 50);
    button2 = gtk_button_new_with_label("卸载模块");
    g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (uninst_mod), "卸载模块");
    gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 50);
    button3 = gtk_button_new_with_label("刷新");
    g_signal_connect_swapped (G_OBJECT (button3), "clicked",G_CALLBACK (refresh2), clist2);
    gtk_box_pack_start(GTK_BOX(hbox), button3, FALSE, FALSE, 50);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);

    gtk_widget_show_all(vbox);	

    label = gtk_label_new (bufferl);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, label);

    /*建立系统信息选项卡*/
    sprintf(bufferf1, "处理器信息");
    sprintf(bufferf2,"操作系统信息");
    sprintf(bufferl, "系统信息");

    vbox = gtk_vbox_new(FALSE,0);

    frame = gtk_frame_new (bufferf1);
    gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
    gtk_widget_set_size_request (frame, 500, 150);
    sprintf(bufferf1, "CPU名称：%s\nCPU类型：%s\nCPU频率：%s MHz\nCache大小：%s\n",get_cpu_name(buf1),get_cpu_type(buf2),get_cpu_f(buf3),get_cache_size(buf4));
    label = gtk_label_new (bufferf1);
    gtk_container_add (GTK_CONTAINER (frame), label);
    gtk_widget_show (label);
    gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,5);
    gtk_widget_show (frame);

    frame2 = gtk_frame_new (bufferf2);
    gtk_container_set_border_width (GTK_CONTAINER (frame2), 10);
    gtk_widget_set_size_request (frame2, 500, 150);
    sprintf(bufferf1, "操作系统类型：%s\n操作系统版本：%s\nGCC编译器版本：%s\n",get_system_type(buf1),get_system_version(buf2),get_gcc_version(buf3));
    label = gtk_label_new (bufferf1);
    gtk_container_add (GTK_CONTAINER (frame2), label);
    gtk_widget_show (label);
    gtk_box_pack_start(GTK_BOX(vbox),frame2,FALSE,FALSE,5);
    gtk_widget_show (frame2);

    gtk_widget_show (vbox);

    label = gtk_label_new (bufferl);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, label);

    /*建立说明选项卡*/
    sprintf(bufferf1, "欢迎使用");
    sprintf(bufferf2, "作者：夏天\n\n\n信息安全0603\n\n\n012006015519\n\n\nEmail:godfather88@tom.com\n\n\n");
    sprintf(bufferl, "说明");

    hbox=gtk_hbox_new(FALSE, 5);

    frame = gtk_frame_new (bufferf1);
    label = gtk_label_new (bufferf2);
    gtk_container_add (GTK_CONTAINER (frame), label);

    gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 15);

    vbox=gtk_vbox_new(FALSE, 5); 
    button1 = gtk_button_new_with_label("重启");
    g_signal_connect (G_OBJECT (button1), "clicked",G_CALLBACK (restart), "重启");
    gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, TRUE, 35);
    button2 = gtk_button_new_with_label("关机");
    g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (shutdown), "关机");
    gtk_box_pack_start(GTK_BOX(vbox), button2, TRUE, TRUE, 35);
    button3 = gtk_button_new_with_label("退出");
    g_signal_connect (G_OBJECT (button3), "clicked",G_CALLBACK (delete_event), "退出");
    gtk_box_pack_start(GTK_BOX(vbox), button3, TRUE, TRUE, 35);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 80);

    gtk_widget_show_all(hbox);

    label = gtk_label_new (bufferl);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), hbox, label);

    /* 设置起始页(第1页) */
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);

    gtk_widget_show (table);
    gtk_widget_show (window);
    
    gtk_timeout_add(1000,func,temp);
    gtk_main ();
    
    return 0;
}







