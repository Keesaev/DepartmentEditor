import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

// Диалог с введением нескольких строк
Dialog{
    id: dialog
    title: "Введите данные"
    width: 400
    height: 300

    signal accepted(var input)
    signal declined()

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
            Column{
                spacing: 1
                anchors.horizontalCenter: parent.horizontalCenter
                InputRow{ id: surnameInput; defaultText: "Иванов"; helpText: "Фамилия" }
                InputRow{ id: nameInput; defaultText: "Иван"; helpText: "Имя" }
                InputRow{ id: middleNameInput; defaultText: "Иванович"; helpText: "Отчество" }
                InputRow{ id: functionInput; defaultText: "Директор"; helpText: "Должность" }
                InputRow{ id: salaryInput; defaultText: "100000"; helpText: "Зарплата"; textValidator: IntValidator{ bottom: 0 } }
                Component.onCompleted: {
                    //  salaryInput.setIntOnly()
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
                        var a = [
                            surnameInput.getText(),
                            nameInput.getText(),
                            middleNameInput.getText(),
                            functionInput.getText(),
                            salaryInput.getText()
                        ]
                        accepted(a)
                        close()
                    }
                }
                Button{
                    text: "Отмена"
                    onClicked: {
                        declined()
                        close()
                    }
                }
            }
        }
    }
}
