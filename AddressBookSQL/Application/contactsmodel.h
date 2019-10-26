#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "contact.h"
#include "contactsreader.h"
#include <QQmlEngine> // to register model
#include <QDebug>


class ContactsModel : public QAbstractListModel
{
    Q_OBJECT // to enable MOC compiler

public:
    ContactsModel();

    static void registerMe(const std::string & moduleName);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = {}) const override;
    // for any type of data
    QVariant data(const QModelIndex & index ={}, int role = Qt::DisplayRole) const override;

private:
    ContactsReader m_contactsReader;
    std::vector<Contact> m_contacts;

    enum ContactRoles {
        NameRole = Qt::UserRole + 1, //0x0100 + 1
        SurnameRole,
        PhoneNumberRole
    };

    bool updateContacts(void);
};

#endif // CONTACTSMODEL_H
