#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>

int a0 = 0, a1 = 0, b0 = 0, b1 = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QWidget::connect( timer, SIGNAL( timeout() ), this, SLOT( timer_update_currentTabInfo() ) );//ui控件-事件响应

    QWidget::connect( ui->tabWidget_INFO, SIGNAL( currentChanged() ),
                      this, SLOT( on_tabWidget_currentChanged() ) );
    timer->start(1000);
}




MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


void MainWindow::timer_update_currentTabInfo()
{
    int index = ui->tabWidget_INFO->currentIndex();

    //定时器只刷新内存tab页面，用于进度条动态显示
    if (index == 0)
    {
        show_tabWidgetInfo(index);
    }
}

void MainWindow::show_tabWidgetInfo(int index)
{
    QString tempStr; //读取文件信息字符串
    QFile tempFile; //用于打开系统文件
    int pos; //读取文件的位置

    if (index == 0) //内存資源
    {
        tempFile.setFileName("/proc/meminfo"); //打开内存信息文件
        if ( !tempFile.open(QIODevice::ReadOnly) )
        {
            QMessageBox::warning(this, tr("warning"), tr("The meminfo file can not open!"), QMessageBox::Yes);
            return ;
        }
        QString memTotal;
        QString memFree;
        QString memUsed;
        QString swapTotal;
        QString swapFree;
        QString swapUsed;
        int nMemTotal, nMemFree, nMemUsed, nSwapTotal, nSwapFree, nSwapUsed;

        while (1)
        {
            tempStr = tempFile.readLine();
            pos = tempStr.indexOf("MemTotal");
            if (pos != -1)
            {
                memTotal = tempStr.mid(pos+10, tempStr.length()-13);
                memTotal = memTotal.trimmed();
                nMemTotal = memTotal.toInt()/1024;
            }
            else if (pos = tempStr.indexOf("MemFree"), pos != -1)
            {
                memFree = tempStr.mid(pos+9, tempStr.length()-12);
                memFree = memFree.trimmed();
                nMemFree = memFree.toInt()/1024;
            }
            else if (pos = tempStr.indexOf("SwapTotal"), pos != -1)
            {
                swapTotal = tempStr.mid(pos+11, tempStr.length()-14);
                swapTotal = swapTotal.trimmed();
                nSwapTotal = swapTotal.toInt()/1024;
            }
            else if (pos = tempStr.indexOf("SwapFree"), pos != -1)
            {
                swapFree = tempStr.mid(pos+10,tempStr.length()-13);

                swapFree = swapFree.trimmed();
                nSwapFree = swapFree.toInt()/1024;
                break;
            }
        }
        nMemUsed = nMemTotal - nMemFree;
        nSwapUsed = nSwapTotal - nSwapFree;
        memUsed = QString::number(nMemUsed, 10);
        swapUsed = QString::number(nSwapUsed, 10);
        memFree = QString::number(nMemFree, 10);
        memTotal = QString::number(nMemTotal, 10);
        swapFree = QString::number(nSwapFree, 10);
        swapTotal = QString::number(nSwapTotal, 10);

        ui->label_RAM_Used->setText(memUsed+" MB");
        ui->label_RAM_Left->setText(memFree+" MB");
        ui->label_RAM_Total->setText(memTotal+" MB");
        ui->label_SWAP_Used->setText(swapUsed+" MB");
        ui->label_SWAP_Left->setText(swapFree+" MB");
        ui->label_SWAP_Total->setText(swapTotal+" MB");

        ui->progressBar_RAM->setValue(nMemUsed*100/nMemTotal);
        ui->progressBar_SWAP->setValue(nSwapUsed*100/nSwapTotal);
        tempFile.close(); //关闭内存信息文件

        int tt = 2; //取2个点采样计算cpu当前利用律
        int cpuInfo[2][7];
        int cpuTotal[2][2];
        while (tt)
        {
            tempFile.setFileName("/proc/stat"); //打开CPU使用状态信息
            if ( !tempFile.open(QIODevice::ReadOnly) )
            {
                QMessageBox::warning(this, tr("warning"), tr("The stat file can not open!"), QMessageBox::Yes);
                return;
            }
            tempStr = tempFile.readLine();
            for (int i = 0; i < 7; i++)
            {
                cpuInfo[2-tt][i] = tempStr.section(" ", i+1, i+1).toInt();
                cpuTotal[1][2-tt] += cpuInfo[2-tt][i];
                if (i == 3)
                {
                    cpuTotal[0][2-tt] += cpuInfo[2-tt][i];
                }
            }
            tt--;
            tempFile.close(); //关闭stat文件
        }
        int a = cpuTotal[0][1] - cpuTotal[0][0];
        int b = cpuTotal[1][1] - cpuTotal[1][0];
        if (a < 0)
        {
            a = -a;
        }
        if (b < 0)
        {
            b = -b;
        }
        ui->progressBar_CPU->setValue(a*100/b);
        tempFile.setFileName("/proc/stat");  //linux下用/proc/stat文件来计算cpu的利用率
        //这个文件包含了所有CPU活动的信息，该文件中的所有值都是从系统启动开始累计到当前时刻。

        if ( !tempFile.open(QIODevice::ReadOnly) )
        {
            QMessageBox::warning(this, tr("warning"), tr("The stat file can not open!"), QMessageBox::Yes);
            return;
        }
        tempStr = tempFile.readLine();
        a0 = a1;
        b0 = b1;
        a1 = b1 = 0;
        int gg;
        for (int i = 0; i < 7; i++)
        {
            b1 += tempStr.section(" ", i+2, i+2).toInt();
            gg = b1;
            if (i == 3)
            {
                a1 += tempStr.section(" ", i+2, i+2).toInt();
            }
        }
        int m, n;
        m = a1 - a0;
        n = b1 - b0;
        if (m < 0)
        {
            m = -m;
        }
        if (n < 0)
        {
            n = -n;
        }
        ui->progressBar_CPU->setValue( (n-m)*100/n );
        tempFile.close(); //关闭stat文件
    }
        else if (index == 1) //进程信息
        {
            ui->listWidget_process->clear();
            QDir qd("/proc");
            QStringList qsList = qd.entryList();
            QString qs = qsList.join("\n");
            QString id_of_pro;
            bool ok;
            int find_start = 3;
            int a, b;
            int nProPid; //进程PID
            int number_of_sleep = 0, number_of_run = 0, number_of_zombie = 0;
            int totalProNum = 0; //进程总数
            QString proName; //进程名
            QString proState; //进程状态
            QString proPri; //进程优先级
            QString proMem; //进程占用内存
            QListWidgetItem *title = new QListWidgetItem("PID\t" + QString::fromUtf8("Process Name") + "\t" +
                                                         QString::fromUtf8("Status") + "\t" +
                                                         QString::fromUtf8("Priority") + "\t" +
                                                         QString::fromUtf8("Memory Usage"), ui->listWidget_process);
            //循环读取进程
            while (1)
            {
                //获取进程PID
                a = qs.indexOf("\n", find_start);
                b = qs.indexOf("\n", a+1);
                find_start = b;
                id_of_pro = qs.mid(a+1, b-a-1);
                totalProNum++;
                nProPid = id_of_pro.toInt(&ok, 10);
                if(!ok)
                {
                    break;
                }

                //打开PID所对应的进程状态文件
                tempFile.setFileName("/proc/" + id_of_pro + "/stat");
                if ( !tempFile.open(QIODevice::ReadOnly) )
                {
                    QMessageBox::warning(this, tr("warning"), tr("The pid stat file can not open!"), QMessageBox::Yes);
                    return;
                }
                tempStr = tempFile.readLine();
                if (tempStr.length() == 0)
                {
                    break;
                }
                a = tempStr.indexOf("(");
                b = tempStr.indexOf(")");
                proName = tempStr.mid(a+1, b-a-1);
                proName.trimmed(); //删除两端的空格
                proState = tempStr.section(" ", 2, 2);
                proPri = tempStr.section(" ", 17, 17);
                proMem = tempStr.section(" ", 22, 22);
                switch ( proState.at(0).toLatin1() )
                {
                case 'S':   number_of_sleep++; break; //Sleep
                case 'R':   number_of_run++; break; //Running
                case 'Z':   number_of_zombie++; break; //Zombie
                default :   break;
                }
                if (proName.length() >= 12)
                {
                    QListWidgetItem *item = new QListWidgetItem(id_of_pro + "\t" +
                                                                proName + "\t" +
                                                                proState + "\t" +
                                                                proPri + "\t" +
                                                                proMem, ui->listWidget_process);
                }
                else
                {
                    QListWidgetItem *item = new QListWidgetItem(id_of_pro + "\t" +
                                                                proName + "\t\t" +
                                                                proState + "\t" +
                                                                proPri + "\t" +
                                                                proMem, ui->listWidget_process);
                }
            }
            QString temp;
            temp = QString::number(totalProNum, 10);
            ui->label_pNum->setText(temp);
            temp = QString::number(number_of_run, 10);
            ui->label_pRun->setText(temp);
            temp = QString::number(number_of_sleep, 10);
            ui->label_pSleep->setText(temp);
            temp = QString::number(number_of_zombie, 10);
            ui->label_pZombie->setText(temp);
            tempFile.close(); //关闭该PID进程的状态文件
        }
        else if (index == 2) //模块信息
        {
            ui->listWidget_model->clear();
            //sys/module 是一个 sysfs 目录层次, 包含当前加载模块的信息. /proc/moudles 是旧式的, 那种信息的单个文件版本. 其中的条目包含了模块名, 每个模块占用的内存数量, 以及使用计数. 另外的字串追加到每行的末尾来指定标志, 对这个模块当前是活动的.
            tempFile.setFileName("/proc/modules"); //打开模块信息文件
            if ( !tempFile.open(QIODevice::ReadOnly) )
            {
                QMessageBox::warning(this, tr("warning"), tr("The modules file can not open!"), QMessageBox::Yes);
                return ;
            }
            //设置模块首行项目
            QListWidgetItem *title = new QListWidgetItem( QString::fromUtf8("Module Name") + "\t\t" +
                                                          QString::fromUtf8("Memory Size") + "\t\t" +
                                                          QString::fromUtf8("Instance Loaded"), ui->listWidget_model);
            QString mod_Name, mod_Mem, mod_Num;
            //循环读取文件内容，查找需要的信息
            while (1)
            {
                tempStr = tempFile.readLine();
                if (tempStr.length() == 0)
                {
                    break;
                }
                mod_Name = tempStr.section(" ", 0, 0);
                mod_Mem = tempStr.section(" ", 1, 1);
                mod_Num = tempStr.section(" ", 2, 2);
                if (mod_Name.length() > 10)
                {
                    QListWidgetItem *item = new QListWidgetItem(mod_Name + "\t\t" +
                                                                mod_Mem + "\t\t" +
                                                                mod_Num, ui->listWidget_model);
                }
                else
                {
                    QListWidgetItem *item = new QListWidgetItem(mod_Name + "\t\t\t" +
                                                                mod_Mem + "\t\t" +
                                                                mod_Num, ui->listWidget_model);
                }
            }
            tempFile.close(); //关闭模块信息文件

        }
        else if (index == 3) //系统信息
        {
            //int ok;
            tempFile.setFileName("/proc/cpuinfo"); //打开CPU信息文件
            if ( !tempFile.open(QIODevice::ReadOnly) )
            {
                QMessageBox::warning(this, tr("warning"), tr("The cpuinfo file can not open!"), QMessageBox::Yes);
                return;
            }

            //循环读取文件内容，查找需要的信息
            while (1)
            {

                tempStr = tempFile.readLine();

                //QMessageBox::warning(this, tr("msg"), tempStr, QMessageBox::Yes);

                if(tempStr==NULL){//文件读完，跳出
                    break;
                }

                pos = tempStr.indexOf("model name");
                if (pos != -1)
                {
                    pos += 13; //跳过前面的"model name："所占用的字符
                    QString *cpu_name = new QString( tempStr.mid(pos, tempStr.length()-13) );
                    ui->label_CPUName->setText(*cpu_name);
                }
                else if (pos = tempStr.indexOf("vendor_id"), pos != -1)
                {
                    pos += 12; //跳过前面的"vendor_id："所占用的字符
                    QString *cpu_type = new QString( tempStr.mid(pos, tempStr.length()-12) );
                    ui->label_CPUType->setText(*cpu_type);
                }
                else if (pos = tempStr.indexOf("cpu MHz"), pos != -1)
                {
                    pos += 11; //跳过前面的"cpu MHz："所占用的字符
                    QString *cpu_frq = new QString( tempStr.mid(pos, tempStr.length()-11) );
                    double cpufrq = cpu_frq->toDouble(); //4核CPU
                    cpu_frq->setNum(cpufrq*4);
                    ui->label_CPUFrequency->setText(*cpu_frq + " HZ");
                }
                else if (pos = tempStr.indexOf("cache size"), pos!=-1)
                {
                    pos += 13; //跳过前面的"cache size："所占用的字符
                    QString *cache_size = new QString( tempStr.mid(pos, tempStr.length()-16) );
                    int cachesize = cache_size->toInt(); //4核CPU
                    cache_size->setNum(cachesize*4);
                    ui->label_CatheCapacity->setText(*cache_size + " KB");
                }
                else //跳过其他的内容
                {
                }
            }
            tempFile.close(); //关闭CPU信息文件
            //打开操作系统信息文件
            tempFile.setFileName("/proc/version");
            if ( !tempFile.open(QIODevice::ReadOnly) )
            {
                QMessageBox::warning(this, tr("warning"), tr("The version file can not open!"), QMessageBox::Yes);
                return ;
            }
            tempStr = tempFile.readLine();
            pos = tempStr.indexOf("version");
            QString *os_version = new QString( tempStr.mid(0, pos-1) );
            ui->label_SystemType->setText(*os_version);
            int pos1 = tempStr.indexOf("(");
            QString *os_type = new QString( tempStr.mid(pos, pos1-pos-1) );
            ui->label_SystemVersion->setText(*os_type);
            pos = tempStr.indexOf("gcc version");
            pos1 = tempStr.indexOf("#");
            QString *gcc_info = new QString( tempStr.mid(pos+12, pos1-pos-14) );
            ui->label_GCCVersion->setText(*gcc_info);
            tempFile.close(); //关闭操作系统信息文件
        }
            else //说明
            {
            }
            return;
        }

        void MainWindow::on_pushButton_halt_clicked()
        {
            system("halt");
        }

        void MainWindow::on_pushButton_reboot_clicked()
        {
            system("reboot");
        }

        void MainWindow::on_tabWidget_INFO_currentChanged(int index)
        {
            show_tabWidgetInfo(index); //显示tab中的内容
            return ;
        }

        //杀死进程
        void MainWindow::on_pushButton_pkill_clicked()
        {
            //获得进程号
            QListWidgetItem *item = ui->listWidget_process->currentItem();
            QString pro = item->text();
            pro = pro.section("\t", 0, 0);
            system("kill " + pro.toLatin1());
            QMessageBox::warning(this, tr("kill"), QString::fromUtf8("The Process Is Killed!"), QMessageBox::Yes);
            //回到进程信息tab表
            show_tabWidgetInfo(1);
        }

        //刷新进程信息
        void MainWindow::on_pushButton_prefresh_clicked()
        {
            show_tabWidgetInfo(1);
        }

        void MainWindow::on_pushButton_Model_install_clicked()
        {
            show_tabWidgetInfo(2); //安装模块还不知道如何实现
             QMessageBox::warning(this, tr("tip"), tr("Install Module Not Implemented"), QMessageBox::Yes);
        }

        void MainWindow::on_pushButton_Model_remove_clicked()
        {
            show_tabWidgetInfo(2);
            //卸载模块还不知道如何实现
            QMessageBox::warning(this, tr("tip"), tr("Remove Module Not Implemented"), QMessageBox::Yes);
        }


        void MainWindow::on_pushButton_Model_refresh_clicked()
        {
            show_tabWidgetInfo(2);
            QMessageBox::warning(this, tr("tip"), tr("Refresh Module Not Implemented"), QMessageBox::Yes);
        }
