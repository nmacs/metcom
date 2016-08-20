#ifndef ZCOMMLOG_H
#define ZCOMMLOG_H

#include <QObject>
#include <QTextBrowser>

class ZCommLog : public QObject
{
    Q_OBJECT
public:
    enum Direction
    {
        LOG_INPUT,
        LOG_OUTPUT
    };

    explicit ZCommLog(QTextBrowser *view, QObject *parent = 0);

    void log(QByteArray const& block, Direction dir);

signals:

public slots:

private:
    QTextBrowser *m_view;
    bool m_directionEmpty;
    Direction m_direction;
};

#endif // ZCOMMLOG_H
