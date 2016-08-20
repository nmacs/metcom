#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTranslator>
#include "zsettingstable.h"
#include "zcommlog.h"

class ZChannel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnUpgrade_clicked();
    void on_btnSelectFirmware_clicked();

    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();
    void on_actionReadSettings_triggered();
    void on_actionWriteSettings_triggered();
    void on_actionLoadSettings_triggered();
    void on_actionSaveSettings_triggered();

    void on_groupSerialPort_clicked();
    void on_groupInternet_clicked();

    void on_timeout();

private:
    void updateLanguage();
    bool setupChannel();

private:
    QString m_firmware;

    Ui::MainWindow *ui;
    QTimer *timer;
    QSettings *settings;
    QTranslator *translator;
    ZSettingsView *m_modemSettingsView;
    ZSettings *m_modemSettings;
    ZCommLog *m_commLog;
    ZChannel *m_channel;
};

#endif // MAINWINDOW_H
