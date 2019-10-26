#include "contactsmodel.h"

ContactsModel::ContactsModel()
{
    const bool updateResult {updateContacts()};

    if (!updateResult)
    {
        qWarning() << "Update contacts failed.";
    }

}

void ContactsModel::registerMe(const std::string &moduleName)
{
    qmlRegisterType<ContactsModel>(moduleName.c_str(), 1, 0, "ContactsModel");
}


// Qt will know with which value has the role name for date method
QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ContactRoles::NameRole] = "name";
    roles[ContactRoles::SurnameRole] = "surname";
    roles[ContactRoles::PhoneNumberRole] = "phoneNumber";

    return roles;

}

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent) // cast to void

    return static_cast<int>(m_contacts.size());
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > rowCount(index))
       return {};

    // get element of the row

    const Contact & contact {m_contacts.at(index.row())};

    switch (role)
    {
        case ContactRoles::NameRole: {
            return QVariant::fromValue(contact.firstName());
             }
        case ContactRoles::SurnameRole: {
            return QVariant::fromValue(contact.surname());
            }
        case ContactRoles::PhoneNumberRole: {
            return QVariant::fromValue(contact.phone());
            }
        default: {
            return true;
        }
    }
}

bool ContactsModel::updateContacts()
{
    bool requestResult{false};

    std::vector<Contact> contactsResult;


    // to avoid first and second
    std::tie(requestResult, contactsResult) = m_contactsReader.requestContactsBrowse();

    if (requestResult)
    {
        m_contacts.swap(contactsResult);
        // notify that data changed
        emit dataChanged(createIndex(0,0), createIndex(m_contacts.size(), 0));
    }
    return requestResult;
}
