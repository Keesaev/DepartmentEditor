import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as OldControls
import XmlEditor 1.1
import TreeModel 1.1

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    XmlEditor{
        id: xmlEditor

    }

    OldControls.TreeView{
        anchors.fill: parent
        model: treeModel
        OldControls.TableViewColumn{
            title: "Name"
            role: "name"
            width: 200
        }
    }

    TreeModel{
        id: treeModel
        roles: ["name"]

        TreeNode{
            property string name: "Дизайнерский отдел"
            nodes: [
                TreeNode{
                    property string name: "Сотрудники"

                    nodes: [
                        TreeNode{
                            property string name: "Сотрудник"
                            nodes:[
                                TreeNode{
                                    property string name: "Иванов"
                                },
                                TreeNode{
                                    property string name: "Иван"
                                },
                                TreeNode{
                                    property string name: "Иванович"
                                },
                                TreeNode{
                                    property string name: "Руководитель"
                                },
                                TreeNode{
                                    property string name: "10000"
                                }
                            ]
                        },
                        TreeNode{
                            property string name: "Сотрудник"
                            nodes:[
                                TreeNode{
                                    property string name: "Иванов"
                                },
                                TreeNode{
                                    property string name: "Иван"
                                },
                                TreeNode{
                                    property string name: "Иванович"
                                },
                                TreeNode{
                                    property string name: "Руководитель"
                                },
                                TreeNode{
                                    property string name: "10000"
                                }
                            ]
                        }
                    ]
                }

            ]
        }

    }
}
