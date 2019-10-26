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
        const QString driver {"QSQLLITE"};
    }

}
