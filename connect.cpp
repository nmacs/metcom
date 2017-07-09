#include "connect.h"
#include "ui_connect.h"

#include <QTimer>
#include <QToolTip>
#include <QtSerialPort/QtSerialPort>

#include "zchanneldirectserial.h"
#include "zchannelopto.h"
#include "zchannelcsd.h"
#include "zchannelsocket.h"

Connect::Connect(ZChannel *channel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);

	//ui->txtIP->setIP("10.7.42.111");
	//ui->txtPort->setText("9999");

    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    m_timer->start();

    connect(m_timer, &QTimer::timeout, this, &Connect::on_timeout);

    refreshSerialPortList();
    m_channel = channel;

    if (channel != NULL)
    {
		ui->txtPassword->setText(channel->password());

		/*if (dynamic_cast<ZChannelCSD*>(channel) != NULL)
		{
			ui->groupSerialPort->setChecked(false);
			//ui->groupDialup->setChecked(true);
			ui->groupInternet->setChecked(false);

			ZChannelCSD *ch = dynamic_cast<ZChannelCSD*>(channel);
			for (int c = 0; c < ui->cmbDialupSerialPort->count(); c++)
			{
				if (ui->cmbDialupSerialPort->itemData(c).toString() == ch->portName())
				{
					ui->cmbDialupSerialPort->setCurrentIndex(c);
				}
			}

			ui->cmbBaud->setCurrentText(QString::number(ch->baudRate()));
			ui->txtPhone->setText(ch->phoneNumbaer());
		}
		else */
		if (dynamic_cast<ZChannelDirectSerial*>(channel) != NULL)
		{
			ui->groupSerialPort->setChecked(true);
			//ui->groupDialup->setChecked(false);
			ui->groupInternet->setChecked(false);

			ZChannelDirectSerial *ch = dynamic_cast<ZChannelDirectSerial*>(channel);
			for (int c = 0; c < ui->cmbSerialPort->count(); c++)
			{
				if (ui->cmbSerialPort->itemData(c).toString() == ch->portName())
				{
					ui->cmbSerialPort->setCurrentIndex(c);
				}
			}

			if (dynamic_cast<ZChannelOpto*>(channel) != NULL)
			{
				ui->chkOpticalMode->setChecked(true);
				ui->mode_7E1->setChecked(dynamic_cast<ZChannelOpto*>(channel)->getMode() == ZChannelOpto::mode_7E1);
			}
			else
			{
				ui->chkOpticalMode->setChecked(false);
			}
		}
		else if (dynamic_cast<ZChannelSocket*>(channel) != NULL)
		{
			ui->groupSerialPort->setChecked(false);
			//ui->groupDialup->setChecked(false);
			ui->groupInternet->setChecked(true);

			ZChannelSocket *ch = dynamic_cast<ZChannelSocket*>(channel);

			ui->txtIP->setIP(ch->address());
			ui->txtPort->setText(QString::number(ch->port()));
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
		//ui->cmbDialupSerialPort->setItemData(c, "");
    }

    for (i = ports.begin(); i != ports.end(); i++)
    {
        QString text = i->portName() + ": " + i->description();
        QString data = i->portName();

        int ind = ui->cmbSerialPort->findText(text);
		if (ind < 0)
		{
			ui->cmbSerialPort->addItem(text, data);
			//ui->cmbDialupSerialPort->addItem(text, data);
		}
		else
		{
			ui->cmbSerialPort->setItemData(ind, data);
			//ui->cmbDialupSerialPort->setItemData(ind, data);
		}
    }

    for (int c = 0; c < ui->cmbSerialPort->count();)
    {
        if (ui->cmbSerialPort->itemData(c).toString() == "")
            ui->cmbSerialPort->removeItem(c);
        else
            c++;
    }

	/*for (int c = 0; c < ui->cmbDialupSerialPort->count();)
	{
		if (ui->cmbDialupSerialPort->itemData(c).toString() == "")
			ui->cmbDialupSerialPort->removeItem(c);
		else
			c++;
	}*/
}

void Connect::on_timeout()
{
    refreshSerialPortList();
}

void Connect::on_groupSerialPort_clicked()
{
    ui->groupSerialPort->setChecked(true);
    //ui->groupDialup->setChecked(false);
    ui->groupInternet->setChecked(false);
}


void Connect::on_groupDialup_clicked()
{
    ui->groupSerialPort->setChecked(false);
    //ui->groupDialup->setChecked(true);
    ui->groupInternet->setChecked(false);
}

void Connect::on_groupInternet_clicked()
{
    ui->groupSerialPort->setChecked(false);
    //ui->groupDialup->setChecked(false);
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

		ZChannelDirectSerial *channel;
		if (ui->chkOpticalMode->isChecked())
		{
			ZChannelOpto* opto = new ZChannelOpto(ui->mode_7E1->isChecked() ? ZChannelOpto::mode_7E1 : ZChannelOpto::mode_8N1, parent());

			opto->setMeterPassword(ui->txtMeterPassword->text());

			channel = opto;
		}
		else
		{
			channel = new ZChannelDirectSerial(parent());
			channel->setBaudRate(QSerialPort::Baud115200);
		}

        channel->setPassword(ui->txtPassword->text());
        channel->setPortName(portName.toString());

        return channel;
    }
	else 
	/*if (ui->groupDialup->isChecked())
	{
		QVariant portName = ui->cmbDialupSerialPort->currentData();
		if (!portName.isValid())
		{
			showError(ui->cmbDialupSerialPort, tr("No serial port selected"));
			return NULL;
		}

		ZChannelCSD *channel = new ZChannelCSD(parent());

		channel->setBaudRate(ui->cmbBaud->currentText().toInt());
		channel->setPassword(ui->txtPassword->text());
		channel->setPortName(portName.toString());
		channel->setPhoneNumber(ui->txtPhone->text());
		
		return channel;
	}
	else */
	if (ui->groupInternet->isChecked())
	{
		ZChannelSocket *channel = new ZChannelSocket(parent());

		channel->setAddress(ui->txtIP->IP());
		channel->setPort(ui->txtPort->text().toUShort());

		channel->setPassword(ui->txtPassword->text());

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
	ui->mode_7E1->setEnabled(checked);
	ui->mode_8N1->setEnabled(checked);
}
