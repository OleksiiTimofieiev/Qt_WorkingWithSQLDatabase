import QtQuick 2.0
import ContactsModule.Base 1.0
import StyleSettings 1.0
import ResourceProvider 1.0


// syntax for inheritance
BaseListDelegate {
    // positioning option like anchors
    id: root

    ImageBubble {
        id: _contactBubble;
        anchors.left: root.left
        anchors.leftMargin: Style.defaultOffset
        anchors.verticalCenter: root.verticalCenter
        width: root.height - 15
        height: root.height - 15
        image.source: Resources.contacts.defaultContactItem
    }

    Column {
        // positioning:
        anchors.verticalCenter: root.verticalCenter
        anchors.left: _contactBubble.right
        anchors.leftMargin: Style.defaultOffset

        Row {
            spacing: Style.smallSpacing
            // roles
            BaseText {
                text: name
            }
            BaseText {
                text: surname
            }
        }
        BaseText {
            text: "+" + phoneNumber
            color:  Style.primaryColor
        }
    }
}
