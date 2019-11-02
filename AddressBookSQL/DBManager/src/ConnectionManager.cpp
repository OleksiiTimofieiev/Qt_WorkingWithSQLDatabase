#include "ConnectionManager.h"
#include <iostream>

namespace db
{

namespace
{
    class DBCloser
    {
        public:
            void operator()(QSqlDatabase * db)
            {
                db->close();
                QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
                delete db;
            }
    };
}
    struct ConnectionManager::ConnectionManagerPrivate
    {
        std::unique_ptr<QSqlDatabase, DBCloser> database;
        QString dbPath;
        bool isValid{true};
        DBState state {DBState::OK};

        bool setUp(void);
        bool setUpWorkSpace(void);
        bool setUpTables(void);
    };

    ConnectionManager::~ConnectionManager()
    {
    }

    ConnectionManager & ConnectionManager::instance()
    {
        static ConnectionManager instance;
        return instance;
    };

    ConnectionManager::ConnectionManager()
        : m_d {new ConnectionManagerPrivate{} }
    {
        const bool setupResult{m_d->setUp()};

        m_d->isValid = setupResult;
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
        database.reset(new QSqlDatabase {QSqlDatabase::addDatabase(driver)}) ;
        database->setDatabaseName(dbPath);

        qDebug() << "Database name: " <<database->databaseName();

        if(!database->open())
        {
            state = DBState::ERROR_OPENING;
            qCritical() << "Error i opening DB" << database->databaseName()
                        << "reason" << database->lastError();
            return false;
        }
        return setUpTables();
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

        dbPath = fullPath;

        QDir dbDirectory {location};

        if (!dbDirectory.exists())
        {
            const bool creationResult {dbDirectory.mkpath(location)};

            qInfo() << "DB directory does not exists" << creationResult;
        }

        qDebug() << "data path" << fullPath;

        return dbDirectory.exists();
    }

    bool ConnectionManager::ConnectionManagerPrivate::setUpTables()
    {
        bool result{true};

        std::vector<QSqlQuery> creationQuaries {
            QSqlQuery  {
                "CREATE TABLE IF NOT EXISTS Contacts"
                "("
                "Name TEXT,"
                "Surname TEXT"
                "PhoneNumber Text"
                "UNIQUE(Name,Surname)"
                ")"
            }
        };

        for (auto & query : creationQuaries)
        {
            if (query.exec())
            {
                result = false;
                state = DBState::ERROR_TABLES;
                qDebug() << "Table creation failed:" << query.lastError() << query.result();
            }
            else
            {
                qInfo() << "Table successfully created";
            }
        }
        return  result;

    }

}
