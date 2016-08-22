#include "ipctrl.h"
#include <QIntValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <strstream>
#include <QEvent>
#include <QKeyEvent>

class IPItemValidator : public QIntValidator
{
public:
    IPItemValidator(QObject* parent) : QIntValidator(parent)
    {
        setRange(0, UCHAR_MAX);
    }
    ~IPItemValidator() {}

    virtual QValidator::State validate(QString &text, int &pos) const
    {
        bool ok;
        int value = text.toInt(&ok);

        if (!ok || QString::number(value) != text)
        {
            pos = 0;
            return QValidator::Intermediate;
        }

        return QIntValidator::validate(text, pos);
    }

    virtual void fixup(QString & input) const
    {
        if (input.isEmpty())
            input = "0";
        else
        {
            bool ok;
            int value = input.toInt(&ok);
            if (ok)
            {
                if (value < 0)
                {
                    input = "0";
                }
                else if (value > UCHAR_MAX)
                {
                    input = "255";
                }
            }
            else
            {
                input = "0";
            }
        }

    }
};

IPCtrl::IPCtrl(QWidget *parent) : baseClass(parent)
{
    setFrameShape( QFrame::StyledPanel );
    setFrameShadow( QFrame::Sunken );

    QHBoxLayout* pLayout = new QHBoxLayout( this );
    setLayout( pLayout );
    pLayout->setContentsMargins( 0, 0, 0, 0 );
    pLayout->setSpacing( 0 );

    for ( int i = 0; i != QTUTL_IP_SIZE; ++i )
    {
        if ( i != 0 )
        {
            QLabel* pDot = new QLabel( ".", this );
            pDot->setStyleSheet( "background: white" );
            pLayout->addWidget( pDot );
            pLayout->setStretch( pLayout->count(), 0 );
        }

        m_pLineEdit[i] = new QLineEdit( this );
        QLineEdit* pEdit = m_pLineEdit[i];
        pEdit->installEventFilter( this );

        connect(pEdit,
                &QLineEdit::textChanged,
                this,
                &IPCtrl::itemTextChanged);

        pLayout->addWidget( pEdit );
        pLayout->setStretch( pLayout->count(), 1 );

        pEdit->setFrame( false );
        pEdit->setAlignment( Qt::AlignCenter );

        QFont font = pEdit->font();
        font.setStyleHint( QFont::Monospace );
        font.setFixedPitch( true );
        pEdit->setFont( font );

        pEdit->setValidator( new IPItemValidator( pEdit ) );
    }

    setMaximumWidth( 30 * QTUTL_IP_SIZE );

    connect( this, SIGNAL(signalTextChanged(QLineEdit*)),
             this, SLOT(slotTextChanged(QLineEdit*)),
             Qt::QueuedConnection );
}

IPCtrl::~IPCtrl()
{

}

QString IPCtrl::IP() const
{
    int i;
    QString ip;

    for (i = 0; i < QTUTL_IP_SIZE - 1; i++)
    {
        QString ipItem = m_pLineEdit[i]->text();
        ip += !ipItem.isEmpty() ? ipItem : "0";
        ip += '.';
    }
    ip += m_pLineEdit[i]->text();

    return ip;
}

void IPCtrl::setIP(QString const& ip)
{
    int i;
    QStringList ipItems = ip.split('.');
    int count = QTUTL_IP_SIZE;

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

    for (; i < QTUTL_IP_SIZE; i++)
    {
        m_pLineEdit[i]->setText("0");
    }

    emit textChanged(IP());
}

std::string IPCtrl::getIPItemStr( unsigned char item )
{
    std::strstream str;
    str << (int) item;
    str << std::ends;
    return str.str();
}

void IPCtrl::slotTextChanged( QLineEdit* pEdit )
{
    for ( unsigned int i = 0; i != QTUTL_IP_SIZE; ++i )
    {
        if ( pEdit == m_pLineEdit[i] )
        {
            if ( pEdit->text().size() == getIPItemStr( UCHAR_MAX ).size() &&
                 pEdit->text().size() == pEdit->cursorPosition() )
            {
                // auto-move to next item
                if ( i+1 != QTUTL_IP_SIZE )
                {
                   m_pLineEdit[i+1]->setFocus();
                   m_pLineEdit[i+1]->selectAll();
                }
            }
        }
    }
}

void IPCtrl::itemTextChanged(const QString &text)
{
    (void)text;
    emit textChanged(IP());
}

bool IPCtrl::eventFilter(QObject *obj, QEvent *event)
{
    bool bRes = baseClass::eventFilter(obj, event);

    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent* pEvent = dynamic_cast<QKeyEvent*>( event );
        if ( pEvent )
        {
            for ( unsigned int i = 0; i != QTUTL_IP_SIZE; ++i )
            {
                QLineEdit* pEdit = m_pLineEdit[i];
                if ( pEdit == obj )
                {
                    switch ( pEvent->key() )
                    {
                    case Qt::Key_Left:
                        {
                            if ( pEdit->cursorPosition() == 0 )
                            {
                                // user wants to move to previous item
                                if ( i != 0 )
                                {
                                    m_pLineEdit[i-1]->setFocus();
                                    m_pLineEdit[i-1]->setCursorPosition( m_pLineEdit[i-1]->text().size() );
                                }
                            }
                            break;
                        }
                    case Qt::Key_Right:
                        {
                            if ( pEdit->text().isEmpty() ||
                                 (pEdit->text().size() == pEdit->cursorPosition()) )
                            {
                                // user wants to move to next item
                                if ( i+1 != QTUTL_IP_SIZE )
                                {
                                    m_pLineEdit[i+1]->setFocus();
                                    m_pLineEdit[i+1]->setCursorPosition( 0 );
                                }
                            }
                            break;
                        }
                    default:
                        {
                            emit signalTextChanged( pEdit );
                        }
                    }

                    break;
                }
            }
        }
    }

    return bRes;
}
