#ifndef DIALOG_H
#define DIALOG_H
#include "slavethread.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void startSlave();
    void showRequest(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void activateRunButton();

private:
    Ui::Dialog *ui;
    int m_transactionCount = 0;
    SlaveThread m_thread;
};
#endif // DIALOG_H
