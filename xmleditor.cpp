#include "xmleditor.h"

XmlEditor::XmlEditor(QObject *parent) : QObject(parent)
{

}

void XmlEditor::readXml(QString path, TreeModel *model){
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QIODevice::Text)){
        qDebug() << "Couldn't open file\n";
        return;
    }
    QDomDocument document;
    if(!document.setContent(&file)){
        qDebug() << "Couldn't open file\n";
        file.close();
        return;
    }

    QDomElement rootElement = document.firstChildElement();
    traverseRead(rootElement, nullptr, model);

    file.close();
}

void XmlEditor::writeXml(QString path){

}

void XmlEditor::traverseRead(QDomElement rootElement, TreeNode *parentNode, TreeModel *model){
    for(QDomNode n = rootElement.firstChildElement(); !n.isNull(); n = n.nextSibling()){
        if(n.isElement()){
            QDomElement element = n.toElement();
            if(element.tagName() == "department"){
                TreeNode *node = new TreeNode(element.attribute("name"), element.tagName());
                traverseRead(element, node, model);
                model->appendNode(node, parentNode);
            }
            else if(element.tagName() == "employments"){
                TreeNode *node = new TreeNode("Сотрудники", element.tagName(), parentNode);
                traverseRead(element, node, model);
                parentNode->appendNode(node);
            }
            else if(element.tagName() == "employment"){
                TreeNode *node = new TreeNode("Сотрудник", element.tagName(), parentNode);
                traverseRead(element, node, model);
                parentNode->appendNode(node);
            }
            else{
                TreeNode *node = new TreeNode(element.text(), element.tagName(), parentNode);
                parentNode->appendNode(node);
            }
        }
    }
}

