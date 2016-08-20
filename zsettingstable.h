#ifndef ZSETTINGSTABLE_H
#define ZSETTINGSTABLE_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "zsettingsview.h"

class ZSettingsTable : public ZSettingsView
{
    Q_OBJECT
public:
    ZSettingsTable(QTableView* table, QObject *parent = 0);

    virtual void draw(ZSettings *settings);

private slots:
    void itemChanged(QStandardItem* item);

private:
    QTableView* m_table;
    QStandardItemModel *m_model;
};

#endif // ZSETTINGSTABLE_H
