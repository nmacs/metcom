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
	char checkByte = 0;

    QFile file(m_firmwareFile);
    res = file.open(QIODevice::ReadOnly);
    if (!res)
    {
        setErrorString(file.errorString());
        return false;
    }

    qint64 firmwareSize = file.size();
	QByteArray data = file.readAll();
	file.reset();

	for (int i = 0; i < data.length(); i++)
	{
		data.data()[i] ^= 0x27;
	}

	if (data.left(4) == QByteArray("2DOM", 4))
	{
		int index = data.indexOf("$$$$$");

		if (index < 0)
		{
			setErrorString(tr("Fail to read harwave version from firmware file"));
			return false;
		}

		// $$$$$09.01.C0.17
		//               ^
		QString checkByteStr(QByteArray(&data.data()[index + 14], 2));

		checkByte = checkByteStr.toInt(0, 16);
	}
	else
	{
		checkByte = data.at(500);
	}

    reportProgress(0, tr("Firmware Update..."));

    command = QString("VER=%1\r").arg(password());
    res = post(command);
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
        setErrorString(QString(tr("Unexpected Modem hardware version %1 %2")).arg(result.at(0).left(2).toUpper()).arg(QString("%1").arg(checkByte, 2, 16, QChar('0')).toUpper()));
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

			QByteArray cmd;
			cmd.append(command);
			cmd.append(block, sizeof(block));

            res = execute(cmd, 3000);
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
