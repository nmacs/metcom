#include "info.h"
#include "zcommand.h"
#include <QClipboard>

Info::Info(ZChannel *channel, Progress *progress, QWidget *parent)
	: QDialog(parent),
	ui(new Ui::frmInfo),
	m_channel(channel),
	m_progress(progress)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	ui->lblStatus->setText("");
	ui->txtInfo->setPlainText("");

#if 0
	m_infoMap.insert("HARD", tr("Hardware ID"));
	m_infoMap.insert("SOFT", tr("Software ID"));
	m_infoMap.insert("TYPE", tr("Device Model"));
	m_infoMap.insert("CELL", tr("Network Technology"));
	m_infoMap.insert("CGMM", tr("Module Type"));
	m_infoMap.insert("CGMR", tr("Module Software ID"));
	m_infoMap.insert("IMEI", tr("IMEI"));
	m_infoMap.insert("IMSI", tr("IMSI"));
	m_infoMap.insert("CCID", tr("CCID"));
	m_infoMap.insert("OPER", tr("Operator"));
	m_infoMap.insert("SYGN", tr("Signal Quality"));
	m_infoMap.insert("TIME", tr("Date/Time"));
#endif

	refresh();
}

Info::~Info()
{
	delete ui;
}

void Info::on_btnRefresh_clicked()
{
	refresh();
}

void Info::on_btnCopy_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(ui->txtInfo->toPlainText());
}

void Info::drawInfo(QStringList const& info)
{
	QStringListIterator iter(info);
	QString text;

	while (iter.hasNext())
	{
		QString const& item = iter.next();
		QStringList nameValue = item.trimmed().split(QChar(':'));
		if (nameValue.length() >= 2)
		{
			QString name = nameValue.at(0);
			QString value = nameValue.at(1);
			QString line = QString().sprintf("%-23s%s\r\n", m_infoMap.value(name, name).toString().toUtf8().constData(), value.toUtf8().constData());

			text.append(line);
		}
	}

	ui->txtInfo->setPlainText(text);
}

void Info::refresh()
{
#if 1
	bool ret;

	ZCommand *command = new ZCommand("INFO=%1\r", "Info", m_channel, m_progress, this);
	command->setHaveResponse(true);

	ret = command->run();
	if (!ret)
	{

		ui->lblStatus->setText(tr("Error: ") + command->errorString());
	}
	else
	{
		QStringList const& info = command->response();
		drawInfo(info);
		ui->lblStatus->setText(tr("Done"));
	}
#else
	QStringList info;
	info.append("Device name: Metronika 300 AS3500 ETH");
	info.append("Hardware ID: 01.03.02.11");
	info.append("Firmware ID: 00.0001.01");
	info.append("Local IP: 192.168.1.108");
	info.append("Default GateWay: 192.168.1.1");
	info.append("Net Mask: 255.255.255.0");
	info.append("Primary DNS: 192.168.1.1");
	info.append("Secodary DNS: 62.148.128.1");	
	drawInfo(info);
	ui->lblStatus->setText(tr("Done"));
#endif
}