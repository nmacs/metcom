#include "progress.h"
#include "ui_progress.h"

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
    if (progress < 0)
    {
        ui->progressBar->setMaximum(0);
        ui->progressBar->setValue(0);
    }
    else
    {
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(progress * ui->progressBar->maximum());
    }
    ui->lblMessage->setText(message);
}

void Progress::start()
{
    m_timer->start();
    m_cancelRequest = false;
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
