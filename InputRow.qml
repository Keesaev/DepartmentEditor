import QtQuick 2.0

Row{
    width: 250; height: 35
    spacing: 10
    anchors.horizontalCenter: parent.horizontalCenter
    function getText(){
        return textInput.text
    }
    property string helpText: "Поле"
    property string defaultText: "Данные"

    Rectangle{
        id: leftRect
        width: 100; height: 30
        Text{
            text: helpText
            anchors.centerIn: parent
        }
    }
    Rectangle{
        id: rightRect
        border.color: "grey"; border.width: 1
        width: 100; height: 30

        TextInput{
            id: textInput
            text: defaultText
            width: parent.width; height: parent.height
            anchors.centerIn: parent
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
    }
}
