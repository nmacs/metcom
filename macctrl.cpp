#include "macctrl.h"
#include <QIntValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <strstream>
#include <QEvent>
#include <QKeyEvent>

class MACItemValidator : public QIntValidator
{
public:
	MACItemValidator(QObject* parent) : QIntValidator(parent)
	{
		setRange(0, UCHAR_MAX);
	}
	~MACItemValidator() {}

	virtual QValidator::State validate(QString &text, int &pos) const
	{
		if (text.isEmpty())
		{
			return QValidator::Intermediate;
		}

		bool ok;
		int value = text.toInt(&ok, 16);

		if (!ok)
		{
			return QValidator::Invalid;
		}

		return QValidator::Acceptable;
	}

	virtual void fixup(QString & input) const
	{
		if (input.isEmpty())
			input = "00";
		else
		{
			bool ok;
			int value = input.toInt(&ok, 16);
			if (ok)
			{
				if (value < 0)
				{
					input = "00";
				}
				else if (value > UCHAR_MAX)
				{
					input = "FF";
				}
			}
			else
			{
				input = "00";
			}
		}

	}
};

MACCtrl::MACCtrl(QWidget *parent) : baseClass(parent)
{
	setFrameShape(QFrame::StyledPanel);
	setFrameShadow(QFrame::Sunken);

	QHBoxLayout* pLayout = new QHBoxLayout(this);
	setLayout(pLayout);
	pLayout->setContentsMargins(5, 1, 5, 1);
	pLayout->setSpacing(0);

	for (int i = 0; i != QTUTL_MAC_SIZE; ++i)
	{
		if (i != 0)
		{
			QLabel* pDot = new QLabel(":", this);
			pDot->setStyleSheet("background: white");
			pLayout->addWidget(pDot);
			pLayout->setStretch(pLayout->count(), 0);
		}

		m_pLineEdit[i] = new QLineEdit(this);
		QLineEdit* pEdit = m_pLineEdit[i];

		pEdit->setText("00");
		pEdit->installEventFilter(this);

		connect(pEdit,
			&QLineEdit::textChanged,
			this,
			&MACCtrl::itemTextChanged);

		connect(pEdit, SIGNAL(textEdited(const QString &)), SLOT(toUpper(const QString &)));

		pLayout->addWidget(pEdit);
		pLayout->setStretch(pLayout->count(), 1);

		pEdit->setFrame(false);
		pEdit->setAlignment(Qt::AlignCenter);

		QFont font = pEdit->font();
		font.setStyleHint(QFont::Monospace);
		font.setFixedPitch(true);
		pEdit->setFont(font);

		pEdit->setValidator(new MACItemValidator(pEdit));
		pEdit->setMaxLength(2);
	}

	setMaximumWidth(30 * QTUTL_MAC_SIZE);

	connect(this, SIGNAL(signalTextChanged(QLineEdit*)),
		this, SLOT(slotTextChanged(QLineEdit*)),
		Qt::QueuedConnection);
}

MACCtrl::~MACCtrl()
{

}

void MACCtrl::toUpper(const QString &text)
{
	QLineEdit *pEdit = qobject_cast<QLineEdit *>(sender());
	if (!pEdit)
		return;

	int pos = pEdit->cursorPosition();

	for (unsigned int i = 0; i != QTUTL_MAC_SIZE; ++i)
	{
		if (pEdit == m_pLineEdit[i])
		{
			int pos = pEdit->cursorPosition();
			if (pEdit->text().size() == (int)getMACItemStr(UCHAR_MAX).size() &&
				pEdit->text().size() == pEdit->cursorPosition())
			{
				// auto-move to next item
				if (i + 1 != QTUTL_MAC_SIZE)
				{
					m_pLineEdit[i + 1]->setFocus();
					m_pLineEdit[i + 1]->selectAll();
				}
			}
		}
	}

	QString upperText = text.toUpper();
	if (upperText != text)
	{
		pEdit->setText(upperText);
		pEdit->setCursorPosition(pos);
	}
}

QString MACCtrl::MAC() const
{
	int i;
	QString ip;

	for (i = 0; i < QTUTL_MAC_SIZE - 1; i++)
	{
		QString ipItem = m_pLineEdit[i]->text();
		ip += !ipItem.isEmpty() ? ipItem : "00";
		ip += ':';
	}
	ip += m_pLineEdit[i]->text();

	return ip;
}

void MACCtrl::setMAC(QString const& ip)
{
	int i;
	QStringList ipItems = ip.split(':');
	int count = QTUTL_MAC_SIZE;

	if (count > ipItems.length())
	{
		count = ipItems.length();
	}

	for (i = 0; i < count; i++)
	{
		int pos;
		QString ipItem = ipItems[i];
		const QValidator *validator = m_pLineEdit[i]->validator();

		if (validator->validate(ipItem, pos) != QValidator::Acceptable)
		{
			validator->fixup(ipItem);
		}

		m_pLineEdit[i]->setText(ipItem);
	}

	for (; i < QTUTL_MAC_SIZE; i++)
	{
		m_pLineEdit[i]->setText("00");
	}

	emit textChanged(MAC());
}

QString MACCtrl::getMACItemStr(unsigned char item)
{
	QString s;
	s.sprintf("%02X", item);
	return s;
}

void MACCtrl::slotTextChanged(QLineEdit* pEdit)
{

}

void MACCtrl::itemTextChanged(const QString &text)
{
	(void)text;
	emit textChanged(MAC());
}

bool MACCtrl::eventFilter(QObject *obj, QEvent *event)
{
	bool bRes = baseClass::eventFilter(obj, event);

	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* pEvent = dynamic_cast<QKeyEvent*>(event);
		if (pEvent)
		{
			for (unsigned int i = 0; i != QTUTL_MAC_SIZE; ++i)
			{
				QLineEdit* pEdit = m_pLineEdit[i];
				if (pEdit == obj)
				{
					switch (pEvent->key())
					{
					case Qt::Key_Left:
					{
						if (pEdit->cursorPosition() == 0)
						{
							// user wants to move to previous item
							if (i != 0)
							{
								m_pLineEdit[i - 1]->setFocus();
								m_pLineEdit[i - 1]->setCursorPosition(m_pLineEdit[i - 1]->text().size());
							}
						}
						break;
					}
					case Qt::Key_Right:
					{
						if (pEdit->text().isEmpty() ||
							(pEdit->text().size() == pEdit->cursorPosition()))
						{
							// user wants to move to next item
							if (i + 1 != QTUTL_MAC_SIZE)
							{
								m_pLineEdit[i + 1]->setFocus();
								m_pLineEdit[i + 1]->setCursorPosition(0);
							}
						}
						break;
					}
					case Qt::Key_Shift:
					{
						break;
					}
					default:
					{
						emit signalTextChanged(pEdit);
					}
					}

					break;
				}
			}
		}
	}

	return bRes;
}
