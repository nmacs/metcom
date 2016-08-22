#ifndef ZWRITESETTINGS_H
#define ZWRITESETTINGS_H

#include <QObject>
#include "zprotocol.h"
#include "zsettings.h"

class ZWriteSettings : public ZProtocol
{
    Q_OBJECT
public:
    ZWriteSettings(ZChannel *channel = 0, Progress *progress = 0, QObject* parent = 0);

    void setSettings(ZSettings const& settings);

protected:
    virtual bool doRun();

private:
    ZSettings m_settings;
};

#endif // ZWRITESETTINGS_H
