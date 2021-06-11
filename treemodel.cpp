#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_rootNode = new TreeNode();
}

TreeModel::~TreeModel(){
    delete m_rootNode;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    /*
    if(role != Qt::DisplayRole)
        return QVariant();
    */
    TreeNode *node = static_cast<TreeNode*>(index.internalPointer());
    return node->data();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode *parentItem = getNode(parent);
    TreeNode *childItem = parentItem->getChild(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const{
    if(!index.isValid())
        return QModelIndex();
    TreeNode *childItem = static_cast<TreeNode*>(index.internalPointer());
    TreeNode *parentItem = static_cast<TreeNode*>(childItem->parentNode());

    if(parentItem == m_rootNode)
        return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const{
    if(parent.column() > 0)
        return 0;
    TreeNode *parentItem = getNode(parent);
    return parentItem->count();
}

int TreeModel::columnCount(const QModelIndex &parent) const{
    return 1;
}

QVariant TreeModel::getTagByIndex(const QModelIndex &index){
    TreeNode *node = getNodeByIndex(index);
    return node->getTag();
}

TreeNode *TreeModel::getNodeByIndex(const QModelIndex &index){
    if(!index.isValid())
        return nullptr;
    return static_cast<TreeNode*>(index.internalPointer());
}

QModelIndex TreeModel::getIndexByNode(TreeNode *node){
    QVector<int> positions;
    QModelIndex result;
    if(node){
        do{
            int pos = node->row();
            positions.append(pos);
            node = node->parentNode();
        }while(node != nullptr);

        for(int i = positions.size() - 2; i >= 0; i--){
            result = index(positions[i], 0, result);
        }
    }
    return result;
}

void TreeModel::appendNode(TreeNode *child, TreeNode *parent){
    if(parent == nullptr)
        parent = m_rootNode;
    QModelIndex index = getIndexByNode(parent);
    child->setParentNode(parent);
    beginInsertRows(index, parent->count(), parent->count());
    parent->appendNode(child);
    endInsertRows();
}

void TreeModel::editNodeData(const QModelIndex &index, QVariant data){
    TreeNode *node = getNodeByIndex(index);
    node->setData(data);
    emit dataChanged(index, index, QVector<int>{Qt::UserRole});
}

void TreeModel::addEmployment(const QModelIndex &index, QVariantList data){
    TreeNode *parentNode = getNodeByIndex(index);
    TreeNode *employment = new TreeNode("Сотрудник", "employment");
    QList<QString> tags = {"surname", "name", "middleName", "function", "salary"};
    for(int i = 0; i < 5; i++){
        TreeNode *node = new TreeNode(data[i], tags[i], employment);
        employment->appendNode(node);
    }
    appendNode(employment, parentNode);
}

void TreeModel::insertNode(TreeNode *childNode, const QModelIndex &parent, int pos){
    TreeNode *parentElement = getNode(parent);
    if(pos >= parentElement->count())
        return;
    if(pos < 0)
        pos = parentElement->count();

    childNode->setParentNode(parentElement);
    beginInsertRows(parent, pos, pos);
    parentElement->appendNode(childNode);
    endInsertRows();
}

void TreeModel::createNode(QVariant data, QVariant tag, const QModelIndex index){
    TreeNode *parentNode = getNodeByIndex(index);
    TreeNode *node = new TreeNode(data, tag);
    appendNode(node, parentNode);
}

void TreeModel::createDepartment(QVariant data){
    TreeNode *department = new TreeNode(data, "department");
    appendNode(department, m_rootNode);
    TreeNode *emplyments = new TreeNode("Сотрудники", "employments");
    appendNode(emplyments, department);
}

void TreeModel::removeNode(const QModelIndex &index){
    TreeNode *node = getNodeByIndex(index);
    TreeNode *parentNode = node->parentNode();
    if(parentNode == nullptr)
        parentNode = m_rootNode;
    QModelIndex parentIndex = getIndexByNode(parentNode);
    beginRemoveRows(parentIndex, parentNode->getChildIndex(node), parentNode->getChildIndex(node));
    parentNode->removeChild(node);
    endRemoveRows();
}

TreeNode *TreeModel::getNode(const QModelIndex &index) const{
    if(index.isValid())
        return static_cast<TreeNode*>(index.internalPointer());
    return m_rootNode;
}

QHash<int, QByteArray> TreeModel::roleNames() const{
    return QHash<int, QByteArray> {
        { Qt::UserRole, "name"}
    };
}

TreeNode *TreeModel::getRootNode(){
    return m_rootNode;
}

void TreeModel::clear(){
    beginResetModel();
    m_rootNode->clear();
    endResetModel();
}
