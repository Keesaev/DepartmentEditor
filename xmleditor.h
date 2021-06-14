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
    void traverseRead(QDomElement rootElement, TreeNode *parentNode);
    QMap<QVariant, QVariant> annotations = {
        {"surname", "Фамилия"},
        {"name", "Имя"},
        {"middleName", "Отчество"},
        {"function", "Должность"},
        {"salary", "Зарплата"}
    };
public:
    explicit XmlEditor(QObject *parent = nullptr);
    Q_INVOKABLE void readXml(QUrl path, TreeModel *model);
    Q_INVOKABLE void writeXml(QUrl path, TreeModel *model);
signals:

};

#endif // XMLEDITOR_H
