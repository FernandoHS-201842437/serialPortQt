#include "dialog.h"
#include "ui_dialog.h"
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
#include "main.h"
#include "QDebug"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

 ui->m_waitRequestSpinBox->setRange(0, 10000);
    ui->m_waitRequestSpinBox->setValue(10000);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->m_serialPortComboBox->addItem(info.portName());

    setWindowTitle(tr("Blocking Slave"));
    ui->m_serialPortComboBox->setFocus();

    connect(ui->m_runButton, &QPushButton::clicked, this, &Dialog::startSlave);
    connect(&m_thread, &SlaveThread::request, this,&Dialog::showRequest);
    connect(&m_thread, &SlaveThread::error, this, &Dialog::processError);
    connect(&m_thread, &SlaveThread::timeout, this, &Dialog::processTimeout);

    connect(ui->m_serialPortComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &Dialog::activateRunButton);
    //connect(ui->m_waitRequestSpinBox, &QSpinBox::textChanged, this, &Dialog::activateRunButton);
    connect(ui->m_responseLineEdit, &QLineEdit::textChanged, this, &Dialog::activateRunButton);


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::startSlave()
{
     ui->m_runButton->setEnabled(false);
     ui->m_statusLabel->setText(tr("Status: Running, connected to port %1.")
                           .arg( ui->m_serialPortComboBox->currentText()));
     m_thread.startSlave(ui->m_serialPortComboBox->currentText(),
                        ui->m_waitRequestSpinBox->value(),
                         ui->m_responseLineEdit->text());
}

void Dialog::showRequest(const QString &s)
{
    ui->m_trafficLabel->setText(tr("Traffic, transaction #%1:"
                               "\n\r-request: %2"
                               "\n\r-response: %3")
                            .arg(++m_transactionCount)
                            .arg(s)
                            .arg( ui->m_responseLineEdit->text()));
QString str= s.mid(207,14);
   //qDebug()<<str;
 QString str2 = megafuncion(s.mid(5,200));
    //qDebug()<<str2<<endl;
    //qDebug()<<minifuncion(str,str2);
 QMessageBox msg;
 if(minifuncion(str,str2))
 {
     msg.setWindowTitle("Status Trama");
     msg.setText("Trama recibida correctamente");
     msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
     msg.exec();
 }
 else
 {
     msg.setWindowTitle("Status Trama");
     msg.setText("Trama corrompida");
     msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
     msg.exec();
 }


}

void Dialog::processError(const QString &s)
{
    activateRunButton();
     ui->m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
     ui->m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::processTimeout(const QString &s)
{
     ui->m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
     ui->m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::activateRunButton()
{
     ui->m_runButton->setEnabled(true);
}



