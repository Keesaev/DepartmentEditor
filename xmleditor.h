#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QObject>
#include <QtQml>
#include <QtXml>
#include <QFile>
#include <QDebug>

class XmlEditor : public QObject
{
    QML_ELEMENT
    Q_OBJECT
    void getAttributes(QDomElement rootElement, QString name, QStringList attributes);
    void traverse(QDomElement rootElement);
public:
    explicit XmlEditor(QObject *parent = nullptr);
    Q_INVOKABLE void readXml(QString path);
    Q_INVOKABLE void writeXml(QString path);
signals:

};

#endif // XMLEDITOR_H
