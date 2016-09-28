#include "zcommlog.h"

ZCommLog::ZCommLog(QTextBrowser *view, QObject *parent) :
    QObject(parent),
    m_view(view),
    m_directionEmpty(true)
{
}

void ZCommLog::log(const QByteArray &block, ZCommLog::Direction dir)
{
    QString hex;
    QString ascii;

    /*  <IN>:
     * 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  ................
     *
     * <OUT>:
     * 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  ................
     */

    if (m_directionEmpty || m_direction != dir)
    {
        m_directionEmpty = false;
        m_direction = dir;
        m_view->append(m_direction == LOG_INPUT ? tr("<IN>:") : tr("<OUT>:"));
    }

    for (int i = 0; i < block.length(); i++)
    {
        char byte = block.at(i);
        hex += QString::asprintf("%02X ", (unsigned char)byte);
        ascii += isprint((unsigned char)byte) ? byte : '.';

        if (ascii.length() >= 16)
        {
            QString line = hex + "  " + ascii;
            m_view->append(line);
            hex.clear();
            ascii.clear();
        }
    }

    if (!hex.isEmpty())
    {
        if (hex.length() < 48)
        {
            hex = QString("%1").arg(hex, -48, QChar(' '));
        }
        QString line = hex + "  " + ascii;
        m_view->append(line);
    }
}
