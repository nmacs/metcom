#include "phonebook.h"
#include <QGridLayout>
#include <QLabel>

PhoneBook::PhoneBook(QWidget *parent) :
    QFrame(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setHorizontalSpacing(20);
    layout->setVerticalSpacing(20);

    QLabel *label = new QLabel(this);
    label->setText("+7XXXXXXXXXX");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label, 0, 0);

    for (int i = 0; i < 10; i++)
    {
        QLabel *label = new QLabel(this);
        label->setText(QString::number(i + 1));
        layout->addWidget(label, 0, i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        QLineEdit *edit = new QLineEdit(this);
        edit->setProperty("row", i);
        layout->addWidget(edit, i + 1, 0);

        m_phones.push_back(edit);

        connect(edit, &QLineEdit::textChanged,
                this, &PhoneBook::phoneTextChanged);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            QCheckBox *check = new QCheckBox(this);
            check->setProperty("row", i);
            check->setProperty("col", j);
            layout->addWidget(check, i + 1, j + 1);

            m_mask.push_back(check);

            connect(check, &QCheckBox::toggled,
                    this, &PhoneBook::phoneGroupToggled);
        }
    }
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::setPhone(const QString &phone, int index)
{
    m_phones.at(index)->setText(phone);
}

void PhoneBook::setGroupMask(const QString &mask, int index)
{
    int i;
    int len = mask.length();
    if (len > 10)
    {
        len = 10;
    }

    if (index > 10)
    {
        index = 10;
    }

    for (i = 0; i < len; i++)
    {
        m_mask.at(index * 10 + i)->setChecked(mask.at(i).toLatin1() != '0');
    }

    for (; i < 10; i++)
    {
        m_mask.at(index * 10 + i)->setChecked(false);
    }
}

void PhoneBook::phoneTextChanged(const QString &text)
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
    int row = edit->property("row").toInt();
    emit phoneChanged(text, row);
}

void PhoneBook::phoneGroupToggled(bool)
{
    QCheckBox *check = qobject_cast<QCheckBox*>(sender());
    int row = check->property("row").toInt();
    QString phone = m_phones.at(row)->text();
    QString mask;

    for (int i = 0; i < 10; i++)
    {
        mask += m_mask.at(row * 10 + i)->isChecked() ? "1" : "0";
    }

    emit phoneGroupChanged(phone, mask, row);
}
