#ifndef ZPASSWORDCHANGE_H
#define ZPASSWORDCHANGE_H

#include "zprotocol.h"

class ZPasswordChange : public ZProtocol
{
    Q_OBJECT
public:
    explicit ZPasswordChange(ZChannel *channel = 0, Progress *progress = 0, QObject *parent = 0);

    virtual bool doRun();

    void setNewPassword(QString const& password);

signals:

public slots:

private:
    QString m_newPassword;
};

#endif // ZPASSWORDCHANGE_H
