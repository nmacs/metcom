#ifndef ZSETTINGSGUI_H
#define ZSETTINGSGUI_H

#include "mainwindow.h"
#include "zsettingsview.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>

class ZSettingsGUI : public ZSettingsView
{
    Q_OBJECT
public:
    ZSettingsGUI(Ui::MainWindow* gui, QObject *parent = 0);

    virtual void draw(ZSettings *settings);

private slots:
	/*
	 * Mode
	 */
    void on_MODE_toggled(bool checked);
	void on_IP1_textChanged(const QString &text);
	void on_IP2_textChanged(const QString &text);
	void on_PORT1_valueChanged(int value);
	void on_PORT2_valueChanged(int value);
	void on_ENIP1_textChanged(const QString &text);
	void on_ENIP2_textChanged(const QString &text);
	void on_ENIP3_textChanged(const QString &text);
	void on_ENIP4_textChanged(const QString &text);
	void on_SPORT_valueChanged(int value);
	void on_MPSIZE_valueChanged(int value);
	void on_TOUT_valueChanged(int value);
	void on_SITOUT_valueChanged(int value);

	/*
	 * Network
	 */
	void on_DHCP_toggled(bool checked);
	void on_LOCALIP_textChanged(const QString &text);
	void on_SUBMASK_textChanged(const QString &text);
	void on_DEFGWAY_textChanged(const QString &text);
	void on_PRIDNS_textChanged(const QString &text);
	void on_SECDNS_textChanged(const QString &text);
	void on_MAC_textChanged(const QString &text);

	/*
	 * PING
	 */

	void on_TIMEPING_valueChanged(int value);
	void on_PINGDNS_toggled(bool checked);
	void on_ENPING_toggled(bool checked);
	void on_PINGIP1_textChanged(const QString &text);
	void on_PINGIP2_textChanged(const QString &text);

	/*
	 * Interface
	 */

	void on_BDRT_currentIndexChanged(int index);
	void on_SETUART_toggled(bool checked);

	/*
	 * Access
	 */

	void on_ENDBG_toggled(bool checked);
	void on_MODEDBG_toggled(bool checked);
	void on_IPDBG_textChanged(const QString &text);
	void on_PORTDBG_valueChanged(int value);
	void on_PORTSDBG_valueChanged(int value);
	void on_PORTTN_valueChanged(int value);

	/*
	 * Reset/Time
	 */

	void on_INTTIM_toggled(bool checked);
	void on_PINTTIM_valueChanged(int value);
	void on_DLYTIM_toggled(bool checked);
	void on_HOURTIM_valueChanged(int value);
	void on_MINTIM_valueChanged(int value);
	void on_ENNTP_toggeld(bool checked);
	void on_TZONE_valueChanged(int value);
	void on_NTP1_textChanged(const QString &text);
	void on_NTP2_textChanged(const QString &text);
	void on_NTP3_textChanged(const QString &text);

private:
	void update_WME(QString const& param, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm);
	void render_WME(QStringList const& params, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm);

    Ui::MainWindow* m_gui;
};

#endif // ZSETTINGSGUI_H
