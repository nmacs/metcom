#ifndef PASSWORDCHANGEDLG_H
#define PASSWORDCHANGEDLG_H

#include <QDialog>
#include "zchannel.h"
#include "progress.h"

namespace Ui {
class PasswordChangeDlg;
}

class PasswordChangeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordChangeDlg(ZChannel *channel, Progress *progress, QWidget *parent = 0);
    ~PasswordChangeDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PasswordChangeDlg *ui;

    ZChannel *m_channel;
    Progress *m_progress;
};

#endif // PASSWORDCHANGEDLG_H
