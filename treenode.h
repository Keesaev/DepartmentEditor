#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QtQml>
#include <QQmlListProperty>

class TreeNode : public QObject
{
    Q_OBJECT
public:
    explicit TreeNode(QObject *parent = nullptr);
    Q_PROPERTY(QQmlListProperty<TreeNode> nodes READ nodes)
    Q_CLASSINFO("DefaultProperty", "nodes")

    void setParentNode(TreeNode *parent);
    Q_INVOKABLE TreeNode *parentNode() const;
    bool insertNode(TreeNode *node, int pos = (-1));
    QQmlListProperty<TreeNode> nodes();

    TreeNode *getChild(int index) const;
    void clear();

    Q_INVOKABLE int pos() const;
    Q_INVOKABLE int count() const;
private:
    QList<TreeNode *> m_nodes;
    TreeNode *m_parentNode;

};

#endif // TREENODE_H
