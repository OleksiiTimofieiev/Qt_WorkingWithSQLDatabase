#ifndef CONTACT_H
#define CONTACT_H

#include <QString>


class Contact
{
public:
    Contact() = default;

    // workaroung for rValue and lValue
    Contact(QString firstName, QString  secondName, QString phone);

    QString phone() const;

    QString firstName() const;

    QString surname() const;

private:
    QString m_phone;
    QString m_firstName;
    QString m_surname;
};

#endif // CONTACT_H
