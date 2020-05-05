#include "dialog.h"
#include "ui_dialog.h"
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
       ui->m_serialPortComboBox->addItem(info.portName());

    ui->m_waitResponseSpinBox->setRange(0, 10000);
    ui->m_waitResponseSpinBox->setValue(1000);
    setWindowTitle(tr("Blocking Master"));
    ui->m_serialPortComboBox->setFocus();

    connect(ui->m_runButton, &QPushButton::clicked, this, &Dialog::transaction);
    connect(&m_thread, &MasterThread::response, this, &Dialog::showResponse);
    connect(&m_thread, &MasterThread::error, this, &Dialog::processError);
    connect(&m_thread, &MasterThread::timeout, this, &Dialog::processTimeout);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::transaction()
{
    setControlsEnabled(false);
    ui->m_statusLabel->setText(tr("Status: Running, connected to port %1.")
                           .arg(ui->m_serialPortComboBox->currentText()));
    m_thread.transaction(ui->m_serialPortComboBox->currentText(),
                         ui->m_waitResponseSpinBox->value(),
                         ui->m_requestLineEdit->text());
}

void Dialog::showResponse(const QString &s)
{
    setControlsEnabled(true);
    ui->m_trafficLabel->setText(tr("Traffic, transaction #%1:"
                               "\n\r-request: %2"
                               "\n\r-response: %3")
                            .arg(++m_transactionCount)
                            .arg(ui->m_requestLineEdit->text())
                            .arg(s));
}

void Dialog::processError(const QString &s)
{
    setControlsEnabled(true);
    ui->m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
   ui->m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::processTimeout(const QString &s)
{
    setControlsEnabled(true);
    ui->m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
    ui->m_trafficLabel->setText(tr("No traffic."));
}

void Dialog::setControlsEnabled(bool enable)
{
    ui->m_runButton->setEnabled(enable);
    ui->m_serialPortComboBox->setEnabled(enable);
    ui->m_waitResponseSpinBox->setEnabled(enable);
    ui->m_requestLineEdit->setEnabled(enable);
}

