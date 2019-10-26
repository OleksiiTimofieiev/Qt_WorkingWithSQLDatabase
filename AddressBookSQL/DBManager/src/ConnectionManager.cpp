#include "ConnectionManager.h"

namespace db
{
    struct ConnectionManager::ConnectionManagerPrivate
    {
        std::string dbPath;
        bool isValid{true};
        DBState state {DBState::OK};

        bool setUp(void);
        bool setUpWorkSpace(void);
        bool setUpTables(void);
    };

    ConnectionManager & ConnectionManager::instance()
    {
        static ConnectionManager instance;
        return instance;
    };

    ConnectionManager::ConnectionManager()
        : m_d {new ConnectionManagerPrivate{} }
    {
    }

    bool ConnectionManager::ConnectionManagerPrivate::setUp()
    {
        static const QString driver {"QSQLLITE"};

        if (!QSqlDatabase::isDriverAvailable(driver))
        {
            state = DBState::ERROR_NO_DRIVER;
            qCritical() << "Driver" << driver << "not available";
            return false;
        }
        if (!setUpWorkSpace())
        {
            state = DBState::ERROR_WORKSPACE;
            qCritical() << "Workspace setup failed";
        }
    }

    bool ConnectionManager::ConnectionManagerPrivate::setUpWorkSpace()
    {
        1:18:17
    }

}
