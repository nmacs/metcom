#ifndef ZCOMMLOGDIALOG_H
#define ZCOMMLOGDIALOG_H

#include <QDialog>
#include "zcommlog.h"

namespace Ui {
class ZCommLogDialog;
}

class ZCommLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCommLogDialog(QWidget *parent = 0);
    ~ZCommLogDialog();

    ZCommLog* log() const { return m_log; }

private slots:
    void on_pushButton_clicked();

private:
    Ui::ZCommLogDialog *ui;

    ZCommLog *m_log;
};

#endif // ZCOMMLOGDIALOG_H
