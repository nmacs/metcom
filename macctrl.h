#pragma once

#include <QFrame>
#include <QLineEdit>

#define QTUTL_MAC_SIZE 6

class MACCtrl : public QFrame
{
	typedef QFrame baseClass;
	Q_OBJECT
public:
	MACCtrl(QWidget *parent);
	~MACCtrl();

	QString MAC() const;
	void setMAC(QString const& ip);

	virtual bool eventFilter(QObject *obj, QEvent *event);

	public slots:
	void slotTextChanged(QLineEdit* pEdit);

signals:
	void signalTextChanged(QLineEdit* pEdit);
	void textChanged(QString const& text);

private slots:
	void itemTextChanged(QString const& text);
	void toUpper(const QString &text);

private:
	QLineEdit *(m_pLineEdit[QTUTL_MAC_SIZE]);

	static QString getMACItemStr(unsigned char item);
};
