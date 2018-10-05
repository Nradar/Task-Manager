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
    Ui::MainWindow *ui;//interface, call all interface elements
    QTimer *timer; //timer

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
    //show contents in tab
    void show_tabWidgetInfo(int index);
};
#endif // MAINWINDOW_H
