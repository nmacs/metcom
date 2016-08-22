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

    m_modemSettings = new ZSettings(this);
    m_modemSettings->addView(new ZSettingsTable(ui->tblSettings, this));
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

void MainWindow::on_actionConnect_triggered()
{
    Connect *connect = new Connect(m_channel, this);
    QDialog::DialogCode code = (QDialog::DialogCode)connect->exec();

    if (code == QDialog::Rejected)
    {
        delete connect;
        return;
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
}
void MainWindow::on_actionPassword_Change_triggered()
{
    if (m_channel == 0)
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
    if (m_channel == 0)
    {
        statusBar()->showMessage(tr("Communication channel was not configured"));
        return;
    }

    FirmwareUpgrade *dialog = new FirmwareUpgrade(m_channel, m_progress, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionCommunication_Log_triggered()
{
    m_log->show();
}

#if 0
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
#if 0
    if (!setupChannel())
    {
        return;
    }

    ZGuiDisabler disabler(ui);
    (void)disabler;

    statusBar()->showMessage(tr("Reading Settings from Modem..."));

    ZReadSettings read(m_channel);
    read.setPassword(ui->txtPassword->text());

    bool ret = read.connect();
    if (!ret)
    {
        statusBar()->showMessage(read.errorString());
        return;
    }

    ret = read.run();
    read.disconnect();

    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + read.errorString());
    }
    else
    {
        *m_modemSettings = read.settings();
        statusBar()->showMessage(tr("Done"));
    }
#endif
}

void MainWindow::on_actionWriteSettings_triggered()
{
#if 0
    if (!setupChannel())
    {
        return;
    }

    ZGuiDisabler disabler(ui);
    (void)disabler;

    statusBar()->showMessage(tr("Reading Settings from Modem..."));

    ZWriteSettings write(m_channel);
    write.setPassword(ui->txtPassword->text());
    write.setSettings(*m_modemSettings);

    bool ret = write.connect();
    if (!ret)
    {
        statusBar()->showMessage(write.errorString());
        return;
    }

    ret = write.run();
    write.disconnect();

    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + write.errorString());
    }
    else
    {
        statusBar()->showMessage(tr("Done"));
    }
#endif
}

void MainWindow::on_actionLoadSettings_triggered()
{
#if 0
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
#endif
}

void MainWindow::on_actionSaveSettings_triggered()
{
#if 0
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
#endif
}

bool MainWindow::setupChannel()
{
#if 0
    if (m_channel != 0)
    {
        delete m_channel;
    }

    if (ui->txtPassword->text().isEmpty())
    {
        statusBar()->showMessage(tr("Password is not entered"));
        return false;
    }

    if (ui->groupSerialPort->isChecked())
    {
        QVariant portName = ui->cmbSerialPort->currentData();
        if (!portName.isValid())
        {
            statusBar()->showMessage(tr("No serial port selected."));
            return false;
        }

        ZChannelDirectSerial *channel = new ZChannelDirectSerial(this);

        channel->setBaudRate(QSerialPort::Baud115200);
        channel->setPortName(portName.toString());
        channel->setCommLog(m_commLog);

        m_channel = channel;
    }
    else if (ui->groupInternet->isChecked())
    {
        statusBar()->showMessage(tr("Internet communication is not supported yet."));
        return false;
    }
    else
    {
        statusBar()->showMessage(tr("No communication channel selected."));
        return false;
    }
#endif

    return true;
}

void MainWindow::on_groupSerialPort_clicked()
{
    //ui->groupSerialPort->setChecked(true);
    //ui->groupInternet->setChecked(false);
}


void MainWindow::on_groupInternet_clicked()
{
    //ui->groupInternet->setChecked(true);
    //ui->groupSerialPort->setChecked(false);
}
#endif
