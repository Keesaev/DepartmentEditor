#include "xmleditor.h"

XmlEditor::XmlEditor(QObject *parent) : QObject(parent)
{
}

// Парсим .xml файл и записываем в модель
void XmlEditor::readXml(QUrl path, TreeModel *model){
    QFile file(path.toLocalFile());
    if(!file.open(QFile::ReadOnly | QIODevice::Text)){
        qDebug() << "Не удалось открыть файл\n";
        return;
    }
    QDomDocument document;
    if(!document.setContent(&file)){
        qDebug() << "Не удалось открыть файл\n";
        file.close();
        return;
    }

    QDomElement rootElement = document.firstChildElement();
    TreeNode *rootNode = new TreeNode();
    traverseRead(rootElement, rootNode);
    model->resetRoot(rootNode);
    rootNode->clear();
    delete rootNode;

    file.close();
}

// Рекурсивный метод, читающий ноды по корневому элементу rootElement, и записывающий элементы в parentNode
void XmlEditor::traverseRead(QDomElement rootElement, TreeNode *parentNode){
    for(QDomNode n = rootElement.firstChildElement(); !n.isNull(); n = n.nextSibling()){
        if(n.isElement()){
            QDomElement element = n.toElement();
            if(element.tagName() == "department"){
                TreeNode *node = new TreeNode(element.attribute("name"), element.tagName(), parentNode);
                traverseRead(element, node);
                parentNode->appendChild(node);
            }
            else if(element.tagName() == "employments"){
                TreeNode *node = new TreeNode("Сотрудники", element.tagName(), parentNode);
                traverseRead(element, node);
                parentNode->appendChild(node);
            }
            else if(element.tagName() == "employment"){
                TreeNode *node = new TreeNode("Сотрудник", element.tagName(), parentNode);
                traverseRead(element, node);
                parentNode->appendChild(node);
            }
            else{
                TreeNode *node = new TreeNode(element.text(), element.tagName(), parentNode);
                parentNode->appendChild(node);
            }
        }
    }
}

// Составляем QDomDocument из модели и записываем в файл .xml
void XmlEditor::writeXml(QUrl path, TreeModel *model){
    QDomDocument document;
    QDomElement root = document.createElement("departments");
    TreeNode *rootNode = model->getRootNode();

    for(int i = 0; i < rootNode->count(); i++){
        TreeNode *department = rootNode->getChild(i);
        TreeNode *employments = department->getChild(0);
        QDomElement departmentElement = document.createElement("department");
        QDomElement employmentsElement = document.createElement("employments");
        departmentElement.setAttribute("name", department->getData().toString());

        for(int j = 0; j < employments->count(); j++){
            TreeNode *employment = employments->getChild(j);
            QDomElement employementElement = document.createElement("employment");
            for(int k = 0; k < employment->count(); k++){
                TreeNode *leaf = employment->getChild(k);
                QDomElement leafElement = document.createElement(leaf->getTag().toString());
                QDomText text = document.createTextNode(leaf->getData().toString());
                leafElement.appendChild(text);
                employementElement.appendChild(leafElement);
            }
            employmentsElement.appendChild(employementElement);
        }
        root.appendChild(departmentElement);
        departmentElement.appendChild(employmentsElement);
    }
    document.appendChild(root);

    QFile file(path.toLocalFile());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Не удалось открыть файл";
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << document.toString();
    file.close();
}

