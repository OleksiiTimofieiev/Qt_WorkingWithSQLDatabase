#include "contact.h"




Contact::Contact( QString  firstName, QString  secondName, QString phone)
    : m_phone{std::move(phone)},
      m_firstName{std::move(firstName)},
      m_surname{std::move(secondName)}
{

}

QString Contact::phone() const
{
    return m_phone;
}

QString Contact::firstName() const
{
    return m_firstName;
}

QString Contact::surname() const
{
    return m_surname;
}
