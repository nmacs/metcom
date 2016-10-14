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
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_IPC1_textChanged);

    connect(m_gui->IPC2,
            &QLineEdit::textChanged,
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
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_txtSIMSwapInterval_valueChanged(int)));

    connect(m_gui->txtRMNS,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_txtRMNS_valueChanged(int)));

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

	/*
	* Reset/Time
	*/

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

	connect(m_gui->NTPE,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_NTPE_toggeld(bool)));

	connect(m_gui->NTPZ,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_NTPZ_valueChanged(int)));

	connect(m_gui->NTP1,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP1_textChanged(const QString&)));

	connect(m_gui->NTP1_P,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_NTP1_P_valueChanged(int)));

	connect(m_gui->NTP2,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP2_textChanged(const QString&)));

	connect(m_gui->NTP2_P,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_NTP2_P_valueChanged(int)));

	connect(m_gui->NTP3,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP3_textChanged(const QString&)));

	connect(m_gui->NTP3_P,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_NTP3_P_valueChanged(int)));

    /*
     * Phone Book
     */
    connect(m_gui->phoneBook,
            &PhoneBook::phoneChanged,
            this,
            &ZSettingsGUI::on_phoneBook_phoneChanged);

    connect(m_gui->phoneBook,
            &PhoneBook::phoneGroupChanged,
            this,
            &ZSettingsGUI::on_phoneBook_phoneGroupChanged);

	/*
	* Access
	*/
	connect(m_gui->DBEN,
		    SIGNAL(toggled(bool)),
		    this,
		    SLOT(on_DBEN_toggled(bool)));

	connect(m_gui->DBMD_C,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_DBMD_C_toggled(bool)));

	connect(m_gui->DBMD_S,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_DBMD_S_toggled(bool)));

	connect(m_gui->DBIP,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_DBIP_textChanged(const QSTring&)));

	connect(m_gui->DBPC,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_DBPC_valueChanged(int)));

	connect(m_gui->DBPS,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_DBPS_valueChanged(int)));

	connect(m_gui->DBAF,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_DBAF_toggled(bool)));

	connect(m_gui->DBPG,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_DBPG_valueChanged(int)));


	/*
	 *Schedule
	 */
	connect(m_gui->WMMD,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WMMD_toggled(bool)));

	connect(m_gui->WMWT_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMWT_H_valueChanged(int)));

	connect(m_gui->WMWT_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMWT_M_valueChanged(int)));

	connect(m_gui->WMTP,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WMTP_toggled(bool)));

	connect(m_gui->WMON_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMON_H_valueChanged(int)));

	connect(m_gui->WMON_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMON_M_valueChanged(int)));

	connect(m_gui->WME1_EN,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WME1_EN_toggled(bool)));

	connect(m_gui->WME1_EV,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_WME1_EV_valueChanged(int)));

	connect(m_gui->WME1_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME1_H_valueChanged(int)));

	connect(m_gui->WME1_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME1_M_valueChanged(int)));

	connect(m_gui->WME2_EN,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WME2_EN_toggled(bool)));

	connect(m_gui->WME2_EV,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_WME2_EV_valueChanged(int)));

	connect(m_gui->WME2_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME2_H_valueChanged(int)));

	connect(m_gui->WME2_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME2_M_valueChanged(int)));

	connect(m_gui->WME3_EN,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WME3_EN_toggled(bool)));

	connect(m_gui->WME3_EV,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_WME3_EV_valueChanged(int)));

	connect(m_gui->WME3_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME3_H_valueChanged(int)));

	connect(m_gui->WME3_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME3_M_valueChanged(int)));

	connect(m_gui->WME4_EN,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WME4_EN_toggled(bool)));

	connect(m_gui->WME4_EV,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_WME4_EV_valueChanged(int)));

	connect(m_gui->WME4_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME4_H_valueChanged(int)));

	connect(m_gui->WME4_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME4_M_valueChanged(int)));

	connect(m_gui->WME5_EN,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WME5_EN_toggled(bool)));

	connect(m_gui->WME5_EV,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_WME5_EV_valueChanged(int)));

	connect(m_gui->WME5_H,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME5_H_valueChanged(int)));

	connect(m_gui->WME5_M,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WME5_M_valueChanged(int)));

	connect(m_gui->WMES,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WMES_toggled(bool)));

	connect(m_gui->WMGI,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMGI_valueChanged(int)));

	connect(m_gui->WMIS,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_WMIS_toggled(bool)));

	connect(m_gui->WMGO,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_WMGO_valueChanged(int)));

	connect(m_gui->WMSI,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_WMSI_textChanged(const QString&)));

	connect(m_gui->WMSO,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_WMSO_textChanged(const QString&)));
}

void ZSettingsGUI::on_phoneBook_phoneChanged(QString const& phone, int index)
{
    emitUpdated(QString("PHN%1").arg(index), phone);
}

void ZSettingsGUI::on_phoneBook_phoneGroupChanged(QString const&, QString const& mask, int index)
{
    emitUpdated(QString("GRP%1").arg(index), mask);
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

void ZSettingsGUI::on_txtSIMSwapInterval_valueChanged(int value)
{
    emitUpdated("SWAP", value);
}

void ZSettingsGUI::on_txtRMNS_valueChanged(int value)
{
    emitUpdated("RMNS", value);
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
    emitUpdated("SCH1", !text.isEmpty() ? text + ":" + m_gui->SCH1_PORT->text() : "");
}

void ZSettingsGUI::on_SCH1_PORT_valueChanged(int value)
{
    emitUpdated("SCH1", m_gui->SCH1_IP->text() + ":" + QString::number(value));
}

void ZSettingsGUI::on_SCH2_IP_textChanged(QString const& text)
{
    emitUpdated("SCH2", !text.isEmpty() ? text + ":" + m_gui->SCH2_PORT->text() : "");
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
	m_gui->EPNG1->setEnabled(!checked);
    emitUpdated("EDNS", checked ? 1 : 0);
}

void ZSettingsGUI::on_PPNG_valueChanged(int value)
{
    emitUpdated("PPNG", value);
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
    emitUpdated("SSTB", index);
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

void ZSettingsGUI::on_NTPE_toggeld(bool checked)
{
	emitUpdated("NTPE", checked ? 1 : 0);
	m_gui->groupNTP->setEnabled(checked);
}

void ZSettingsGUI::on_NTPZ_valueChanged(int value)
{
	QString NTPZ;
	if (value > 0)
		NTPZ = QString("+%1").arg(value);
	else
		NTPZ = QString("%1").arg(value);

	emitUpdated("NTPZ", NTPZ);
}

void ZSettingsGUI::on_NTP1_textChanged(const QString&)
{
	emitUpdated("NTP1", m_gui->NTP1->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP1->text()).arg(m_gui->NTP1_P->value()));
}

void ZSettingsGUI::on_NTP1_P_valueChanged(int)
{
	emitUpdated("NTP1", m_gui->NTP1->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP1->text()).arg(m_gui->NTP1_P->value()));
}

void ZSettingsGUI::on_NTP2_textChanged(const QString&)
{
	emitUpdated("NTP2", m_gui->NTP2->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP2->text()).arg(m_gui->NTP2_P->value()));
}

void ZSettingsGUI::on_NTP2_P_valueChanged(int)
{
	emitUpdated("NTP2", m_gui->NTP2->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP2->text()).arg(m_gui->NTP2_P->value()));
}

void ZSettingsGUI::on_NTP3_textChanged(const QString&)
{
	emitUpdated("NTP3", m_gui->NTP3->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP3->text()).arg(m_gui->NTP3_P->value()));
}

void ZSettingsGUI::on_NTP3_P_valueChanged(int)
{
	emitUpdated("NTP3", m_gui->NTP3->text().isEmpty() ? ":" : QString("%1:%2").arg(m_gui->NTP3->text()).arg(m_gui->NTP3_P->value()));
}

void ZSettingsGUI::on_DBEN_toggled(bool checked)
{
	emitUpdated("DBEN", checked ? 1 : 0);
}

void ZSettingsGUI::on_DBMD_C_toggled(bool checked)
{
	if (checked)
		emitUpdated("DBMD", 0);

	m_gui->DBIP->setEnabled(checked);
	m_gui->DBPC->setEnabled(checked);
}

void ZSettingsGUI::on_DBMD_S_toggled(bool checked)
{
	if (checked)
		emitUpdated("DBMD", 1);

	m_gui->DBPS->setEnabled(checked);
}

void ZSettingsGUI::on_DBIP_textChanged(const QString& text)
{
	emitUpdated("DBIP", text);
}

void ZSettingsGUI::on_DBPC_valueChanged(int value)
{
	emitUpdated("DBPC", value);
}

void ZSettingsGUI::on_DBPS_valueChanged(int value)
{
	emitUpdated("DBPS", value);
}

void ZSettingsGUI::on_DBAF_toggled(bool checked)
{
	emitUpdated("DBAF", checked ? 1 : 0);
	m_gui->DBPG->setEnabled(!checked);
}

void ZSettingsGUI::on_DBPG_valueChanged(int value)
{
	emitUpdated("DBPG", value);
}

void ZSettingsGUI::on_WMMD_toggled(bool checked)
{
	emitUpdated("WMMD", checked ? 1 : 0);
}

void ZSettingsGUI::on_WMWT_H_valueChanged(int)
{
	emitUpdated("WMWT", QString().sprintf("%02d:%02d", m_gui->WMWT_H->value(), m_gui->WMWT_M->value()));
}

void ZSettingsGUI::on_WMWT_M_valueChanged(int value)
{
	emitUpdated("WMWT", QString().sprintf("%02d:%02d", m_gui->WMWT_H->value(), m_gui->WMWT_M->value()));
}

void ZSettingsGUI::on_WMTP_toggled(bool checked)
{
	emitUpdated("WMTP", checked ? 0 : 1);
	m_gui->WMON_H->setEnabled(checked);
	m_gui->WMON_M->setEnabled(checked);
	m_gui->frmTimes->setEnabled(!checked);
}

void ZSettingsGUI::on_WMON_H_valueChanged(int value)
{
	emitUpdated("WMON", QString().sprintf("%02d:%02d", m_gui->WMON_H->value(), m_gui->WMON_M->value()));
}

void ZSettingsGUI::on_WMON_M_valueChanged(int value)
{
	emitUpdated("WMON", QString().sprintf("%02d:%02d", m_gui->WMON_H->value(), m_gui->WMON_M->value()));
}

void ZSettingsGUI::update_WME(QString const& param, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm)
{
	emitUpdated(param, QString().sprintf("%d:%02d:%02d:%02d",
		en->isChecked() ? 1 : 0,
		ev->currentIndex(),
		hh->value(),
		mm->value()));
}

void ZSettingsGUI::on_WME1_EN_toggled(bool checked)
{
	update_WME("WME1", m_gui->WME1_EN, m_gui->WME1_EV, m_gui->WME1_H, m_gui->WME1_M);

}

void ZSettingsGUI::on_WME1_EV_valueChanged(int value)
{
	update_WME("WME1", m_gui->WME1_EN, m_gui->WME1_EV, m_gui->WME1_H, m_gui->WME1_M);
}

void ZSettingsGUI::on_WME1_H_valueChanged(int value)
{
	update_WME("WME1", m_gui->WME1_EN, m_gui->WME1_EV, m_gui->WME1_H, m_gui->WME1_M);
}

void ZSettingsGUI::on_WME1_M_valueChanged(int value)
{
	update_WME("WME1", m_gui->WME1_EN, m_gui->WME1_EV, m_gui->WME1_H, m_gui->WME1_M);
}

void ZSettingsGUI::on_WME2_EN_toggled(bool checked)
{
	update_WME("WME2", m_gui->WME2_EN, m_gui->WME2_EV, m_gui->WME2_H, m_gui->WME2_M);
}

void ZSettingsGUI::on_WME2_EV_valueChanged(int value)
{
	update_WME("WME2", m_gui->WME2_EN, m_gui->WME2_EV, m_gui->WME2_H, m_gui->WME2_M);
}

void ZSettingsGUI::on_WME2_H_valueChanged(int value)
{
	update_WME("WME2", m_gui->WME2_EN, m_gui->WME2_EV, m_gui->WME2_H, m_gui->WME2_M);
}

void ZSettingsGUI::on_WME2_M_valueChanged(int value)
{
	update_WME("WME2", m_gui->WME2_EN, m_gui->WME2_EV, m_gui->WME2_H, m_gui->WME2_M);
}

void ZSettingsGUI::on_WME3_EN_toggled(bool checked)
{
	update_WME("WME3", m_gui->WME3_EN, m_gui->WME3_EV, m_gui->WME3_H, m_gui->WME3_M);
}

void ZSettingsGUI::on_WME3_EV_valueChanged(int value)
{
	update_WME("WME3", m_gui->WME3_EN, m_gui->WME3_EV, m_gui->WME3_H, m_gui->WME3_M);
}

void ZSettingsGUI::on_WME3_H_valueChanged(int value)
{
	update_WME("WME3", m_gui->WME3_EN, m_gui->WME3_EV, m_gui->WME3_H, m_gui->WME3_M);
}

void ZSettingsGUI::on_WME3_M_valueChanged(int value)
{
	update_WME("WME3", m_gui->WME3_EN, m_gui->WME3_EV, m_gui->WME3_H, m_gui->WME3_M);
}

void ZSettingsGUI::on_WME4_EN_toggled(bool checked)
{
	update_WME("WME4", m_gui->WME4_EN, m_gui->WME4_EV, m_gui->WME4_H, m_gui->WME4_M);
}

void ZSettingsGUI::on_WME4_EV_valueChanged(int value)
{
	update_WME("WME4", m_gui->WME4_EN, m_gui->WME4_EV, m_gui->WME4_H, m_gui->WME4_M);
}

void ZSettingsGUI::on_WME4_H_valueChanged(int value)
{
	update_WME("WME4", m_gui->WME4_EN, m_gui->WME4_EV, m_gui->WME4_H, m_gui->WME4_M);
}

void ZSettingsGUI::on_WME4_M_valueChanged(int value)
{
	update_WME("WME4", m_gui->WME4_EN, m_gui->WME4_EV, m_gui->WME4_H, m_gui->WME4_M);
}

void ZSettingsGUI::on_WME5_EN_toggled(bool checked)
{
	update_WME("WME5", m_gui->WME5_EN, m_gui->WME5_EV, m_gui->WME5_H, m_gui->WME5_M);
}

void ZSettingsGUI::on_WME5_EV_valueChanged(int value)
{
	update_WME("WME5", m_gui->WME5_EN, m_gui->WME5_EV, m_gui->WME5_H, m_gui->WME5_M);
}

void ZSettingsGUI::on_WME5_H_valueChanged(int value)
{
	update_WME("WME5", m_gui->WME5_EN, m_gui->WME5_EV, m_gui->WME5_H, m_gui->WME5_M);
}

void ZSettingsGUI::on_WME5_M_valueChanged(int value)
{
	update_WME("WME5", m_gui->WME5_EN, m_gui->WME5_EV, m_gui->WME5_H, m_gui->WME5_M);
}

void ZSettingsGUI::on_WMES_toggled(bool checked)
{
	emitUpdated("WMES", checked ? 1 : 0);
	m_gui->WMGI->setEnabled(checked);
}

void ZSettingsGUI::on_WMGI_valueChanged(int value)
{
	emitUpdated("WMGI", value);
}

void ZSettingsGUI::on_WMIS_toggled(bool checked)
{
	emitUpdated("WMIS", checked ? 1 : 0);
	m_gui->WMGO->setEnabled(checked);
}

void ZSettingsGUI::on_WMGO_valueChanged(int value)
{
	emitUpdated("WMGO", value);
}

void ZSettingsGUI::on_WMSI_textChanged(const QString& text)
{
	emitUpdated("WMSI", text);
}

void ZSettingsGUI::on_WMSO_textChanged(const QString& text)
{
	emitUpdated("WMSO", text);
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
    m_gui->txtSIMSwapInterval->setValue(SWAP);

    int RMNS = settings->value("RMNS", 10).toInt();
    m_gui->txtRMNS->setValue(RMNS);

    QString APN1 = settings->value("APN1", "").toString();
    m_gui->txtAPN1->setText(APN1);

    QString APN2 = settings->value("APN2", "").toString();
    m_gui->txtAPN2->setText(APN2);

    QString LOG1 = settings->value("LOG1", "").toString();
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

    QString IPC1 = settings->value("IPC1", "").toString();
    m_gui->IPC1->setText(IPC1);

    QString IPC2 = settings->value("IPC2", "").toString();
    m_gui->IPC2->setText(IPC2);

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

    int SSTB = settings->value("SSTB", 0).toInt();
    m_gui->STOP->setCurrentIndex(SSTB);

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

    for (int i = 0; i < 10; i++)
    {
        QString PHNx = settings->value(QString("PHN%1").arg(i), "+7").toString();
        QString GRPx = settings->value(QString("GRP%1").arg(i), "0000000000").toString();
        m_gui->phoneBook->setPhone(PHNx, i);
        m_gui->phoneBook->setGroupMask(GRPx, i);
    }

	int DBEN = settings->value("DBEN", 0).toInt();
	m_gui->DBEN->setChecked(DBEN != 0 ? true : false);

	int DBMD = settings->value("DBMD", 1).toInt();
	if (DBMD == 0)
		m_gui->DBMD_S->setChecked(true);
	else
		m_gui->DBMD_C->setChecked(true);

	QString DBIP = settings->value("DBIP", "").toString();
	m_gui->DBIP->setText(DBIP);

	int DBPC = settings->value("DBPC", 9001).toInt();
	m_gui->DBPC->setValue(DBPC);

	int DBPS = settings->value("DBPS", 9001).toInt();
	m_gui->DBPS->setValue(DBPS);

	int DBAF = settings->value("DBAF", 0).toInt();
	m_gui->DBAF->setChecked(DBAF != 0);

	int DBPG = settings->value("DBPG", "1").toInt();
	m_gui->DBPG->setValue(DBPG);

	int NTPE = settings->value("NTPE", 0).toInt();
	m_gui->NTPE->setChecked(NTPE != 0);

	QString NTP1 = settings->value("NTP1", "ntp2.stratum2.ru:123").toString();
	QStringList NTP1_items = NTP1.split(':');
	m_gui->NTP1->setText(NTP1_items.length() > 0 ? NTP1_items[0] : "ntp2.stratum2.ru");
	m_gui->NTP1_P->setValue(NTP1_items.length() > 1 ? NTP1_items[1].toInt() : 123);

	QString NTP2 = settings->value("NTP2", "ntp3.stratum2.ru:123").toString();
	QStringList NTP2_items = NTP2.split(':');
	m_gui->NTP2->setText(NTP2_items.length() > 0 ? NTP2_items[0] : "ntp3.stratum2.ru");
	m_gui->NTP2_P->setValue(NTP2_items.length() > 1 ? NTP2_items[1].toInt() : 123);

	QString NTP3 = settings->value("NTP3", "ntp4.stratum2.ru:123").toString();
	QStringList NTP3_items = NTP3.split(':');
	m_gui->NTP3->setText(NTP3_items.length() > 0 ? NTP3_items[0] : "ntp4.stratum2.ru");
	m_gui->NTP3_P->setValue(NTP3_items.length() > 1 ? NTP3_items[1].toInt() : 123);

	QString NTPZ = settings->value("NTPZ", "+12").toString();
	int NTPZ_int = NTPZ.toInt();
	m_gui->NTPZ->setValue(NTPZ_int);

	int WMMD = settings->value("WMMD", 0).toInt();
	m_gui->WMMD->setChecked(WMMD != 0);

	int WMTP = settings->value("WMTP", 0).toInt();
	if (WMTP == 0)
		m_gui->WMTP->setChecked(true);
	else
		m_gui->WMTP_2->setChecked(true);

	QStringList WMWT = settings->value("WMWT", "01:00").toString().split(':');
	m_gui->WMWT_H->setValue(WMWT.length() > 0 ? WMWT[0].toInt() : 1);
	m_gui->WMWT_M->setValue(WMWT.length() > 1 ? WMWT[1].toInt() : 0);

	QStringList WMON = settings->value("WMON", "06:00").toString().split(':');
	m_gui->WMON_H->setValue(WMON.length() > 0 ? WMON[0].toInt() : 6);
	m_gui->WMON_M->setValue(WMON.length() > 1 ? WMON[1].toInt() : 0);

	QStringList WME1 = settings->value("WME1", "0:00:00:00").toString().split(':');
	render_WME(WME1, m_gui->WME1_EN, m_gui->WME1_EV, m_gui->WME1_H, m_gui->WME1_M);

	QStringList WME2 = settings->value("WME2", "0:00:00:00").toString().split(':');
	render_WME(WME2, m_gui->WME2_EN, m_gui->WME2_EV, m_gui->WME2_H, m_gui->WME2_M);

	QStringList WME3 = settings->value("WME3", "0:00:00:00").toString().split(':');
	render_WME(WME3, m_gui->WME3_EN, m_gui->WME3_EV, m_gui->WME3_H, m_gui->WME3_M);

	QStringList WME4 = settings->value("WME4", "0:00:00:00").toString().split(':');
	render_WME(WME4, m_gui->WME4_EN, m_gui->WME4_EV, m_gui->WME4_H, m_gui->WME4_M);

	QStringList WME5 = settings->value("WME5", "0:00:00:00").toString().split(':');
	render_WME(WME5, m_gui->WME5_EN, m_gui->WME5_EV, m_gui->WME5_H, m_gui->WME5_M);

	int WMES = settings->value("WMES", 0).toInt();
	m_gui->WMES->setChecked(WMES != 0);

	int WMGI = settings->value("WMGI", 3).toInt();
	m_gui->WMGI->setValue(WMGI);

	int WMIS = settings->value("WMIS", 0).toInt();
	m_gui->WMIS->setChecked(WMIS != 0);

	int WMGO = settings->value("WMGO", 4).toInt();
	m_gui->WMGO->setValue(WMGO);

	QString WMSI = settings->value("WMSI", "start").toString();
	m_gui->WMSI->setText(WMSI);

	QString WMSO = settings->value("WMSO", "stop").toString();
	m_gui->WMSO->setText(WMSO);
}

void ZSettingsGUI::render_WME(QStringList const& params, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm)
{
	en->setChecked(params.length() > 0 ? (params[0].toInt() != 0 ? true : false) : false);
	ev->setCurrentIndex(params.length() > 1 ? params[1].toInt() : 0);
	hh->setValue(params.length() > 2 ? params[2].toInt() : 0);
	mm->setValue(params.length() > 3 ? params[3].toInt() : 0);
}