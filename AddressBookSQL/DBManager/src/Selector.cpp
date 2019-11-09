#include "Selector.h"
#include <QSqlQuery>
#include <QSqlRecord>

namespace db
{
    DBResult Selector::selectAll(const QString & tableName, std::vector<QVariantList> & returnData)
    {
        QString query {generateQuery(tableName)};

        DBResult result;

        QSqlQuery resultQuery;

        std::tie(result, resultQuery) = m_executor.execute(query);

        if (result == DBResult::OK)
        {
            returnData.clear();
            returnData.reserve(resultQuery.size());
            while (resultQuery.next())
            {
                const QSqlRecord & entryRecord {resultQuery.record()};
                QVariantList entryData;
                entryData.reserve(entryRecord.count());

                for (int i = 0; i < entryRecord.count(); ++i)
                {
                    entryData.push_back(entryRecord.value(i));
                }

                returnData.push_back(std::move(entryData))
;            }
        }
    }

    QString Selector::generateQuery(const QString & tableName) const
    {
        QString query {"SELECT rowid, * FROM " + tableName};
        return query;
    }
}

