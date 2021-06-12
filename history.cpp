#include "history.h"

History::History(QObject *parent) : QObject(parent)
{

}

// Создаем копию дерева в объект newRoot посредством вызова copyTree
void History::saveState(TreeModel *state){
    TreeNode *root = state->getRootNode();
    TreeNode *newRoot = new TreeNode();
    for(int i = 0; i < root->count(); i++){
        TreeNode *newChild = new TreeNode();
        copyTree(root->getChild(i), newChild, newRoot);
        newRoot->appendChild(newChild);
    }
    m_history.append(newRoot);
}

// Рекурсивный метод, копирующий дерево из root в newRoot
void History::copyTree(TreeNode *root, TreeNode *newRoot, TreeNode *parentNode){
    if(root == nullptr)
        return;
    else{
        newRoot->setData(root->getData());
        newRoot->setTag(root->getTag());
        newRoot->setParentNode(parentNode);
        for(int i = 0; i < root->count(); i++){
            TreeNode *child = new TreeNode();
            // Рекурсивно добавляем все дочерние ноды
            copyTree(root->getChild(i), child, newRoot);
            newRoot->appendChild(child);
        }
    }
}

bool History::isEmpty(){
    return m_history.isEmpty();
}

// Вызываем метод resetRoot класса TreeModel, в котором корневая нода заменяется
// на ноду из стака. Там же происходит удаление текущего состояния
void History::revertState(TreeModel *model){
    if(!m_history.isEmpty()){
        TreeNode *m = m_history.back();
        model->resetRoot(m);
        m_history.pop();
    }
}

// Очищаем историю (при открытии файла, например)
void History::clear(){
    while(!m_history.isEmpty()){
        TreeNode *node = m_history.top();
        delete node;
        m_history.pop();
    }
    m_history.clear();
}
