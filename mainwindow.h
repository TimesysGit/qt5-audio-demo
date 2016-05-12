#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#define TS_AUDIO_MSG_LEN 9
#define TS_AUDIO_MSG_PREAMBLE_OFF 0
#define TS_AUDIO_MSG_PREAMBLE_LEN 2
#define TS_AUDIO_MSG_KEY_OFF 2
#define TS_AUDIO_MSG_VAL_OFF 4
#define TS_AUDIO_MSG_TERM_OFF (TS_AUDIO_MSG_LEN - 1)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_volume_dial_valueChanged(int value);

    void on_delay_dial_valueChanged(int value);

    void on_fade_dial_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    char message_buf[TS_AUDIO_MSG_LEN];
};

#endif // MAINWINDOW_H
