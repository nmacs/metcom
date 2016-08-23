#ifndef ZSETTINGS_H
#define ZSETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QList>

class ZSettingsView;

class ZSettings : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, QVariant> Map;

    explicit ZSettings(QObject *parent = 0);

    static const ZSettings& defaultSettings();

    void operator=(ZSettings const& other);

    bool save(const QString& file);
    bool load(const QString& file);

    void setValues(const Map& values);
    void setValue(const QString& key, const QVariant& value);
    QVariant const& value(const QString& key, const QVariant &def = QVariant()) const;

    void clear();

    const Map& values() const { return m_values; }

    void addView(ZSettingsView* view);

signals:

public slots:
    void update(ZSettingsView *sender, const QString& key, const QVariant& value);

private:
    void drawViews(ZSettingsView *except = 0);

private:
    Map m_values;
    QList<ZSettingsView*> m_views;
};

#endif // ZSETTINGS_H
