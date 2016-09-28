#include "progress.h"
#include "ui_progress.h"
#include <QDebug>

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress),
    m_cancelRequest(false)
{
    ui->setupUi(this);

    ui->lblMessage->setText("");

    ui->progressBar->setMaximum(1000);
    ui->progressBar->setMinimum(0);

    setModal(true);
	setWindowModality(Qt::WindowModal);

    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &Progress::on_timeout);
}

Progress::~Progress()
{
    delete ui;
}

void Progress::setProgress(double progress, const QString &message)
{
    qDebug() << "Report progress " << progress;
    if (progress < 0)
    {
        ui->progressBar->setMaximum(0);
        ui->progressBar->setValue(0);
    }
    else
    {
        if (ui->progressBar->maximum() == 0)
        {
            ui->progressBar->setMaximum(100);
        }
        int value = progress * ui->progressBar->maximum();
        qDebug() << "Report progress (value) " << value;
        ui->progressBar->setValue(value);
    }

    if (!message.isEmpty())
    {
        ui->lblMessage->setText(message);
    }
}

void Progress::start()
{
    ui->progressBar->setMaximum(100);
    m_timer->start();
    m_cancelRequest = false;
    ui->lblMessage->clear();
}

void Progress::end()
{
    m_cancelRequest = false;
    m_timer->stop();
    hide();
}

void Progress::on_timeout()
{
    show();
}

void Progress::on_btnCancel_clicked()
{
    m_cancelRequest = true;
}
