#ifndef DISPLAYWORKER_H
#define DISPLAYWORKER_H
#include <QObject>
#include <string>

class displayWorker : public QObject {
    Q_OBJECT

public:
    explicit displayWorker(QObject *parent = 0) : QObject(parent) {}
    void display(QString message, QString tab, bool focus) { emit requestDisplay(message, tab, focus);}

signals:
    void requestDisplay(QString message, QString tab, bool focus);
};

#endif // DISPLAYWORKER_H
