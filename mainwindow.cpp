#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "zchanneldirectserial.h"
#include "zfirmwareupgrade.h"
#include "zreadsettings.h"
#include "zwritesettings.h"
#include "zsettings.h"
#include "connect.h"
#include "firmwareupgrade.h"
#include "passwordchangedlg.h"
#include "zsettingsgui.h"
#include "zcommand.h"
#include "info.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_channel(0)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    settings = new QSettings("ZixLink", "ModemControl", this);

	m_timer = new QTimer(this);
	m_timer->setInterval(500);

	connect(m_timer, &QTimer::timeout, this, &MainWindow::on_timer);

    translator = new QTranslator(this);
    qApp->installTranslator(translator);

    ui->txtPIN1->setValidator(new QIntValidator);
    ui->txtPIN2->setValidator(new QIntValidator);

    m_modemSettings = new ZSettings(this);
    *m_modemSettings = ZSettings::defaultSettings();
    //m_modemSettings->addView(new ZSettingsTable(ui->tblSettings, this));
    m_modemSettings->addView(new ZSettingsGUI(ui, this));

	updateLanguage();

    m_progress = new Progress(this);
    m_log = new ZCommLogDialog(this);
	
	setConnectionTime(0);

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
	delete m_channel;
    delete ui;
}

void MainWindow::on_timer()
{
	setConnectionTime(m_channel != 0 ? m_channel->connectionTime() : 0);
}

void MainWindow::updateLanguage()
{
    QVariant language = settings->value("Language", QLocale::system().name());

    if (language.toString() == "ru")
    {
        ui->actionRussian->setChecked(true);
        ui->actionEnglish->setChecked(false);
    }
    else if (language.toString() == "en")
    {
        ui->actionEnglish->setChecked(true);
        ui->actionRussian->setChecked(false);
    }

    QString translation = qApp->applicationDirPath() + "/translations/app_" + language.toString();
    translator->load(translation);

	m_modemSettings->setLocked(true);
    ui->retranslateUi(this);

	setConnectionStatus((m_channel != 0) ? (m_channel->isConnected() ? tr("Connected") : tr("Disconnected")) : tr("Disconnected"));
	setConnectionTime(m_channel != 0 ? m_channel->connectionTime() : 0);

	setWindowTitle(windowTitle() + " " + QApplication::applicationVersion());
	m_modemSettings->redraw();
	m_modemSettings->setLocked(false);
}

bool MainWindow::setupChannel()
{
    Connect *dlg = new Connect(m_channel, this);
    QDialog::DialogCode code = (QDialog::DialogCode)dlg->exec();

    if (code == QDialog::Rejected)
    {
        delete dlg;
        return false;
    }

    ZChannel *channel = dlg->channel();
    if (channel != 0)
    {
        if (m_channel)
        {
            delete m_channel;
        }
        m_channel = channel;

        m_channel->setCommLog(m_log->log());
		m_channel->setProgress(m_progress);
		connect(m_channel, &ZChannel::connected, this, &MainWindow::on_channelConnected);
    }

    delete dlg;

    return true;
}

void MainWindow::setConnectionStatus(QString const& status)
{
	ui->lblConnectionStatus->setText(QString(tr("Connection Status: %1")).arg(status));
}

void MainWindow::setConnectionTime(int time)
{
	ui->lblConnectionTime->setText(QString(tr("Connection Time: %1 sec")).arg(time));
}

bool MainWindow::disconnectChannel()
{
	if (m_channel == 0)
		return true;

	setConnectionStatus(tr("Disconnecting..."));
	m_channel->disconnect();
	setConnectionTime(0);

	return true;
}

void MainWindow::on_btnConfiguration_clicked()
{
    (void)setupChannel();
}

void MainWindow::on_btnDisconnect_clicked()
{
	(void)disconnectChannel();
}

bool MainWindow::checkChannel()
{
	if (m_channel != 0)
		return true;

	return setupChannel();
}

void MainWindow::on_channelConnected(bool connected)
{
	if (connected)
	{
		setConnectionStatus(tr("Connected"));
		m_timer->start();
		ui->btnDisconnect->setEnabled(true);
		ui->btnConfiguration->setEnabled(false);
	}
	else
	{
		m_timer->stop();
		setConnectionStatus(tr("Disconnected"));
		setConnectionTime(0);
		ui->btnDisconnect->setEnabled(false);
		ui->btnConfiguration->setEnabled(true);
	}
}

void MainWindow::on_actionPassword_Change_triggered()
{    
    if (!checkChannel())
        return;

    PasswordChangeDlg *dialog = new PasswordChangeDlg(m_channel, m_progress, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionFirmwareUpgrade_triggered()
{
    if (!checkChannel())
        return;

    FirmwareUpgrade *dialog = new FirmwareUpgrade(m_channel, m_progress, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionReset_triggered()
{
    bool ret;

    if (!checkChannel())
        return;

    QString title = tr("Resetting Modem...");
    statusBar()->showMessage(title);

    ZCommand *command = new ZCommand("RST=%1\r", title, m_channel, m_progress, this);
    ret = command->run();
    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + command->errorString());
    }
    else
    {
        statusBar()->showMessage(tr("Done"));
    }
}

void MainWindow::on_actionInfo_triggered()
{
	if (!checkChannel())
		return;

	Info *dialog = new Info(m_channel, m_progress, this);
	dialog->exec();
	delete dialog;
}

void MainWindow::on_actionCommunication_Log_triggered()
{
    m_log->show();
}

void MainWindow::on_actionEnglish_triggered()
{
    settings->setValue("Language", "en");
    updateLanguage();
}

void MainWindow::on_actionRussian_triggered()
{
    settings->setValue("Language", "ru");
    updateLanguage();
}

void MainWindow::on_actionReadSettings_triggered()
{
    bool ret;

    if (!checkChannel())
        return;

    statusBar()->showMessage(tr("Reading Settings from Modem..."));

    ZReadSettings *read = new ZReadSettings(m_channel, m_progress, this);

    ret = read->run();
    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + read->errorString());
    }
    else
    {
        *m_modemSettings = read->settings();
        statusBar()->showMessage(tr("Done"));
    }
}

void MainWindow::on_actionWriteSettings_triggered()
{
    bool ret;

    if (!checkChannel())
        return;

    statusBar()->showMessage(tr("Writing Settings from Modem..."));

    ZWriteSettings *write = new ZWriteSettings(m_channel, m_progress, this);
    write->setSettings(*m_modemSettings);

    ret = write->run();
    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + write->errorString());
    }
    else
    {
        statusBar()->showMessage(tr("Done"));
    }
}

void MainWindow::on_actionLoadSettings_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                    tr("Load Settings file"),
                                                    "",
                                                    tr("ZixLink settings (*.zcfg)"));
    if (file.isEmpty())
    {
        return;
    }

    if (!m_modemSettings->load(file))
    {
        statusBar()->showMessage(tr("Fail to load settings"));
    }
}

void MainWindow::on_actionSaveSettings_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,
                                                    tr("Save Settings file"),
                                                    "",
                                                    tr("ZixLink settings (*.zcfg)"));
    if (file.isEmpty())
    {
        return;
    }

    if (!m_modemSettings->save(file))
    {
        statusBar()->showMessage(tr("Fail to save settings"));
    }
}

void MainWindow::on_actionDefaultSettings_triggered()
{
    bool ret;

    if (!checkChannel())
        return;

    QString title = tr("Writing default Modem settings...");
    statusBar()->showMessage(title);

    ZCommand *command = new ZCommand("DEF=%1\r", title, m_channel, m_progress, this);
    ret = command->run();
    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + command->errorString());
    }
    else
    {
        statusBar()->showMessage(tr("Done"));
    }
}

