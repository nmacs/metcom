#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Progress;
}

class Progress : public QDialog
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

    void setProgress(double progress, QString const& message);
    void start();
    void end();

    bool cancelRequest() const { return m_cancelRequest; }

private slots:
    void on_btnCancel_clicked();
    void on_timeout();

private:
    Ui::Progress *ui;

    bool m_cancelRequest;
    QTimer *m_timer;
};

#endif // PROGRESS_H
