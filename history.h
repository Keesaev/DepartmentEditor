#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>
#include <QtQml>
#include <treemodel.h>

class History : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit History(QObject *parent = nullptr);
    Q_INVOKABLE void saveState(TreeModel *state);
    Q_INVOKABLE void revertState(TreeModel *model);
    Q_INVOKABLE bool isEmpty();
    Q_INVOKABLE void clear();
private:
    QStack<TreeNode*> m_history; // Список корневых нод модели TreeModel
    void copyTree(TreeNode *root, TreeNode *newRoot, TreeNode *parentNode);
};

#endif // HISTORY_H
