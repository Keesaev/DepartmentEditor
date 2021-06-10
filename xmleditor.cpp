#include "xmleditor.h"

XmlEditor::XmlEditor(QObject *parent) : QObject(parent)
{

}

void XmlEditor::readXml(QString path){
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
    traverse(rootElement);

    file.close();
}

void XmlEditor::writeXml(QString path){

}

void XmlEditor::traverse(QDomElement rootElement){
    for(QDomNode n = rootElement.firstChildElement(); !n.isNull(); n = n.nextSibling()){
        if(n.isElement()){
            QDomElement element = n.toElement();
            if(!element.text().isEmpty()){
                qDebug() << element.text();
            }
            if(!element.firstChildElement().isNull())
                traverse(element);
        }
    }
}

void XmlEditor::getAttributes(QDomElement rootElement, QString tag, QStringList attributes){
    QDomNodeList nodes = rootElement.elementsByTagName(tag);

    for(int i = 0; i < nodes.count(); i++){
        QDomNode node = nodes.at(i);
        if(node.isElement()){
            QDomElement element = node.toElement();
            for(auto i : attributes){
                qDebug() << element.attribute(i);
            }
        }
    }
}
