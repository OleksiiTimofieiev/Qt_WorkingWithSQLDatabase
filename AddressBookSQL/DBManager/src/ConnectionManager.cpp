#include "ConnectionManager.h"
#include <iostream>

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
            return false;
        }
        //1:26:36
    };

    bool ConnectionManager::ConnectionManagerPrivate::setUpWorkSpace()
    {
#ifdef BUILD_TESTS
        static const QString dataBaseName{"TestDB"};
#else
        static const QString dataBaseName{"ContactsDB"};
#endif
        const QString location{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};
        const QString fullPath {location + "/" + dataBaseName}; //+.db

        dbPath = fullPath.toStdString();

        QDir dbDirectory {location};

        if (!dbDirectory.exists())
        {
            const bool creationResult {dbDirectory.mkpath(location)};

            qInfo() << "DB directory does not exists" << creationResult;
        }

        qDebug() << "data path" << fullPath;

        return dbDirectory.exists();
    }

}
