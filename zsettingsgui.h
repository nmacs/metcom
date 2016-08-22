#ifndef ZSETTINGSGUI_H
#define ZSETTINGSGUI_H

#include "mainwindow.h"
#include "zsettingsview.h"

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
    void on_txtSIMSwapInterval_textChanged(const QString &text);
    void on_txtRMNS_textChanged(const QString &text);
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

private:
    Ui::MainWindow* m_gui;
};

#endif // ZSETTINGSGUI_H
