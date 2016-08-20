#ifndef ZSETTINGSVIEW_H
#define ZSETTINGSVIEW_H

#include <QObject>

class ZSettings;

class ZSettingsView : public QObject
{
    Q_OBJECT
public:
    explicit ZSettingsView(QObject *parent = 0);

    virtual void draw(ZSettings *settings) = 0;

protected:
    void emitUpdated(const QString& key, const QVariant& value);

signals:
    void updated(const QString& key, const QVariant& value);

public slots:
};

#endif // ZSETTINGSVIEW_H
