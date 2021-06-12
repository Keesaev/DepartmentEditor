import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as OldControls
import XmlEditor 1.1
import TreeModel 1.1
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1 as Labs

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    OldControls.TreeView{
        id: treeView
        width: parent.width; height: parent.height * 0.9
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }

        model: treeModel
        OldControls.TableViewColumn{
            title: ""
            role: "name"
            width: 400
        }

        onDoubleClicked: {
            var tag = treeModel.getTagByIndex(index)
            if(tag === "department")
                departmentMenu.popup()
            else if (tag === "employments"){
                employmentsMenu.popup()
            }
            else if (tag === "employment"){
                employmentMenu.popup()
            }

            else if(tag === "surname" || tag === "name" ||
                    tag === "middleName" || tag === "function" ||
                    tag === "salary"){
                editMenu.popup()
            }
        }
    }

    // Кнопки
    Item{
        id: bottomRect
        width: parent.width; height: parent.height * 0.1
        anchors{
            left: parent.left
            right: parent.right
            top: treeView.bottom
            bottom: parent.bottom
        }
        Row{
            anchors.fill: parent
            spacing: 5
            Button{
                width: 100; height: parent.height
                text: "Добавить отдел"
                onClicked:{
                    dialogCreateDep.open()
                }
            }
            Button{
                width: 100; height: parent.height
                text: "Открыть"
                onClicked:{
                    openDialog.open()
                }
            }
            Button{
                width: 100; height: parent.height
                text: "Сохранить"
                onClicked:{
                    saveDialog.open()
                }
            }
            Button{
                width: 100; height: parent.height
                text: "Отмена"
                onClicked:{
                    history.revertState(treeModel)
                }
            }
            Button{
                width: 100; height: parent.height
                text: "Очистить"
                onClicked:{
                    treeModel.clear()
                }
            }
        }
    }

    // Диалоги

    SingleInputDialog{
        id: editDialog
        title: "Введите новое название"
        onAccepted: {
            history.saveState(treeModel)
            treeModel.editNodeData(treeView.currentIndex, input)
        }
    }

    SingleInputDialog{
        id: dialogCreateDep
        title: "Введите название отдела"

        onAccepted: {
            history.saveState(treeModel)
            treeModel.createDepartment(input);
        }
    }

    MultipleInputDialog{
        id: dialogAddEmployment
        onAccepted: {
            history.saveState(treeModel)
            treeModel.createEmployment(treeView.currentIndex, input)
        }
    }

    // При открытии файла очищаем текущую модель и историю операций
    Labs.FileDialog{
        id: openDialog
        fileMode: Labs.FileDialog.OpenFile
        nameFilters: ["XML files (*.xml)"]
        onAccepted: {
            treeModel.clear()
            history.clear()
            xmlEditor.readXml(file, treeModel)
            close()
        }
        onRejected: {
            close()
        }
    }

    Labs.FileDialog{
        id: saveDialog
        fileMode: Labs.FileDialog.SaveFile
        defaultSuffix: "xml"
        onAccepted: {
            xmlEditor.writeXml(file, treeModel)
            close()
        }
        onRejected: {
            close()
        }
    }

    // Всплывающие меню

    Menu{
        id: departmentMenu
        MenuItem
        {
            text: "Переименовать отдел"
            onTriggered: {
                editDialog.open()
            }
        }
        MenuItem
        {
            text: "Удалить отдел"
            onTriggered: {
                history.saveState(treeModel)
                treeModel.removeNode(treeView.currentIndex);
            }
        }
    }

    Menu{
        id: employmentsMenu

        MenuItem
        {
            text: "Добавить сотрудника"
            onTriggered: {
                dialogAddEmployment.open()
            }
        }
    }

    Menu{
        id: employmentMenu

        MenuItem{
            text: "Удалить сотрудника"
            onTriggered: {
                history.saveState(treeModel)
                treeModel.removeNode(treeView.currentIndex);
            }
        }
    }

    Menu{
        id: editMenu

        MenuItem
        {
            text: "Изменить"
            onTriggered: {
                editDialog.open()
            }
        }
    }

    TreeModel{
        id: treeModel
    }

    History{
        id: history
    }

    XmlEditor{
        id: xmlEditor
    }
}
