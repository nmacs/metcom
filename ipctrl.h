#ifndef IPCTRL_H
#define IPCTRL_H

#include <QFrame>
#include <QLineEdit>

#define QTUTL_IP_SIZE 4

class IPCtrl : public QFrame
{
    typedef QFrame baseClass;
    Q_OBJECT
public:
    IPCtrl(QWidget *parent);
    ~IPCtrl();

    QString IP() const;
    void setIP(QString const& ip);

    virtual bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void slotTextChanged(QLineEdit* pEdit);

signals:
    void signalTextChanged(QLineEdit* pEdit);
    void textChanged(QString const& text);

private slots:
    void itemTextChanged(QString const& text);

private:
    QLineEdit *(m_pLineEdit[QTUTL_IP_SIZE]);

    static std::string getIPItemStr(unsigned char item);
};

#endif // IPCTRL_H
