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

signals:
    void requestDisplay(QString message, QString tab, bool focus);
    void requestFailure(QString message);
    void requestStatusUpdate(QString status);
};

#endif // DISPLAYWORKER_H
