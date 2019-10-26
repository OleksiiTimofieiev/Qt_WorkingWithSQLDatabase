#include "contactsreader.h"

namespace
{
    const std::vector<Contact> mockData {
        {"Wylie", "Johms", "1"},
        {"Wylie", "Johms", "2"},
        {"Wylie", "Johms", "3"}

    };
}

std::pair<bool, std::vector<Contact> > ContactsReader::requestContactsBrowse(void)
{
    return std::make_pair(true, mockData);
}
