#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     cs457::client client;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_connect_Button_clicked();

    void on_send_button_clicked();

private:
    Ui::MainWindow *ui;
    //Here is the client object. It does all the keeping track of statey stuff.
    bool debug;
};

#endif // MAINWINDOW_H
