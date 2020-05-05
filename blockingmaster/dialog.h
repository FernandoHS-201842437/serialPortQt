#ifndef DIALOG_H
#define DIALOG_H
#include "masterthread.h"
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
    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);

private:
    void setControlsEnabled(bool enable);

private:
    Ui::Dialog *ui;
        MasterThread m_thread;
        int m_transactionCount = 0;
};
#endif // DIALOG_H
