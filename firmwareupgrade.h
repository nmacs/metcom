#ifndef FIRMWAREUPGRADE_H
#define FIRMWAREUPGRADE_H

#include <QDialog>
#include "zchannel.h"
#include "progress.h"

namespace Ui {
class FirmwareUpgrade;
}

class FirmwareUpgrade : public QDialog
{
    Q_OBJECT

public:
    explicit FirmwareUpgrade(ZChannel *channel, Progress *progress, QWidget *parent = 0);
    ~FirmwareUpgrade();

private slots:
    void on_btnSelectFirmware_clicked();
    void on_btnUpgrade_clicked();

private:
    Ui::FirmwareUpgrade *ui;

    QString m_firmware;
    ZChannel *m_channel;
    Progress *m_progress;
};

#endif // FIRMWAREUPGRADE_H
