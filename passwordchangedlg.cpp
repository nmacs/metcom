#include "passwordchangedlg.h"
#include "ui_passwordchangedlg.h"
#include "zpasswordchange.h"

PasswordChangeDlg::PasswordChangeDlg(ZChannel *channel, Progress *progress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordChangeDlg),
    m_channel(channel),
    m_progress(progress)
{
    ui->setupUi(this);

    ui->lblStatus->setText("");
}

PasswordChangeDlg::~PasswordChangeDlg()
{
    delete ui;
}

void PasswordChangeDlg::on_pushButton_clicked()
{
    bool res;

    if (ui->txtPassword->text() != ui->txtPassword2->text())
    {
        ui->lblStatus->setText(tr("Passwords are not equal"));
        return;
    }

    ui->lblStatus->setText(tr("Changing Password..."));

    ZPasswordChange *proto = new ZPasswordChange(m_channel, m_progress, this);

    proto->setNewPassword(ui->txtPassword->text());

    res = proto->run();
    if (res)
    {
        ui->lblStatus->setText(tr("Done"));
    }
    else
    {
        ui->lblStatus->setText(tr("Error: ") + proto->errorString());
    }
}
