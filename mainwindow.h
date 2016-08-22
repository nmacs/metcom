#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTranslator>
#include "zsettingstable.h"
#include "zcommlogdialog.h"
#include "connect.h"
#include "progress.h"

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
#if 0
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
#endif

    void on_actionConnect_triggered();

    void on_actionCommunication_Log_triggered();
    void on_actionPassword_Change_triggered();
    void on_actionFirmwareUpgrade_triggered();

private:
    void updateLanguage();
    bool setupChannel();

private:
    QString m_firmware;

    Ui::MainWindow *ui;
    QSettings *settings;
    QTranslator *translator;
    ZSettingsView *m_modemSettingsTable;
    ZSettingsView *m_modemSettingsGUI;
    ZSettings *m_modemSettings;
    ZChannel *m_channel;
    Progress *m_progress;
    ZCommLogDialog *m_log;
};

#endif // MAINWINDOW_H
