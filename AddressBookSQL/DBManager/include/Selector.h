#pragma once

#include "dbtypes.h"
#include <QString>
#include <vector>
#include <QVariantList>
#include "Executor.h"

namespace db
{
class Selector
{
public:
    DBResult selectAll(const QString & tableName,
                       std::vector<QVariantList> & returnData);
private:
    Executor m_executor;

    QString generateQuery(const QString & tableName) const;
};
}
