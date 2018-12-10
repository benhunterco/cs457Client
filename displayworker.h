#ifndef DISPLAYWORKER_H
#define DISPLAYWORKER_H
#include <QObject>
#include <string>

class displayWorker : public QObject {
    Q_OBJECT

public:
    explicit displayWorker(QObject *parent = 0) : QObject(parent) {}
    void display(QString message, QString tab, bool focus) { emit requestDisplay(message, tab, focus);}
    void failure(QString message) { emit requestFailure(message);}
    void status(QString status) {emit requestStatusUpdate(status);}
    void username(QString username) { emit requestUsernameUpdate(username);}
    void closeTab(QString tabName) { emit requestTabCloseByName(tabName);}

signals:
    void requestDisplay(QString message, QString tab, bool focus);
    void requestFailure(QString message);
    void requestStatusUpdate(QString status);
    void requestUsernameUpdate(QString username);
    void requestTabCloseByName(QString tabName);
};

#endif // DISPLAYWORKER_H
