#include "zcommlogdialog.h"
#include "ui_zcommlogdialog.h"

ZCommLogDialog::ZCommLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZCommLogDialog)
{
    ui->setupUi(this);
    m_log = new ZCommLog(ui->textBrowser, this);
}

ZCommLogDialog::~ZCommLogDialog()
{
    delete ui;
}

void ZCommLogDialog::on_pushButton_clicked()
{
    ui->textBrowser->clear();
}
