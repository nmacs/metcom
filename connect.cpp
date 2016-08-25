#include "connect.h"
#include "ui_connect.h"

#include <QTimer>
#include <QToolTip>
#include <QtSerialPort/QtSerialPort>

#include "zchanneldirectserial.h"

Connect::Connect(ZChannel *channel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    m_timer->start();

    connect(m_timer, &QTimer::timeout, this, &Connect::on_timeout);

    refreshSerialPortList();
    m_channel = channel;

    if (channel != NULL)
    {
      ui->txtPassword->setText(channel->password());

      if (dynamic_cast<ZChannelDirectSerial*>(channel) != NULL)
      {
        ZChannelDirectSerial *ch = dynamic_cast<ZChannelDirectSerial*>(channel);
        for (int c = 0; c < ui->cmbSerialPort->count(); c++)
        {
            if (ui->cmbSerialPort->itemData(c).toString() == ch->portName())
            {
                ui->cmbSerialPort->setCurrentIndex(c);
            }
        }
        ui->chkOpticalMode->setChecked(ch->opticalMode());
      }
    }
}

Connect::~Connect()
{
    delete ui;
}

void Connect::showError(QWidget *widget, QString const& text)
{
    QToolTip::showText(widget->mapToGlobal(QPoint()), text);
}

void Connect::refreshSerialPortList()
{
    QList<QSerialPortInfo>::iterator i;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int c = 0; c < ui->cmbSerialPort->count(); c++)
    {
        ui->cmbSerialPort->setItemData(c, "");
    }

    for (i = ports.begin(); i != ports.end(); i++)
    {
        QString text = i->portName() + ": " + i->description();
        QString data = i->portName();

        int ind = ui->cmbSerialPort->findText(text);
        if (ind < 0)
            ui->cmbSerialPort->addItem(text, data);
        else
            ui->cmbSerialPort->setItemData(ind, data);
    }

    for (int c = 0; c < ui->cmbSerialPort->count();)
    {
        if (ui->cmbSerialPort->itemData(c).toString() == "")
            ui->cmbSerialPort->removeItem(c);
        else
            c++;
    }
}

void Connect::on_timeout()
{
    refreshSerialPortList();
}

void Connect::on_groupSerialPort_clicked()
{
    ui->groupSerialPort->setChecked(true);
    ui->groupDialup->setChecked(false);
    ui->groupInternet->setChecked(false);
}


void Connect::on_groupDialup_clicked()
{
    ui->groupSerialPort->setChecked(false);
    ui->groupDialup->setChecked(true);
    ui->groupInternet->setChecked(false);
}

void Connect::on_groupInternet_clicked()
{
    ui->groupSerialPort->setChecked(false);
    ui->groupDialup->setChecked(false);
    ui->groupInternet->setChecked(true);
}

ZChannel* Connect::setupChannel()
{
    if (ui->txtPassword->text().isEmpty())
    {
        showError(ui->txtPassword, tr("Password is not entered"));
        ui->txtPassword->setFocus();
        return NULL;
    }

    if (ui->groupSerialPort->isChecked())
    {
        if (ui->chkOpticalMode->isChecked())
        {
            if (ui->txtMeterPassword->text().isEmpty())
            {
                showError(ui->txtMeterPassword, tr("Meter password is not entered"));
                ui->txtMeterPassword->setFocus();
                return NULL;
            }
            else if (ui->txtMeterPassword->text().length() != 8)
            {
                showError(ui->txtMeterPassword, tr("Meter password must be 8 symbols long"));
                ui->txtMeterPassword->setFocus();
                ui->txtMeterPassword->selectAll();
                return NULL;
            }
        }

        QVariant portName = ui->cmbSerialPort->currentData();
        if (!portName.isValid())
        {
            showError(ui->cmbSerialPort, tr("No serial port selected"));
            return NULL;
        }

        ZChannelDirectSerial *channel = new ZChannelDirectSerial(parent());

        channel->setPassword(ui->txtPassword->text());
        channel->setBaudRate(QSerialPort::Baud115200);
        channel->setPortName(portName.toString());

        if (ui->chkOpticalMode->isChecked())
        {
            channel->setMeterPassword(ui->txtMeterPassword->text());
            channel->setOpticalMode(true);
        }

        return channel;
    }

    return NULL;
}

ZChannel* Connect::channel()
{
    return m_channel;
}

void Connect::on_btnOk_clicked()
{
    m_channel = setupChannel();
    if (m_channel != 0)
    {
        accept();
    }
}

void Connect::on_btnCancel_clicked()
{
    m_channel = 0;
    reject();
}

void Connect::on_chkOpticalMode_toggled(bool checked)
{
    ui->lblMeterPassword->setEnabled(checked);
    ui->txtMeterPassword->setEnabled(checked);
}
