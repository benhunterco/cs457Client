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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Here is the client object. It does all the keeping track of statey stuff.
    cs457::client client;
    bool debug;
};

#endif // MAINWINDOW_H
