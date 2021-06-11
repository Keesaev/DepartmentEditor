#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QtQml>
#include <treenode.h>

// https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    //Q_DECL_OVERRIDE
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE TreeNode *getNodeByIndex(const QModelIndex &index);
    Q_INVOKABLE QModelIndex getIndexByNode(TreeNode *node);
    Q_INVOKABLE void insertNode(TreeNode *childNode, const QModelIndex &parent = QModelIndex(), int pos = (-1));
    Q_INVOKABLE QVariant getTagByIndex(const QModelIndex &index);
    Q_INVOKABLE void createNode(QVariant data, QVariant tag, const QModelIndex index);
    Q_INVOKABLE void createDepartment(QVariant data);
    Q_INVOKABLE void removeNode(const QModelIndex &index);
    Q_INVOKABLE void editNodeData(const QModelIndex &index, QVariant data);
    Q_INVOKABLE void addEmployment(const QModelIndex &index, QVariantList data);
    Q_INVOKABLE void clear();
    void appendNode(TreeNode *child, TreeNode *parent = nullptr);
    TreeNode *getRootNode();

protected:
    TreeNode *getNode(const QModelIndex &index) const;
private:
    TreeNode *m_rootNode;
};

#endif // TREEMODEL_H
