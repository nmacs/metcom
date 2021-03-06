#ifndef ZSETTINGS_H
#define ZSETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QList>
#include <QValidator>

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
    void setValidator(QValidator *validator);
    QVariant const& value(const QString& key, const QVariant &def = QVariant()) const;

	void redraw();
    void clear();
	void setLocked(bool value) { m_locked = value; }

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
	bool m_locked;
};

#endif // ZSETTINGS_H
