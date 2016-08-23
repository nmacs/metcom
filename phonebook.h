#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QFrame>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QList>

class PhoneBook : public QFrame
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = 0);
    ~PhoneBook();

    void setPhone(QString const& phone, int index);
    void setGroupMask(QString const& mask, int index);

signals:
    void phoneChanged(QString const& phone, int index);
    void phoneGroupChanged(QString const& phone, QString const& mask, int index);

private slots:
    void phoneTextChanged(QString const& text);
    void phoneGroupToggled(bool checked);

private:
    QList<QLineEdit*> m_phones;
    QList<QCheckBox*> m_mask;
};

#endif // PHONEBOOK_H
