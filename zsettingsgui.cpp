#include "zsettingsgui.h"
#include "zsettings.h"
#include "ui_mainwindow.h"
#include <QRadioButton>

ZSettingsGUI::ZSettingsGUI(Ui::MainWindow* gui, QObject *parent) :
    ZSettingsView(parent),
    m_gui(gui)
{
    /*
     * Mode
     */
    connect(m_gui->radioModeModem,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_radioModeModem_toggled);

    connect(m_gui->APHN,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_APHN_toggled);

    connect(m_gui->radioModeClient,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_radioModeClient_toggled);

    connect(m_gui->radioModeServer,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_radioModeServer_toggled);

    connect(m_gui->GCSD,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_GCSD_valueChanged(int)));

    connect(m_gui->IPC1,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_IPC1_textChanged);

    connect(m_gui->IPC2,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_IPC2_textChanged);

    connect(m_gui->PTC1,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PTC1_valueChanged(int)));

    connect(m_gui->PTC2,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PTC2_valueChanged(int)));

    connect(m_gui->EIP1,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_EIP1_textChanged);

    connect(m_gui->EIP2,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_EIP2_textChanged);

    connect(m_gui->EIP3,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_EIP3_textChanged);

    connect(m_gui->EIP4,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_EIP4_textChanged);

    connect(m_gui->PTSR,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PTSR_valueChanged(int)));

    connect(m_gui->MPSZ,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_MPSZ_valueChanged(int)));

    connect(m_gui->TRDT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_TRDT_valueChanged(int)));

    connect(m_gui->SITT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_SITT_valueChanged(int)));

    /*
     * SIM
     */
    connect(m_gui->radioSIM1,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_radioSIM1_toggled);

    connect(m_gui->radioSIM2,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_radioSIM2_toggled);

    connect(m_gui->chkSIM1Enable,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_chkSIM1Enable_toggled);

    connect(m_gui->chkSIM2Enable,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_chkSIM2Enable_toggled);

    connect(m_gui->txtSIMSwapInterval,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtSIMSwapInterval_textChanged);

    connect(m_gui->txtRMNS,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtRMNS_textChanged);

    connect(m_gui->txtAPN1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtAPN1_textChanged);

    connect(m_gui->txtAPN2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtAPN2_textChanged);

    connect(m_gui->txtLOG1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtLOG1_textChanged);

    connect(m_gui->txtLOG2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtLOG2_textChanged);

    connect(m_gui->txtPSW1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtPSW1_textChanged);

    connect(m_gui->txtPSW2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtPSW2_textChanged);

    connect(m_gui->txtPIN1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtPIN1_textChanged);

    connect(m_gui->txtPIN2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_txtPIN2_textChanged);

    connect(m_gui->NET1,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_NET1_currentIndexChanged(int)));

    connect(m_gui->NET2,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_NET2_currentIndexChanged(int)));

    connect(m_gui->chkROA1,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_chkROA1_toggled);

    connect(m_gui->chkROA2,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_chkROA2_toggled);

    /*
     * PING
     */
    connect(m_gui->ESCH,
            &QGroupBox::toggled,
            this,
            &ZSettingsGUI::on_ESCH_toggled);

    connect(m_gui->SCH1_IP,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_SCH1_IP_textChanged);

    connect(m_gui->SCH1_PORT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_SCH1_PORT_valueChanged(int)));

    connect(m_gui->SCH2_IP,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_SCH2_IP_textChanged);

    connect(m_gui->SCH2_PORT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_SCH2_PORT_valueChanged(int)));

    connect(m_gui->EPNG1,
            &QGroupBox::toggled,
            this,
            &ZSettingsGUI::on_EPNG1_toggled);

    connect(m_gui->IPP1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_IPP1_textChanged);

    connect(m_gui->IPP2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_IPP2_textChanged);

    connect(m_gui->EDNS,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_EDNS_toggled);

    connect(m_gui->PPNG,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PPNG_valueChanged(int)));

    connect(m_gui->MPRT_RS232,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_MPRT_RS232_toggled);

    connect(m_gui->MPRT_RS485,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_MPRT_RS485_toggled);

    connect(m_gui->MAPT,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_MAPT_currentIndexChanged(int)));

    connect(m_gui->BDRT,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_BDRT_currentIndexChanged(int)));

    connect(m_gui->BITS,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_BITS_currentIndexChanged(int)));

    connect(m_gui->PRTY,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_PRTY_currentIndexChanged(int)));

    connect(m_gui->STOP,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_STOP_currentIndexChanged(int)));

    connect(m_gui->RSIT,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_RSIT_toggled);

    connect(m_gui->RSHR,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_RSHR_valueChanged(int)));

    connect(m_gui->RSDT,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_RSDT_toggled);

    connect(m_gui->DTHR,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_DTHR_valueChanged(int)));

    connect(m_gui->DTMN,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_DTMN_valueChanged(int)));

    connect(m_gui->GPHR,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_GPHR_valueChanged(int)));
}

void ZSettingsGUI::on_radioSIM1_toggled(bool checked)
{
    if (checked)
    {
        emitUpdated("TSIM", 0);
    }
}

void ZSettingsGUI::on_radioSIM2_toggled(bool checked)
{
    if (checked)
    {
        emitUpdated("TSIM", 1);
    }
}

void ZSettingsGUI::on_chkSIM1Enable_toggled(bool checked)
{
    if (!checked)
    {
        m_gui->radioSIM1->setChecked(false);
        m_gui->radioSIM2->setChecked(true);
        if (!m_gui->chkSIM2Enable->isChecked())
        {
            m_gui->chkSIM2Enable->toggle();
        }
    }

    m_gui->groupSIM1->setEnabled(checked);
    m_gui->radioSIM1->setEnabled(checked);

    emitUpdated("OFF1", checked ? 1 : 0);
}

void ZSettingsGUI::on_chkSIM2Enable_toggled(bool checked)
{
    if (!checked)
    {
        m_gui->radioSIM1->setChecked(true);
        m_gui->radioSIM2->setChecked(false);
        if (!m_gui->chkSIM1Enable->isChecked())
        {
            m_gui->chkSIM1Enable->toggle();
        }
    }

    m_gui->groupSIM2->setEnabled(checked);
    m_gui->radioSIM2->setEnabled(checked);

    emitUpdated("OFF2", checked ? 1 : 0);
}

void ZSettingsGUI::on_txtSIMSwapInterval_textChanged(QString const& text)
{
    emitUpdated("SWAP", text.toInt());
}

void ZSettingsGUI::on_txtRMNS_textChanged(QString const& text)
{
    emitUpdated("RMNS", text.toInt());
}

void ZSettingsGUI::on_txtAPN1_textChanged(QString const& text)
{
    emitUpdated("APN1", text);
}

void ZSettingsGUI::on_txtAPN2_textChanged(QString const& text)
{
    emitUpdated("APN2", text);
}

void ZSettingsGUI::on_txtLOG1_textChanged(QString const& text)
{
    emitUpdated("LOG1", text);
}

void ZSettingsGUI::on_txtLOG2_textChanged(QString const& text)
{
    emitUpdated("LOG2", text);
}

void ZSettingsGUI::on_txtPSW1_textChanged(QString const& text)
{
    emitUpdated("PSW1", text);
}

void ZSettingsGUI::on_txtPSW2_textChanged(QString const& text)
{
    emitUpdated("PSW2", text);
}

void ZSettingsGUI::on_txtPIN1_textChanged(QString const& text)
{
    emitUpdated("PIN1", text);
}

void ZSettingsGUI::on_txtPIN2_textChanged(QString const& text)
{
    emitUpdated("PIN2", text);
}

void ZSettingsGUI::on_NET1_currentIndexChanged(int index)
{
   emitUpdated("NET1", index);
}

void ZSettingsGUI::on_NET2_currentIndexChanged(int index)
{
   emitUpdated("NET2", index);
}

void ZSettingsGUI::on_chkROA1_toggled(bool checked)
{
    emitUpdated("ROA1", checked ? 1 : 0);
}

void ZSettingsGUI::on_chkROA2_toggled(bool checked)
{
    emitUpdated("ROA2", checked ? 1 : 0);
}

void ZSettingsGUI::on_radioModeModem_toggled(bool checked)
{
    m_gui->groupModeModem->setEnabled(checked);
    emitUpdated("MODE", 0);
}

void ZSettingsGUI::on_radioModeClient_toggled(bool checked)
{
    m_gui->groupModeClient->setEnabled(checked);
    m_gui->groupModeServerClient->setEnabled(
                m_gui->radioModeClient->isChecked() |
                m_gui->radioModeServer->isChecked());
    emitUpdated("MODE", 1);
}

void ZSettingsGUI::on_radioModeServer_toggled(bool checked)
{
    m_gui->groupModeServer->setEnabled(checked);
    m_gui->groupModeServerClient->setEnabled(
                m_gui->radioModeClient->isChecked() |
                m_gui->radioModeServer->isChecked());
    emitUpdated("MODE", 2);
}

void ZSettingsGUI::on_GCSD_valueChanged(int value)
{
    emitUpdated("GCSD", value);
}

void ZSettingsGUI::on_APHN_toggled(bool checked)
{
    m_gui->GCSD->setEnabled(!checked);
    m_gui->lblModeModemPhoneGroup->setEnabled(!checked);
    emitUpdated("APHN", checked ? 1 : 0);
}

void ZSettingsGUI::on_IPC1_textChanged(QString const& text)
{
    emitUpdated("IPC1", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_IPC2_textChanged(QString const& text)
{
    emitUpdated("IPC2", text != "0.0.0.0" ? text : "");;
}

void ZSettingsGUI::on_PTC1_valueChanged(int value)
{
    emitUpdated("PTC1", value);
}

void ZSettingsGUI::on_PTC2_valueChanged(int value)
{
    emitUpdated("PTC2", value);
}

void ZSettingsGUI::on_EIP1_textChanged(QString const& text)
{
    emitUpdated("EIP1", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_EIP2_textChanged(QString const& text)
{
    emitUpdated("EIP2", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_EIP3_textChanged(QString const& text)
{
    emitUpdated("EIP3", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_EIP4_textChanged(QString const& text)
{
    emitUpdated("EIP4", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_PTSR_valueChanged(int value)
{
    emitUpdated("PTSR", value);
}

void ZSettingsGUI::on_MPSZ_valueChanged(int value)
{
    emitUpdated("MPSZ", value);
}

void ZSettingsGUI::on_TRDT_valueChanged(int value)
{
    emitUpdated("TRDT", value);
}

void ZSettingsGUI::on_SITT_valueChanged(int value)
{
    emitUpdated("SITT", value);
}

void ZSettingsGUI::on_ESCH_toggled(bool checked)
{
    emitUpdated("ESCH", checked ? 1 : 0);
}

void ZSettingsGUI::on_SCH1_IP_textChanged(QString const& text)
{
    emitUpdated("SCH1", text + ":" + m_gui->SCH1_PORT->text());
}

void ZSettingsGUI::on_SCH1_PORT_valueChanged(int value)
{
    emitUpdated("SCH1", m_gui->SCH1_IP->text() + ":" + QString::number(value));
}

void ZSettingsGUI::on_SCH2_IP_textChanged(QString const& text)
{
    emitUpdated("SCH2", text + ":" + m_gui->SCH2_PORT->text());
}

void ZSettingsGUI::on_SCH2_PORT_valueChanged(int value)
{
    emitUpdated("SCH2", m_gui->SCH2_IP->text() + ":" + QString::number(value));
}

void ZSettingsGUI::on_EPNG1_toggled(bool checked)
{
    emitUpdated("EPNG", checked ? 1 : 0);
}

void ZSettingsGUI::on_IPP1_textChanged(QString const& text)
{
    emitUpdated("IPP1", text);
}

void ZSettingsGUI::on_IPP2_textChanged(QString const& text)
{
    emitUpdated("IPP2", text);
}

void ZSettingsGUI::on_EDNS_toggled(bool checked)
{
    emitUpdated("EDNS", checked ? 1 : 0);
}

void ZSettingsGUI::on_PPNG_valueChanged(int value)
{
    emitUpdated("SCH2", value);
}

void ZSettingsGUI::on_MPRT_RS232_toggled(bool checked)
{
    if (checked)
        emitUpdated("MPRT", 0);
}

void ZSettingsGUI::on_MPRT_RS485_toggled(bool checked)
{
    if (checked)
        emitUpdated("MPRT", 1);
}

void ZSettingsGUI::on_MAPT_currentIndexChanged(int index)
{
    emitUpdated("MAPT", index);
}

void ZSettingsGUI::on_BDRT_currentIndexChanged(int index)
{
    emitUpdated("BDRT", index);
}

void ZSettingsGUI::on_BITS_currentIndexChanged(int index)
{
    emitUpdated("BITS", index);
}

void ZSettingsGUI::on_PRTY_currentIndexChanged(int index)
{
    emitUpdated("PRTY", index);
}

void ZSettingsGUI::on_STOP_currentIndexChanged(int index)
{
    emitUpdated("STOP", index);
}

void ZSettingsGUI::on_RSIT_toggled(bool checked)
{
    m_gui->lblRSHR->setEnabled(checked);
    m_gui->lblRSHR_2->setEnabled(checked);
    m_gui->RSHR->setEnabled(checked);

    emitUpdated("RSIT", checked ? 1 : 0);
}

void ZSettingsGUI::on_RSHR_valueChanged(int value)
{
    emitUpdated("RSHR", value);
}

void ZSettingsGUI::on_RSDT_toggled(bool checked)
{
    m_gui->lblDTHR->setEnabled(checked);
    m_gui->DTHR->setEnabled(checked);
    m_gui->DTMN->setEnabled(checked);

    emitUpdated("RSDT", checked ? 1 : 0);
}

void ZSettingsGUI::on_DTHR_valueChanged(int value)
{
    emitUpdated("DTHR", value);
}

void ZSettingsGUI::on_DTMN_valueChanged(int value)
{
    emitUpdated("DTMN", value);
}

void ZSettingsGUI::on_GPHR_valueChanged(int value)
{
    emitUpdated("GPHR", value);
}

void ZSettingsGUI::draw(ZSettings *settings)
{
    int TSIM = settings->value("TSIM", 0).toInt();
    if (TSIM == 0)
    {
        m_gui->radioSIM1->setChecked(true);
    }
    else
    {
        m_gui->radioSIM2->setChecked(true);
    }

    int SWAP = settings->value("SWAP", 10).toInt();
    m_gui->txtSIMSwapInterval->setText(QString::number(SWAP));

    int RMNS = settings->value("RMNS", 10).toInt();
    m_gui->txtRMNS->setText(QString::number(RMNS));

    QString APN1 = settings->value("APN1", "public.mc").toString();
    m_gui->txtAPN1->setText(APN1);

    QString APN2 = settings->value("APN2", "").toString();
    m_gui->txtAPN2->setText(APN2);

    QString LOG1 = settings->value("LOG1", "gdata").toString();
    m_gui->txtLOG1->setText(LOG1);

    QString LOG2 = settings->value("LOG2", "").toString();
    m_gui->txtLOG2->setText(LOG2);

    QString PSW1 = settings->value("PSW1", "gdata").toString();
    m_gui->txtPSW1->setText(PSW1);

    QString PSW2 = settings->value("PSW2", "").toString();
    m_gui->txtPSW2->setText(PSW2);

    QString PIN1 = settings->value("PIN1", "").toString();
    m_gui->txtPIN1->setText(PIN1);

    QString PIN2 = settings->value("PIN2", "").toString();
    m_gui->txtPIN2->setText(PIN2);

    int OFF1 = settings->value("OFF1", 1).toInt();
    m_gui->chkSIM1Enable->setChecked(OFF1 != 0 ? true : false);

    int OFF2 = settings->value("OFF2", 0).toInt();
    m_gui->chkSIM2Enable->setChecked(OFF2 != 0 ? true : false);

    int ROA1 = settings->value("ROA1", 1).toInt();
    m_gui->chkROA1->setChecked(ROA1 != 0 ? true : false);

    int ROA2 = settings->value("ROA2", 1).toInt();
    m_gui->chkROA2->setChecked(ROA2 != 0 ? true : false);

    int NET1 = settings->value("NET1", 0).toInt();
    m_gui->NET1->setCurrentIndex(NET1 > 0 && NET1 <= 2 ? NET1 : 0);

    int NET2 = settings->value("NET2", 0).toInt();
    m_gui->NET2->setCurrentIndex(NET2 > 0 && NET2 <= 2 ? NET2 : 0);

    int MODE = settings->value("MODE", 0).toInt();
    switch (MODE)
    {
    case 2:
        m_gui->radioModeServer->setChecked(true);
        break;
    case 1:
        m_gui->radioModeClient->setChecked(true);
        break;
    case 0:
    default:
        m_gui->radioModeModem->setChecked(true);
        break;
    }

    int APHN = settings->value("APHN", 1).toInt();
    m_gui->APHN->setChecked(APHN != 0 ? true : false);

    int GCSD = settings->value("GCSD", 0).toInt();
    m_gui->GCSD->setValue(GCSD);

    QString IPC1 = settings->value("IPC1", "0.0.0.0").toString();
    m_gui->IPC1->setIP(IPC1);

    QString IPC2 = settings->value("IPC2", "0.0.0.0").toString();
    m_gui->IPC2->setIP(IPC2);

    int PTC1 = settings->value("PTC1", 1).toInt();
    m_gui->PTC1->setValue(PTC1);

    int PTC2 = settings->value("PTC2", 1).toInt();
    m_gui->PTC2->setValue(PTC2);

    QString EIP1 = settings->value("EIP1", "0.0.0.0").toString();
    m_gui->EIP1->setIP(EIP1);

    QString EIP2 = settings->value("EIP2", "0.0.0.0").toString();
    m_gui->EIP2->setIP(EIP2);

    QString EIP3 = settings->value("EIP3", "0.0.0.0").toString();
    m_gui->EIP3->setIP(EIP3);

    QString EIP4 = settings->value("EIP4", "0.0.0.0").toString();
    m_gui->EIP4->setIP(EIP4);

    int PTSR = settings->value("PTSR", 9000).toInt();
    m_gui->PTSR->setValue(PTSR);

    int MPSZ = settings->value("MPSZ", 1024).toInt();
    m_gui->MPSZ->setValue(MPSZ);

    int TRDT = settings->value("TRDT", 300).toInt();
    m_gui->TRDT->setValue(TRDT);

    int SITT = settings->value("SITT", 600).toInt();
    m_gui->SITT->setValue(SITT);

    int ESCH = settings->value("ESCH", 0).toInt();
    m_gui->ESCH->setChecked(ESCH != 0 ? true : false);

    QString SCH1 = settings->value("SCH1", "yandex.ru:8080").toString();
    QStringList SCH1_items = SCH1.split(':');
    m_gui->SCH1_IP->setText(SCH1_items.length() > 0 ? SCH1_items[0] : "yandex.ru");
    m_gui->SCH1_PORT->setValue(SCH1_items.length() > 1 ? SCH1_items[1].toInt() : 8080);

    QString SCH2 = settings->value("SCH2", "8.8.8.8:8080").toString();
    QStringList SCH2_items = SCH2.split(':');
    m_gui->SCH2_IP->setText(SCH2_items.length() > 0 ? SCH2_items[0] : "8.8.8.8");
    m_gui->SCH2_PORT->setValue(SCH2_items.length() > 1 ? SCH2_items[1].toInt() : 8080);

    int EPNG = settings->value("EPNG", 0).toInt();
    m_gui->EPNG1->setChecked(EPNG != 0 ? true : false);

    QString IPP1 = settings->value("IPP1", "yandex.ru").toString();
    m_gui->IPP1->setText(IPP1);

    QString IPP2 = settings->value("IPP2", "google.com").toString();
    m_gui->IPP2->setText(IPP2);

    int EDNS = settings->value("EDNS", 1).toInt();
    m_gui->EDNS->setChecked(EDNS != 0 ? true : false);

    int PPNG = settings->value("PPNG", 10).toInt();
    m_gui->PPNG->setValue(PPNG);

    int MPRT = settings->value("MPRT", 0).toInt();
    if (MPRT != 0)
        m_gui->MPRT_RS485->setChecked(true);
    else
        m_gui->MPRT_RS232->setChecked(true);

    int MAPT = settings->value("MAPT", 1).toInt();
    m_gui->MAPT->setCurrentIndex(MAPT);

    int BDRT = settings->value("BDRT", 4).toInt();
    m_gui->BDRT->setCurrentIndex(BDRT);

    int BITS = settings->value("BITS", 3).toInt();
    m_gui->BITS->setCurrentIndex(BITS);

    int PRTY = settings->value("PRTY", 4).toInt();
    m_gui->PRTY->setCurrentIndex(PRTY);

    int STOP = settings->value("STOP", 0).toInt();
    m_gui->STOP->setCurrentIndex(STOP);

    int RSIT = settings->value("RSIT", 1).toInt();
    m_gui->RSIT->setChecked(RSIT != 0 ? true : false);

    int RSHR = settings->value("RSHR", 24).toInt();
    m_gui->RSHR->setValue(RSHR);

    int RSDT = settings->value("RSDT", 1).toInt();
    m_gui->RSDT->setChecked(RSDT != 0 ? true : false);

    int DTHR = settings->value("DTHT", 16).toInt();
    m_gui->DTHR->setValue(DTHR);

    int DTMN = settings->value("DTMN", 30).toInt();
    m_gui->DTMN->setValue(DTMN);

    int GPHR = settings->value("GPHR", 2).toInt();
    m_gui->GPHR->setValue(GPHR);
}
