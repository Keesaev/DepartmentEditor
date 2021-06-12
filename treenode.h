#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QtQml>

// https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
class TreeNode : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TreeNode(QVariant data = QVariant(), QVariant tag = QVariant(), TreeNode *parentNode = nullptr, QObject *parent = nullptr);
    ~TreeNode();

    void appendChild(TreeNode *node);
    void clear();
    void removeChild(TreeNode *node);

    void setParentNode(TreeNode *parent);
    void setData(QVariant data);
    void setTag(QVariant tag);

    TreeNode *getParentNode() const;
    TreeNode *getChild(int index) const;
    QVariant getData();
    QVariant getTag();
    int getChildIndex(TreeNode *node);

    int row() const;
    int count() const;
private:
    QList<TreeNode *> m_nodes;
    TreeNode *m_parentNode;
    QVariant m_data;
    QVariant m_tag;
};

#endif // TREENODE_H
