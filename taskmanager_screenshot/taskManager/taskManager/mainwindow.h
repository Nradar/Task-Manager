#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;//界面资源类，所有的界面元素都是通过该类来调用
    QTimer *timer; //计时器

    private slots:
    void on_pushButton_pkill_clicked();
    void on_pushButton_prefresh_clicked();
    void on_pushButton_Model_install_clicked();
    void on_pushButton_Model_remove_clicked();
    void on_pushButton_Model_refresh_clicked();
    void on_pushButton_reboot_clicked();
    void on_pushButton_halt_clicked();
    void on_tabWidget_INFO_currentChanged(int index);
    void timer_update_currentTabInfo();
    //显示tab中的内容
    void show_tabWidgetInfo(int index);
};
#endif // MAINWINDOW_H
