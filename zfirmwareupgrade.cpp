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
    qint64 bytesSent = 0;
    int blockNumber = 0;
    QStringList result;

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

    file.seek(0x500);
    char checkByte = 0;
    if (file.read(&checkByte, 1) != 1)
    {
        setErrorString(tr("Fail to read harwave version from firmware file"));
        return false;
    }
    file.reset();
    checkByte ^= 0x27;

    reportProgress(0, tr("Firmware Update..."));

    command = QString("VER=%1\r").arg(password());
    res = execute(command, QByteArray(), true);
    if (!res)
    {
        setErrorString(channel()->errorString());
        goto out;
    }

    res = readout(&result, 1);
    if (!res)
    {
        setErrorString(channel()->errorString());
        goto out;
    }

    if (result.length() != 1)
    {
        setErrorString(tr("Unable to parse Modem hardware version"));
        res = false;
        goto out;
    }

    if (result.at(0).left(2).toUpper() != QString("%1").arg(checkByte, 2, 16, QChar('0')).toUpper())
    {
        setErrorString(tr("Unexpected Modem hardware version"));
        res = false;
        goto out;
    }

    command = QString("ERF=%1\r").arg(password());
    res = execute(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        goto out;
    }

    if (m_resetConfiguration)
    {
        command = QString("ERS=%1\r").arg(password());
        res = execute(command);
        if (!res)
        {
            setErrorString(channel()->errorString());
            goto out;
        }
    }

    while (!file.atEnd())
    {
        char block[513];
        memset(block, 0xFF, sizeof(block) - 1);
        command = QString("BLK=%1;%2;").arg(password()).arg(blockNumber, 3, 10, QChar('0'));

        qint64 len = file.read(block, sizeof(block) - 1);
        if (len < 0)
        {
            setErrorString(file.errorString());
            res = false;
            goto out;
        }
        else if (len == 0)
        {
            break;
        }
        else
        {
            unsigned char sum = 0;
            for (size_t i = 0; i < sizeof(block) - 1; i++)
            {
                sum += (unsigned char)block[i];
            }
            block[512] = (char)sum;

            res = execute(command, QByteArray(block, sizeof(block)));
            if (!res)
            {
                setErrorString(file.errorString());
                goto out;
            }

            bytesSent += sizeof(block) - 1;
            reportProgress((double)bytesSent / firmwareSize);
        }

        blockNumber += 1;
    }

    command = QString("ENF=%1\r").arg(password());
    res = execute(command);
    if (!res)
    {
        setErrorString(channel()->errorString());
        goto out;
    }

out:
    file.close();

    return res;
}
