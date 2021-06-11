#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QObject>
#include <QtQml>
#include <QtXml>
#include <QFile>
#include <QDebug>
#include <treemodel.h>
#include <treenode.h>

class XmlEditor : public QObject
{
    QML_ELEMENT
    Q_OBJECT
    void traverseRead(QDomElement rootElement, TreeNode *parentNode, TreeModel *model);
public:
    explicit XmlEditor(QObject *parent = nullptr);
    Q_INVOKABLE void readXml(QString path, TreeModel *model);
    Q_INVOKABLE void writeXml(QString path);
signals:

};

#endif // XMLEDITOR_H
