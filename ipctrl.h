#ifndef IPCTRL_H
#define IPCTRL_H

#include <QFrame>
#include <QLineEdit>

class IPCtrl : public QFrame
{
    typedef QFrame baseClass;
    Q_OBJECT
public:
    IPCtrl(QWidget *parent);
    ~IPCtrl();

#define QTUTL_IP_SIZE 4

    virtual bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void slotTextChanged(QLineEdit* pEdit);

signals:
    void signalTextChanged(QLineEdit* pEdit);

private:
    QLineEdit *(m_pLineEdit[QTUTL_IP_SIZE]);

    static std::string getIPItemStr(unsigned char item);
};

#endif // IPCTRL_H
