import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Dialog{
    id: dialog
    title: "Введите данные"
    width: 400
    height: 200

    signal accepted(var input)
    signal declined()
    property string defaultText: "Название"

    contentItem: Rectangle{
        anchors.fill: parent
        Rectangle{
            id: textRect
            width: parent.width; height: parent.height * 0.7
            anchors{
                left: parent.left
                right: parent.right
                top: parent.top
            }
            Rectangle{
                width: 100; height: 30
                anchors.centerIn: parent
                border.color: "grey"
                border.width: 1
                TextInput{
                    id: textInput
                    text: defaultText
                    anchors{
                        centerIn: parent
                    }
                }
            }
        }
        Rectangle{
            id: buttonsRect
            anchors{
                left: parent.left
                right: parent.right
                top: textRect.bottom
                bottom: parent.bottom
            }
            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Button{
                    text: "Ок"
                    onClicked: {
                        close()
                        accepted(textInput.text)
                    }
                }
                Button{
                    text: "Отмена"
                    onClicked: {
                        close()
                        declined()
                    }
                }
            }
        }
    }
}
