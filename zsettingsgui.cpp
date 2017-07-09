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

    connect(m_gui->MODE,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_MODE_toggled);

    connect(m_gui->IP1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_IP1_textChanged);

    connect(m_gui->IP2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_IP2_textChanged);

    connect(m_gui->PORT1,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PORT1_valueChanged(int)));

    connect(m_gui->PORT2,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PORT2_valueChanged(int)));

    connect(m_gui->ENIP1,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_ENIP1_textChanged);

    connect(m_gui->ENIP2,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_ENIP2_textChanged);

    connect(m_gui->ENIP3,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_ENIP3_textChanged);

    connect(m_gui->ENIP4,
            &IPCtrl::textChanged,
            this,
            &ZSettingsGUI::on_ENIP4_textChanged);

    connect(m_gui->SPORT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_SPORT_valueChanged(int)));

    connect(m_gui->MPSIZE,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_MPSIZE_valueChanged(int)));

    connect(m_gui->TOUT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_TOUT_valueChanged(int)));

    connect(m_gui->SITOUT,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_SITOUT_valueChanged(int)));

    /*
     * Network
     */

    connect(m_gui->DHCP,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_DHCP_toggled);

	connect(m_gui->LOCALIP,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_LOCALIP_textChanged(const QString&)));

	connect(m_gui->SUBMASK,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_SUBMASK_textChanged(const QString&)));

	connect(m_gui->DEFGWAY,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_DEFGWAY_textChanged(const QString&)));

	connect(m_gui->PRIDNS,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_PRIDNS_textChanged(const QString&)));

	connect(m_gui->SECDNS,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_SECDNS_textChanged(const QString&)));

	connect(m_gui->MAC,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_MAC_textChanged(const QString&)));

    /*
     * PING
     */

	connect(m_gui->TIMEPING,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_TIMEPING_valueChanged(int)));

    connect(m_gui->PINGDNS,
            &QCheckBox::toggled,
            this,
            &ZSettingsGUI::on_PINGDNS_toggled);

	connect(m_gui->ENPING,
			&QGroupBox::toggled,
			this,
			&ZSettingsGUI::on_ENPING_toggled);

    connect(m_gui->PINGIP1,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_PINGIP1_textChanged);

    connect(m_gui->PINGIP2,
            &QLineEdit::textChanged,
            this,
            &ZSettingsGUI::on_PINGIP2_textChanged);


	/*
	 * Interface
	 */

	connect(m_gui->BDRT,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_BDRT_currentIndexChanged(int)));

	connect(m_gui->SETUART,
		&QRadioButton::toggled,
		this,
		&ZSettingsGUI::on_SETUART_toggled);

	/*
	 * Access
	 */

	connect(m_gui->ENDBG,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_ENDBG_toggled(bool)));

	connect(m_gui->MODEDBG,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_MODEDBG_toggled(bool)));

	connect(m_gui->IPDBG,
		SIGNAL(textChanged(const QString&)),
		this,
		SLOT(on_IPDBG_textChanged(const QSTring&)));

	connect(m_gui->PORTDBG,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_PORTDBG_valueChanged(int)));

	connect(m_gui->PORTSDBG,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_PORTSDBG_valueChanged(int)));

	connect(m_gui->PORTTN,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_PORTTN_valueChanged(int)));

	
	/*
	* Reset/Time
	*/

    connect(m_gui->INTTIM,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_INTTIM_toggled);

    connect(m_gui->PINTTIM,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_PINTTIM_valueChanged(int)));

    connect(m_gui->DLYTIM,
            &QRadioButton::toggled,
            this,
            &ZSettingsGUI::on_DLYTIM_toggled);

    connect(m_gui->HOURTIM,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_HOURTIM_valueChanged(int)));

    connect(m_gui->MINTIM,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(on_MINTIM_valueChanged(int)));

	connect(m_gui->ENNTP,
			SIGNAL(toggled(bool)),
			this,
			SLOT(on_ENNTP_toggeld(bool)));

	connect(m_gui->TZONE,
			SIGNAL(valueChanged(int)),
			this,
			SLOT(on_TZONE_valueChanged(int)));

	connect(m_gui->NTP1,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP1_textChanged(const QString&)));

	connect(m_gui->NTP2,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP2_textChanged(const QString&)));

	connect(m_gui->NTP3,
			SIGNAL(textChanged(const QString&)),
			this,
			SLOT(on_NTP3_textChanged(const QString&)));
}

/*
 * Mode
 */

void ZSettingsGUI::on_MODE_toggled(bool checked)
{
	m_gui->groupModeServer->setEnabled(checked);
	m_gui->groupModeClient->setEnabled(!checked);
	emitUpdated("MODE", checked ? 1 : 0);
}

void ZSettingsGUI::on_IP1_textChanged(const QString &text)
{
	emitUpdated("IP1", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_IP2_textChanged(const QString &text)
{
	emitUpdated("IP2", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_PORT1_valueChanged(int value)
{
	emitUpdated("PORT1", value);
}

void ZSettingsGUI::on_PORT2_valueChanged(int value)
{
	emitUpdated("PORT2", value);
}

void ZSettingsGUI::on_ENIP1_textChanged(QString const& text)
{
	emitUpdated("ENIP1", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_ENIP2_textChanged(QString const& text)
{
	emitUpdated("ENIP2", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_ENIP3_textChanged(QString const& text)
{
	emitUpdated("ENIP3", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_ENIP4_textChanged(QString const& text)
{
	emitUpdated("ENIP4", text != "0.0.0.0" ? text : "");
}

void ZSettingsGUI::on_SPORT_valueChanged(int value)
{
	emitUpdated("SPORT", value);
}

void ZSettingsGUI::on_MPSIZE_valueChanged(int value)
{
	emitUpdated("MPSIZE", value);
}

void ZSettingsGUI::on_TOUT_valueChanged(int value)
{
	emitUpdated("TOUT", value);
}

void ZSettingsGUI::on_SITOUT_valueChanged(int value)
{
	emitUpdated("SITOUT", value);
}

/*
 * Network
 */

void ZSettingsGUI::on_DHCP_toggled(bool checked)
{
	m_gui->groupLOCALIP->setEnabled(!checked);

	emitUpdated("DHCP", checked ? 1 : 0);
}

void ZSettingsGUI::on_LOCALIP_textChanged(const QString &text)
{
	emitUpdated("LOCALIP", text);
}

void ZSettingsGUI::on_SUBMASK_textChanged(const QString &text)
{
	emitUpdated("SUBMASK", text);
}

void ZSettingsGUI::on_DEFGWAY_textChanged(const QString &text)
{
	emitUpdated("DEFGWAY", text);
}

void ZSettingsGUI::on_PRIDNS_textChanged(const QString &text)
{
	emitUpdated("PRIDNS", text);
}

void ZSettingsGUI::on_SECDNS_textChanged(const QString &text)
{
	emitUpdated("SECDNS", text);
}

void ZSettingsGUI::on_MAC_textChanged(const QString &text)
{
	emitUpdated("MAC", text);
}


/*
 * PING
 */

void ZSettingsGUI::on_TIMEPING_valueChanged(int value)
{
	emitUpdated("TIMEPING", value);
}

void ZSettingsGUI::on_PINGDNS_toggled(bool checked)
{
	emitUpdated("PINGDNS", checked ? 1 : 0);

	m_gui->ENPING->setEnabled(!checked);
}

void ZSettingsGUI::on_ENPING_toggled(bool checked)
{
	emitUpdated("ENPING", checked ? 1 : 0);
}

void ZSettingsGUI::on_PINGIP1_textChanged(const QString &text)
{
	emitUpdated("PINGIP1", text);
}

void ZSettingsGUI::on_PINGIP2_textChanged(const QString &text)
{
	emitUpdated("PINGIP2", text);
}


/*
 * Interface
 */

void ZSettingsGUI::on_BDRT_currentIndexChanged(int index)
{
	emitUpdated("BDRT", index);
}

void ZSettingsGUI::on_SETUART_toggled(bool checked)
{
	emitUpdated("SETUART", checked ? 1 : 0);
}

/*
 * Access
 */

void ZSettingsGUI::on_ENDBG_toggled(bool checked)
{
	emitUpdated("ENDBG", checked ? 1 : 0);
}

void ZSettingsGUI::on_MODEDBG_toggled(bool checked)
{
	m_gui->IPDBG->setEnabled(!checked);
	m_gui->PORTDBG->setEnabled(!checked);
	m_gui->PORTSDBG->setEnabled(checked);

	emitUpdated("MODEDBG", checked ? 1 : 0);
}

void ZSettingsGUI::on_IPDBG_textChanged(const QString &text)
{
	emitUpdated("IPDBG", text);
}

void ZSettingsGUI::on_PORTDBG_valueChanged(int value)
{
	emitUpdated("PORTDBG", value);
}

void ZSettingsGUI::on_PORTSDBG_valueChanged(int value)
{
	emitUpdated("PORTSDBG", value);
}

void ZSettingsGUI::on_PORTTN_valueChanged(int value)
{
	emitUpdated("PORTTN", value);
}

/*
 * Resetart/Time
 */

void ZSettingsGUI::on_INTTIM_toggled(bool checked)
{
	emitUpdated("INTTIM", checked ? 1 : 0);
	m_gui->groupINTTIM->setEnabled(checked);
}

void ZSettingsGUI::on_PINTTIM_valueChanged(int value)
{
	emitUpdated("PINTTIM", value);
}

void ZSettingsGUI::on_DLYTIM_toggled(bool checked)
{
	emitUpdated("DLYTIM", checked ? 1 : 0);
	m_gui->groupDLYTIM->setEnabled(checked);
}

void ZSettingsGUI::on_HOURTIM_valueChanged(int value)
{
	emitUpdated("HOURTIM", value);
}

void ZSettingsGUI::on_MINTIM_valueChanged(int value)
{
	emitUpdated("MINTIM", value);
}

void ZSettingsGUI::on_ENNTP_toggeld(bool checked)
{
	emitUpdated("ENNTP", checked ? 1 : 0);
	m_gui->groupENNTP->setEnabled(checked);
}

void ZSettingsGUI::on_TZONE_valueChanged(int value)
{
	if (value > 0)
		emitUpdated("TZONE", QString("+%1").arg(value));
	else 
		emitUpdated("TZONE", QString("%1").arg(value));
}

void ZSettingsGUI::on_NTP1_textChanged(const QString &text)
{
	emitUpdated("NTP1", text);
}

void ZSettingsGUI::on_NTP2_textChanged(const QString &text)
{
	emitUpdated("NTP2", text);
}

void ZSettingsGUI::on_NTP3_textChanged(const QString &text)
{
	emitUpdated("NTP3", text);
}

void ZSettingsGUI::draw(ZSettings *settings)
{
	/*
	 * Mode
	 */

	int MODE = settings->value("MODE", 0).toInt();
	if (MODE == 0)
	{
		m_gui->MODE_0->setChecked(true);
	}
	else
	{
		m_gui->MODE->setChecked(true);
	}

	m_gui->IP1->setText(settings->value("IP1", "").toString());
	m_gui->PORT1->setValue(settings->value("PORT1", 0).toInt());
	m_gui->IP2->setText(settings->value("IP2", "").toString());
	m_gui->PORT2->setValue(settings->value("PORT2", 0).toInt());

	m_gui->SPORT->setValue(settings->value("SPORT", 0).toInt());

	m_gui->ENIP1->setIP(settings->value("ENIP1", "").toString());
	m_gui->ENIP2->setIP(settings->value("ENIP2", "").toString());
	m_gui->ENIP3->setIP(settings->value("ENIP3", "").toString());
	m_gui->ENIP4->setIP(settings->value("ENIP4", "").toString());
	
	m_gui->MPSIZE->setValue(settings->value("MPSIZE", 0).toInt());
	m_gui->TOUT->setValue(settings->value("TOUT", 0).toInt());
	m_gui->SITOUT->setValue(settings->value("SITOUT", 0).toInt());

	/*
	 * Network
	 */

	m_gui->DHCP->setChecked(settings->value("DHCP", false).toBool());

	m_gui->LOCALIP->setIP(settings->value("LOCALIP", "").toString());
	m_gui->SUBMASK->setIP(settings->value("SUBMASK", "").toString());
	m_gui->DEFGWAY->setIP(settings->value("DEFGWAY", "").toString());
	m_gui->PRIDNS->setIP(settings->value("PRIDNS", "").toString());
	m_gui->SECDNS->setIP(settings->value("SECDNS", "").toString());

	m_gui->MAC->setMAC(settings->value("MAC", "").toString());

	/*
	 * PING
	 */

	m_gui->TIMEPING->setValue(settings->value("TIMEPING", 0).toInt());
	m_gui->PINGDNS->setChecked(settings->value("PINGDNS", 0).toInt() != 0);
	m_gui->ENPING->setChecked(settings->value("ENPING", 0).toInt() != 0);
	m_gui->PINGIP1->setText(settings->value("PINGIP1", "").toString());
	m_gui->PINGIP2->setText(settings->value("PINGIP2", "").toString());

	/*
	 * Interface
	 */

	m_gui->BDRT->setCurrentIndex(settings->value("BDRT", 0).toInt());
	if (settings->value("SETUART", 0).toInt() != 0)
		m_gui->SETUART->setChecked(true);
	else
		m_gui->SETUART_0->setChecked(true);

	/*
	 * Access
	 */

	m_gui->ENDBG->setChecked(settings->value("ENDBG", 0).toInt() != 0);

	if (settings->value("MODEDBG", 0).toInt() != 0)
		m_gui->MODEDBG->setChecked(true);
	else
		m_gui->MODEDBG_0->setChecked(true);

	m_gui->IPDBG->setText(settings->value("IPDBG", "").toString());
	m_gui->PORTDBG->setValue(settings->value("PORTDBG", 0).toInt());
	m_gui->PORTSDBG->setValue(settings->value("PORTSDBG", 0).toInt());
	m_gui->PORTTN->setValue(settings->value("PORTTN", 0).toInt());

	/*
	 * Restart/Time
	 */

	m_gui->INTTIM->setChecked(settings->value("INTTIM", 0).toInt() != 0);
	m_gui->PINTTIM->setValue(settings->value("PINTTIM", 0).toInt());

	m_gui->DLYTIM->setChecked(settings->value("DLYTIM", 0).toInt() != 0);
	m_gui->HOURTIM->setValue(settings->value("HOURTIM", 0).toInt());
	m_gui->MINTIM->setValue(settings->value("MINTIM", 0).toInt());

	m_gui->ENNTP->setChecked(settings->value("ENNTP", 0).toInt() != 0);
	m_gui->TZONE->setValue(settings->value("TZONE", 0).toInt());
	m_gui->NTP1->setText(settings->value("NTP1", "").toString());
	m_gui->NTP2->setText(settings->value("NTP2", "").toString());
	m_gui->NTP3->setText(settings->value("NTP3", "").toString());	
}
