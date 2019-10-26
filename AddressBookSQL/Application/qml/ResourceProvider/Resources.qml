pragma Singleton
import QtQuick 2.0

Item {
    property alias contacts: _contacts

    QtObject { //cannot keep other QObjects
        id: _contacts
        readonly property string defaultContactItem: "qrc:/qml/Resources/download.svg"
    }
}
