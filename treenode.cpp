#include "treenode.h"

TreeNode::TreeNode(QVariant data, QVariant tag, TreeNode *parentNode, QObject *parent) :
    QObject(parent),
    m_parentNode(parentNode),
    m_data(data),
    m_tag(tag)
{
}

TreeNode::~TreeNode(){
    foreach(TreeNode *i, m_nodes){
        delete i;
    }
    m_nodes.clear();
}

void TreeNode::setParentNode(TreeNode *parent){
    m_parentNode = parent;
}

TreeNode *TreeNode::getParentNode() const{
    return m_parentNode;
}

TreeNode *TreeNode::getChild(int index) const{
    if(index < 0 || index >= m_nodes.length())
        return nullptr;
    return m_nodes.at(index);
}

void TreeNode::clear(){
    m_nodes.clear();
}

void TreeNode::appendChild(TreeNode *node){
    m_nodes.append(node);
}

int TreeNode::row() const{
    TreeNode *parent = getParentNode();
    if(parent){
        return parent->m_nodes.indexOf(const_cast<TreeNode *>(this));
    }
    return 0;
}

int TreeNode::count() const{
    return m_nodes.count();
}

void TreeNode::setData(QVariant data){
    m_data = data;
}

QVariant TreeNode::getTag(){
    return m_tag;
}

void TreeNode::removeChild(TreeNode *node){
    node->clear();
    m_nodes.removeAt(m_nodes.indexOf(node));
}

int TreeNode::getChildIndex(TreeNode *node){
    if(m_nodes.contains(node))
        return m_nodes.indexOf(node);
    else
        return -1;
}

QVariant TreeNode::getData(){
    return m_data;
}

void TreeNode::setTag(QVariant tag){
    m_tag = tag;
}
