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
	ui->lblStatus->setText("");
	ui->txtInfo->setPlainText("");

	m_infoMap.insert("HARD", tr("Hardware ID"));
	m_infoMap.insert("SOFT", tr("Software ID"));
	m_infoMap.insert("CELL", tr("Network Technology"));
	m_infoMap.insert("CGMM", tr("Module Software ID"));
	m_infoMap.insert("IMEI", tr("IMEI"));
	m_infoMap.insert("IMSI", tr("IMSI"));
	m_infoMap.insert("CCID", tr("CCID"));
	m_infoMap.insert("OPER", tr("Operator"));
	m_infoMap.insert("SYGN", tr("Signal Quality"));
	m_infoMap.insert("TIME", tr("Date/Time"));

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

		QString name = item.left(4);
		QString value = item.right(item.length() - 5);

		QString line = QString().sprintf("%-25s%s\r\n", m_infoMap.value(name, name).toString().toLatin1().constData(), value.toLatin1().constData());
		text.append(line);
	}

	ui->txtInfo->setPlainText(text);
}

void Info::refresh()
{
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
}