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
    explicit TreeNode(QVariant data = NULL, QVariant tag = NULL, TreeNode *parentNode = nullptr, QObject *parent = nullptr);
    ~TreeNode();

    void appendNode(TreeNode *node);
    TreeNode *parentNode() const;
    void setParentNode(TreeNode *parent);
    TreeNode *getChild(int index) const;    // Получить дочерний узел по индексу
    void clear();
    QVariant data();
    void setData(QVariant data);
    QVariant getTag();
    void removeChild(TreeNode *node);
    int getChildIndex(TreeNode *node);

    int row() const;                        // Индекс в родительском списке узлов
    int count() const;                      // Число дочерних узлов
private:
    QList<TreeNode *> m_nodes;
    TreeNode *m_parentNode;
    QVariant m_data;
    QVariant m_tag;
};

#endif // TREENODE_H
