#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTranslator>
#include <QTimer>
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
    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();

    void on_actionReadSettings_triggered();
    void on_actionWriteSettings_triggered();
    void on_actionLoadSettings_triggered();
    void on_actionSaveSettings_triggered();
    void on_actionDefaultSettings_triggered();

    void on_btnConfiguration_clicked();
	void on_channelConnected(bool connected);
	void on_btnDisconnect_clicked();

    void on_actionCommunication_Log_triggered();
    void on_actionPassword_Change_triggered();
    void on_actionFirmwareUpgrade_triggered();
    void on_actionReset_triggered();

	void on_timer();

private:
    void updateLanguage();

    bool setupChannel();
	bool checkChannel();
	bool disconnectChannel();

	void setConnectionStatus(QString const& status);
	void setConnectionTime(int time);

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
	QTimer *m_timer;
};

#endif // MAINWINDOW_H
