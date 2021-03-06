#include "history.h"

History::History(QObject *parent) : QObject(parent), m_state(0)
{
    m_history.append(new TreeNode());
}

// Создаем копию дерева в объект newRoot посредством вызова copyTree
void History::saveState(TreeModel *state){
    TreeNode *root = state->getRootNode();
    TreeNode *newRoot = new TreeNode();
    copyTree(root, newRoot, nullptr);
    // Очищаем все отмененные состояния
    if(m_state != (m_history.size() - 1)){
        for(int i = m_state + 1; i < m_history.size(); i++){
            delete m_history[i];
        }
        while(m_state < (m_history.size() - 1))
            m_history.removeLast();
    }
    m_history.append(newRoot);
    m_state++;
}

// Рекурсивный метод, копирующий дерево из root в newRoot
void History::copyTree(TreeNode *root, TreeNode *newRoot, TreeNode *parentNode){
    if(root == nullptr)
        return;
    else{
        newRoot->setData(root->getData());
        newRoot->setTag(root->getTag());
        newRoot->setAnnotation(root->getAnnotation());
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

void History::forward(TreeModel *model){
    if(!m_history.isEmpty() &&
            (m_state + 1) >= 0 &&
            (m_state + 1) < m_history.size()){
        m_state++;
        TreeNode *newRoot = new TreeNode();
        copyTree(m_history[m_state], newRoot, nullptr);
        model->resetRoot(newRoot);
        newRoot->clear();
        delete newRoot;
    }
}

void History::back(TreeModel *model){
    if(!m_history.isEmpty() &&
            (m_state - 1) >= 0 &&
            (m_state - 1) < m_history.size()){
        m_state--;
        // Передаём в model копию состояния, там она копируется в m_root
        TreeNode *newRoot = new TreeNode();
        copyTree(m_history[m_state], newRoot, nullptr);
        model->resetRoot(newRoot);
        newRoot->clear();
        delete newRoot;
    }
}

// Очищаем историю и записываем в качестве первого состояния пустую ноду
void History::clear(){
    foreach(TreeNode *i, m_history){
        delete i;
    }
    m_history.clear();
    m_history.append(new TreeNode());
    m_state = 0;
}

// Очищаем историю и устанавливаем первым элементом ноду указанной модели (при открытии файла, например)
void History::reset(TreeModel *model){
    foreach(TreeNode *i, m_history){
        delete i;
    }
    m_history.clear();
    m_state = -1;
    saveState(model);
}
