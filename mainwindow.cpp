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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_channel(0)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    settings = new QSettings("ZixLink", "ModemControl", this);

    translator = new QTranslator(this);
    qApp->installTranslator(translator);

    updateLanguage();

    ui->txtPIN1->setValidator(new QIntValidator);
    ui->txtPIN2->setValidator(new QIntValidator);

    m_modemSettings = new ZSettings(this);
    *m_modemSettings = ZSettings::defaultSettings();
    //m_modemSettings->addView(new ZSettingsTable(ui->tblSettings, this));
    m_modemSettings->addView(new ZSettingsGUI(ui, this));

    m_progress = new Progress(this);
    m_log = new ZCommLogDialog(this);

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->retranslateUi(this);
}

bool MainWindow::setupChannel()
{
    Connect *connect = new Connect(m_channel, this);
    QDialog::DialogCode code = (QDialog::DialogCode)connect->exec();

    if (code == QDialog::Rejected)
    {
        delete connect;
        return false;
    }

    ZChannel *channel = connect->channel();
    if (channel != 0)
    {
        if (m_channel)
        {
            delete m_channel;
        }
        m_channel = channel;
        m_channel->setCommLog(m_log->log());
        m_channel->setProgress(m_progress);
    }

    delete connect;
    return true;
}

void MainWindow::on_actionConnect_triggered()
{
    (void)setupChannel();
}
void MainWindow::on_actionPassword_Change_triggered()
{    
    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

    PasswordChangeDlg *dialog = new PasswordChangeDlg(m_channel, m_progress, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionFirmwareUpgrade_triggered()
{
    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

    FirmwareUpgrade *dialog = new FirmwareUpgrade(m_channel, m_progress, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionReset_triggered()
{
    bool ret;

    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

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

    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

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

    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

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

    if (m_channel == 0 && !setupChannel())
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

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

