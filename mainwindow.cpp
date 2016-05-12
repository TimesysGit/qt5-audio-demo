#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/logo.png");
    ui->label_3->setPixmap(pix);
    ui->checkBox->setStyleSheet("QCheckBox::indicator { width:50px; height: 50px; }");

    /* Connect to M4 over ttyRPMSG */
    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyRPMSG");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (!serial->open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Serial port open error"), serial->errorString());
    }

    /* Initialize message buffer */
    message_buf[0]='T';
    message_buf[1]='S';
    message_buf[TS_AUDIO_MSG_TERM_OFF]='\0';
}

MainWindow::~MainWindow()
{
    if (serial->isOpen())
        serial->close();
    delete ui;
}

void MainWindow::on_checkBox_toggled(bool checked)
{    
    *(short int*) &message_buf[TS_AUDIO_MSG_KEY_OFF] = 0x1;
    if(checked) {
        *(int*) &message_buf[TS_AUDIO_MSG_VAL_OFF] = 0x1;
        serial->write(message_buf, TS_AUDIO_MSG_LEN);
    }
    else {
        *(int*) &message_buf[TS_AUDIO_MSG_VAL_OFF] = 0x0;
        serial->write(message_buf, TS_AUDIO_MSG_LEN);
    }
}

void MainWindow::on_volume_dial_valueChanged(int value)
{
    *(short int*) &message_buf[TS_AUDIO_MSG_KEY_OFF] = 0x0;
    /* TODO: Add log and fixed point conversion */
    *(int*) &message_buf[TS_AUDIO_MSG_VAL_OFF] = value;
    serial->write(message_buf, TS_AUDIO_MSG_LEN);
}

void MainWindow::on_delay_dial_valueChanged(int value)
{
    *(short int*) &message_buf[TS_AUDIO_MSG_KEY_OFF] = 0x2;
    /* TODO: Add log and fixed point conversion */
    *(int*) &message_buf[TS_AUDIO_MSG_VAL_OFF] = value;
    serial->write(message_buf, TS_AUDIO_MSG_LEN);
}

void MainWindow::on_fade_dial_valueChanged(int value)
{
    *(short int*) &message_buf[TS_AUDIO_MSG_KEY_OFF] = 0x3;
    /* TODO: Add log and fixed point conversion */
    *(int*) &message_buf[TS_AUDIO_MSG_VAL_OFF] = value;
    serial->write(message_buf, TS_AUDIO_MSG_LEN);
}
