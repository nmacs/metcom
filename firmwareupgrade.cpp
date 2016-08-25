#include "firmwareupgrade.h"
#include "ui_firmwareupgrade.h"

#include <QFileDialog>

#include "zfirmwareupgrade.h"

FirmwareUpgrade::FirmwareUpgrade(ZChannel *channel, Progress *progress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmwareUpgrade),
    m_channel(channel),
    m_progress(progress)
{
    ui->setupUi(this);
    ui->lblStatus->setText("");
}

FirmwareUpgrade::~FirmwareUpgrade()
{
    delete ui;
}

void FirmwareUpgrade::on_btnSelectFirmware_clicked()
{
    QString firmware = QFileDialog::getOpenFileName(this,
                                                    tr("Select Firmware file"),
                                                    "",
                                                    tr("ZixLink firmware (*.zlk)"));

    ui->txtFirmwareFile->setText(firmware);
    m_firmware = firmware;
    //settings->setValue("LastFirmwareFile", m_firmware);
}

void FirmwareUpgrade::on_btnUpgrade_clicked()
{
    bool ret;
    ZFirmwareUpgrade *upgrade = new ZFirmwareUpgrade(m_channel, m_progress, this);

    upgrade->setResetConfiguration(ui->chkResetSettings->checkState() == Qt::Checked);
    upgrade->setFirmwareFile(m_firmware);

    ret = upgrade->run();
    if (!ret)
    {
        ui->lblStatus->setText(tr("Error: ") + upgrade->errorString());
    }
    else
    {
        ui->lblStatus->setText(tr("Upgrade Done"));
    }
}
