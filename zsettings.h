#ifndef ZSETTINGS_H
#define ZSETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMap>

class ZSettingsView;

class ZSettings : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, QVariant> Map;

    explicit ZSettings(QObject *parent = 0);

    void operator=(ZSettings const& other);

    bool save(const QString& file);
    bool load(const QString& file);

    void setValues(const Map& values);
    void setValue(const QString& key, const QVariant& value);
    QVariant const& value(const QString& key, const QVariant &def = QVariant()) const;

    void clear();

    const Map& values() const { return m_values; }

    void setView(ZSettingsView* view);

signals:

public slots:
    void update(const QString& key, const QVariant& value);

private:
    Map m_values;
    ZSettingsView *m_view;
};

#endif // ZSETTINGS_H
