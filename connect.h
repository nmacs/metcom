#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>

#include "zchannel.h"

namespace Ui {
class Connect;
}

class Connect : public QDialog
{
    Q_OBJECT

public:
    explicit Connect(ZChannel *channel, QWidget *parent = 0);
    ~Connect();

    ZChannel *channel();

private slots:
    void on_timeout();

    void on_groupSerialPort_clicked();
    void on_groupDialup_clicked();
    void on_groupInternet_clicked();
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_chkOpticalMode_toggled(bool checked);

private:
    void showError(QWidget *widget, QString const& text);
    ZChannel* setupChannel();
    void refreshSerialPortList();

    Ui::Connect *ui;

    QTimer *m_timer;
    ZChannel *m_channel;
};

#endif // CONNECT_H
