#pragma once
#include <memory>
//#include <QObject>
#include <string>
#include "dbtypes.h"
#include <QString>
#include <QSqlDatabase>


// use of deep pointer:
namespace db
{

class ConnectionManager
{
    public:
//        Q_DISABLE_COPY(ConnectionManager);
        ConnectionManager(const ConnectionManager&) = delete;
        ConnectionManager & operator=(const ConnectionManager&) = delete;

        static ConnectionManager & instance();

    private:
        ConnectionManager();
        struct ConnectionManagerPrivate;
        std::unique_ptr<ConnectionManagerPrivate> m_d;
};

}
