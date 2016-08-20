#ifndef ZFIRMWAREUPGRADE_H
#define ZFIRMWAREUPGRADE_H

#include <QObject>
#include "zprotocol.h"

class ZFirmwareUpgrade : public ZProtocol
{
    Q_OBJECT
public:
    explicit ZFirmwareUpgrade(ZChannel *channel = 0, QObject *parent = 0);

    void setFirmwareFile(const QString &file);
    void setResetConfiguration(bool value);

    virtual bool run();

signals:

public slots:

private:
    QString m_firmwareFile;
    bool m_resetConfiguration;
    QProgressBar *m_progress;
};

#endif // ZFIRMWAREUPGRADE_H
