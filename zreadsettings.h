#ifndef ZREADSETTINGS_H
#define ZREADSETTINGS_H

#include <QObject>
#include "zprotocol.h"
#include "zsettings.h"

class ZReadSettings : public ZProtocol
{
    Q_OBJECT
public:
    ZReadSettings(ZChannel *channel = 0, QObject *parent = 0);

    ZSettings const& settings() const { return m_settings; }

    virtual bool run();

private:
    ZSettings m_settings;
};

#endif // ZREADSETTINGS_H
