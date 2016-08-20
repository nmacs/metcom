#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSerialPort/QtSerialPort"
#include <QFileDialog>
#include "zchanneldirectserial.h"
#include "zfirmwareupgrade.h"
#include "zreadsettings.h"
#include "zwritesettings.h"
#include "zsettings.h"

class ZGuiDisabler
{
public:
    ZGuiDisabler(Ui::MainWindow *ui)
    {
        disable(ui->actionLoadSettings);
        disable(ui->actionSaveSettings);
        disable(ui->actionReadSettings);
        disable(ui->actionWriteSettings);
    }

    ~ZGuiDisabler()
    {
        {
            QList<QWidget*>::iterator iter;
            for (iter = m_disabledWidgets.begin(); iter != m_disabledWidgets.end(); ++iter)
            {
                (*iter)->setEnabled(true);
            }
        }

        {
            QList<QAction*>::iterator iter;
            for (iter = m_disabledActions.begin(); iter != m_disabledActions.end(); ++iter)
            {
                (*iter)->setDisabled(false);
            }
        }
    }

private:
    void disable(QWidget *widget)
    {
        widget->setEnabled(false);
        m_disabledWidgets.append(widget);
    }

    void disable(QAction *action)
    {
        action->setDisabled(true);
        m_disabledActions.append(action);
    }

    Ui::MainWindow *m_ui;
    QList<QWidget*> m_disabledWidgets;
    QList<QAction*> m_disabledActions;
};

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

#if 0
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);

    updateLanguage();
    statusBar()->showMessage(tr("Ready"));

    m_firmware = settings->value("LastFirmwareFile", "").toString();
    ui->txtFirmwareFile->setText(m_firmware);

    m_modemSettingsView = new ZSettingsTable(ui->tblSettings, this);
    m_modemSettings = new ZSettings(this);
    m_modemSettings->setView(m_modemSettingsView);

    m_commLog = new ZCommLog(ui->txtCommLog, this);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnUpgrade_clicked()
{
#if 0
    if (!setupChannel())
    {
        return;
    }

    ZGuiDisabler disabler(ui);
    (void)disabler;

    statusBar()->showMessage(tr("Upgrade Firmware..."));

    ZFirmwareUpgrade upgrade(m_channel);
    upgrade.setPassword(ui->txtPassword->text());
    upgrade.setResetConfiguration(ui->chkResetSettings->checkState() == Qt::Checked);
    upgrade.setFirmwareFile(m_firmware);
    upgrade.setProgress(ui->progressBar);

    bool ret = upgrade.connect();
    if (!ret)
    {
        statusBar()->showMessage(upgrade.errorString());
        return;
    }

    ret = upgrade.run();
    upgrade.disconnect();

    if (!ret)
    {
        statusBar()->showMessage(tr("Error: ") + upgrade.errorString());
    }
    else
    {
        statusBar()->showMessage(tr("Done"));
    }
#endif
}

void MainWindow::on_btnSelectFirmware_clicked()
{
#if 0
    QString firmware = QFileDialog::getOpenFileName(this,
                                                    tr("Select Firmware file"),
                                                    "",
                                                    tr("ZixLink firmware (*.zlk)"));

    ui->txtFirmwareFile->setText(firmware);
    m_firmware = firmware;
    settings->setValue("LastFirmwareFile", m_firmware);
#endif
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

void MainWindow::on_timeout()
{
#if 0
    QList<QSerialPortInfo>::iterator i;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int c = 0; c < ui->cmbSerialPort->count(); c++)
    {
        ui->cmbSerialPort->setItemData(c, "");
    }

    for (i = ports.begin(); i != ports.end(); i++)
    {
        QString text = i->portName() + ": " + i->description();
        QString data = i->portName();

        int ind = ui->cmbSerialPort->findText(text);
        if (ind < 0)
            ui->cmbSerialPort->addItem(text, data);
        else
            ui->cmbSerialPort->setItemData(ind, data);
    }

    for (int c = 0; c < ui->cmbSerialPort->count();)
    {
        if (ui->cmbSerialPort->itemData(c).toString() == "")
            ui->cmbSerialPort->removeItem(c);
        else
            c++;
    }
#endif
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
