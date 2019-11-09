#pragma once
#include "ConnectionManager.h"
#include "dbtypes.h"
#include <QSqlQuery>
#include <QVariantList>

namespace db
{
class Executor
{
public:
    Executor();
    Q_DISABLE_COPY(Executor);

    std::pair<DBResult,
        QSqlQuery> execute(const QString & queryText, const QVariantList & args = {});
private:
    ConnectionManager & m_connectionManger;

};
}
