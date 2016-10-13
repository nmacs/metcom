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
    void on_chkSIM1Enable_toggled(bool checked);
    void on_chkSIM2Enable_toggled(bool checked);
    void on_radioModeModem_toggled(bool checked);
    void on_radioModeClient_toggled(bool checked);
    void on_radioModeServer_toggled(bool checked);
    void on_APHN_toggled(bool checked);
    void on_radioSIM1_toggled(bool checked);
    void on_radioSIM2_toggled(bool checked);
    void on_txtSIMSwapInterval_valueChanged(int value);
    void on_txtRMNS_valueChanged(int value);
    void on_txtAPN1_textChanged(const QString &text);
    void on_txtAPN2_textChanged(const QString &text);
    void on_txtLOG1_textChanged(const QString &text);
    void on_txtLOG2_textChanged(const QString &text);
    void on_txtPSW1_textChanged(const QString &text);
    void on_txtPSW2_textChanged(const QString &text);
    void on_txtPIN1_textChanged(const QString &text);
    void on_txtPIN2_textChanged(const QString &text);
    void on_chkROA1_toggled(bool checked);
    void on_chkROA2_toggled(bool checked);
    void on_NET1_currentIndexChanged(int index);
    void on_NET2_currentIndexChanged(int index);
    void on_GCSD_valueChanged(int value);
    void on_IPC1_textChanged(const QString &text);
    void on_IPC2_textChanged(const QString &text);
    void on_PTC1_valueChanged(int value);
    void on_PTC2_valueChanged(int value);
    void on_EIP1_textChanged(const QString &text);
    void on_EIP2_textChanged(const QString &text);
    void on_EIP3_textChanged(const QString &text);
    void on_EIP4_textChanged(const QString &text);
    void on_PTSR_valueChanged(int value);
    void on_MPSZ_valueChanged(int value);
    void on_TRDT_valueChanged(int value);
    void on_SITT_valueChanged(int value);
    void on_ESCH_toggled(bool checked);
    void on_SCH1_IP_textChanged(const QString &text);
    void on_SCH1_PORT_valueChanged(int value);
    void on_SCH2_IP_textChanged(const QString &text);
    void on_SCH2_PORT_valueChanged(int value);
    void on_EPNG1_toggled(bool checked);
    void on_IPP1_textChanged(const QString &text);
    void on_IPP2_textChanged(const QString &text);
    void on_EDNS_toggled(bool checked);
    void on_PPNG_valueChanged(int value);
    void on_MPRT_RS232_toggled(bool checked);
    void on_MPRT_RS485_toggled(bool checked);
    void on_MAPT_currentIndexChanged(int index);
    void on_BDRT_currentIndexChanged(int index);
    void on_BITS_currentIndexChanged(int index);
    void on_PRTY_currentIndexChanged(int index);
    void on_STOP_currentIndexChanged(int index);
    void on_RSIT_toggled(bool checked);
    void on_RSHR_valueChanged(int value);
    void on_RSDT_toggled(bool checked);
    void on_DTHR_valueChanged(int value);
    void on_DTMN_valueChanged(int value);
    void on_GPHR_valueChanged(int value);
    void on_phoneBook_phoneChanged(const QString &phone, int index);
    void on_phoneBook_phoneGroupChanged(const QString &phone, const QString &mask, int index);
	void on_DBEN_toggled(bool checked);
	void on_DBMD_C_toggled(bool checked);
	void on_DBMD_S_toggled(bool checked);
	void on_DBIP_textChanged(const QString& text);
	void on_DBPC_valueChanged(int value);
	void on_DBPS_valueChanged(int value);
	void on_DBAF_toggled(bool checked);
	void on_DBPG_valueChanged(int value);
	void on_NTPE_toggeld(bool checked);
	void on_NTPZ_valueChanged(int value);
	void on_NTP1_textChanged(const QString& text);
	void on_NTP1_P_valueChanged(int value);
	void on_NTP2_textChanged(const QString& text);
	void on_NTP2_P_valueChanged(int value);
	void on_NTP3_textChanged(const QString& text);
	void on_NTP3_P_valueChanged(int value);

	void on_WMMD_toggled(bool checked);
	void on_WMWT_H_valueChanged(int value);
	void on_WMWT_M_valueChanged(int value);
	void on_WMTP_toggled(bool checked);
	void on_WMON_H_valueChanged(int value);
	void on_WMON_M_valueChanged(int value);
	void on_WME1_EN_toggled(bool checked);
	void on_WME1_EV_valueChanged(int value);
	void on_WME1_H_valueChanged(int value);
	void on_WME1_M_valueChanged(int value);
	void on_WME2_EN_toggled(bool checked);
	void on_WME2_EV_valueChanged(int value);
	void on_WME2_H_valueChanged(int value);
	void on_WME2_M_valueChanged(int value);
	void on_WME3_EN_toggled(bool checked);
	void on_WME3_EV_valueChanged(int value);
	void on_WME3_H_valueChanged(int value);
	void on_WME3_M_valueChanged(int value);
	void on_WME4_EN_toggled(bool checked);
	void on_WME4_EV_valueChanged(int value);
	void on_WME4_H_valueChanged(int value);
	void on_WME4_M_valueChanged(int value);
	void on_WME5_EN_toggled(bool checked);
	void on_WME5_EV_valueChanged(int value);
	void on_WME5_H_valueChanged(int value);
	void on_WME5_M_valueChanged(int value);
	void on_WMES_toggled(bool checked);
	void on_WMGI_valueChanged(int value);
	void on_WMIS_toggled(bool checked);
	void on_WMGO_valueChanged(int value);
	void on_WMSI_textChanged(const QString& text);
	void on_WMSO_textChanged(const QString& text);

private:
	void update_WME(QString const& param, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm);
	void render_WME(QStringList const& params, QCheckBox* en, QComboBox* ev, QSpinBox* hh, QSpinBox* mm);

    Ui::MainWindow* m_gui;
};

#endif // ZSETTINGSGUI_H
