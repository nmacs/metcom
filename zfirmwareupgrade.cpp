#include "zfirmwareupgrade.h"
#include <QFile>

ZFirmwareUpgrade::ZFirmwareUpgrade(ZChannel *channel, Progress *progress, QObject *parent) :
    ZProtocol(channel, progress, parent)
{
}

void ZFirmwareUpgrade::setFirmwareFile(const QString &file)
{
    m_firmwareFile = file;
}

void ZFirmwareUpgrade::setResetConfiguration(bool value)
{
    m_resetConfiguration = value;
}

bool ZFirmwareUpgrade::doRun()
{
    bool res;
    QString command;

    QFile file(m_firmwareFile);
    res = file.open(QIODevice::ReadOnly);
    if (!res)
    {
        setErrorString(file.errorString());
        return false;
    }

    qint64 firmwareSize = file.size();
    if (firmwareSize > 64*1024)
    {
        setErrorString(tr("Firmware file is too large"));
        return false;
    }

    command = QString("STOP=%1\r").arg(password());
    res = execute(command, QByteArray(), true);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    msleep(500);

    command = QString("ERF=%1\r").arg(password());
    res = execute(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    if (m_resetConfiguration)
    {
        command = QString("ERS=%1\r").arg(password());
        res = execute(command);
        if (!res)
        {
            setErrorString(channel()->errorString());
            return false;
        }
    }

    qint64 bytesSent = 0;
    int blockNumber = 0;
    while (!file.atEnd())
    {
        char block[513];
        memset(block, 0xFF, sizeof(block) - 1);
        command = QString("BLK=%1;%2;").arg(password()).arg(blockNumber, 3, 10, QChar('0'));

        qint64 len = file.read(block, sizeof(block) - 1);
        if (len < 0)
        {
            setErrorString(file.errorString());
            file.close();
            return false;
        }
        else if (len == 0)
        {
            break;
        }
        else
        {
            unsigned char sum = 0;
            for (int i = 0; i < sizeof(block) - 1; i++)
            {
                sum += (unsigned char)block[i];
            }
            block[512] = (char)sum;

            res = execute(command, QByteArray(block, sizeof(block)));
            if (!res)
            {
                setErrorString(file.errorString());
                file.close();
                return false;
            }

            bytesSent += sizeof(block) - 1;
            reportProgress((double)bytesSent / firmwareSize, tr("Firmware Upgrade..."));
        }

        blockNumber += 1;
    }
    file.close();

    command = QString("ENF=%1\r").arg(password()).toUtf8();
    res = execute(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        return false;
    }

    return true;
}
