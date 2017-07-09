#include "zsettingstable.h"
#include "zsettings.h"
#include <QDebug>

ZSettingsTable::ZSettingsTable(QTableView* table, QObject *parent)
    : ZSettingsView(parent),
      m_table(table),
	  m_internalEdit(false)
{
    m_model = new QStandardItemModel(0, 1, this);
    m_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Value")));

    connect(m_model, &QStandardItemModel::itemChanged,
            this, &ZSettingsTable::itemChanged);

    m_table->setModel(m_model);
}

void ZSettingsTable::draw(ZSettings *settings)
{
    ZSettings::Map map = settings->values();
    ZSettings::Map::iterator item;
	int lastUpdatedRow = -1;

	QList<QString> keysToRemove;

	m_internalEdit = true;

	int rowCount = m_model->rowCount();
	for (int i = 0; i < rowCount; i++)
	{
		keysToRemove.append(m_model->verticalHeaderItem(i)->text());
	}

    for (item = map.begin(); item != map.end(); item++)
    {
		int row = -1;

		for (int i = 0; i < m_model->rowCount(); i++)
		{
			if (m_model->verticalHeaderItem(i)->text() == item.key())
			{
				row = i;
				break;
			}
		}

		if (row >= 0)
		{
			QString oldText = m_model->item(row, 0)->text();

			if (oldText != item.value().toString())
			{
				m_model->item(row, 0)->setText(item.value().toString());
				lastUpdatedRow = row;
			}
		}
		else
		{
			m_model->appendRow(new QStandardItem(item.value().toString()));
			m_model->setVerticalHeaderItem(m_model->rowCount() - 1, new QStandardItem(item.key()));
		}

		keysToRemove.removeAll(item.key());
    }

	if (lastUpdatedRow >= 0)
	{
		m_table->selectRow(lastUpdatedRow);
	}

    m_model->sort(1);

	m_internalEdit = false;
}

void ZSettingsTable::itemChanged(QStandardItem *item)
{
	if (m_internalEdit)
		return;

    QString key = m_model->verticalHeaderItem(item->row())->text();
    QString value = item->text();
    emitUpdated(key, value);
}
