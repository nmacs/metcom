#include "zsettingstable.h"
#include "zsettings.h"
#include <QDebug>

ZSettingsTable::ZSettingsTable(QTableView* table, QObject *parent)
    : ZSettingsView(parent),
      m_table(table)
{
    m_model = new QStandardItemModel(0, 1, this);
    m_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Value")));

    connect(m_model, &QStandardItemModel::itemChanged,
            this, &ZSettingsTable::itemChanged);

    m_table->setModel(m_model);
}

void ZSettingsTable::draw(ZSettings *settings)
{
    const ZSettings::Map& map = settings->values();
    ZSettings::Map::const_iterator item;
    m_model->clear();
    for (item = map.cbegin(); item != map.cend(); item++)
    {
        m_model->appendRow(new QStandardItem(item.value().toString()));
        m_model->setVerticalHeaderItem(m_model->rowCount() - 1, new QStandardItem(item.key()));
    }

    m_model->sort(1);
}

void ZSettingsTable::itemChanged(QStandardItem *item)
{
    QString key = m_model->verticalHeaderItem(item->row())->text();
    QString value = item->text();
    emitUpdated(key, value);
}
