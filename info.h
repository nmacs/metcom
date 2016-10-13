#pragma once

#include <QDialog>
#include <QMap>
#include "ui_info.h"
#include "zchannel.h"
#include "progress.h"

class Info : public QDialog
{
	Q_OBJECT

public:
	Info(ZChannel *channel, Progress *progress, QWidget *parent = 0);
	~Info();

private slots:
	void on_btnRefresh_clicked();
	void on_btnCopy_clicked();

private:
	void drawInfo(QStringList const& info);
	void refresh();

	Ui::frmInfo *ui;
	ZChannel *m_channel;
	Progress *m_progress;
	QMap<QString, QVariant> m_infoMap;
};
