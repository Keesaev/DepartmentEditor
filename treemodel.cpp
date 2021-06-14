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
     * Разделение на роли я опустил
    if(role != Qt::DisplayRole)
        return QVariant();
    */
    Q_UNUSED(role)
    TreeNode *node = static_cast<TreeNode*>(index.internalPointer());
    return node->getData();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode *parentNode = getNodeByIndex(parent);
    TreeNode *childNode = parentNode->getChild(row);
    if(childNode)
        return createIndex(row, column, childNode);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const{
    if(!index.isValid())
        return QModelIndex();
    TreeNode *childNode = static_cast<TreeNode*>(index.internalPointer());
    TreeNode *parentNode = static_cast<TreeNode*>(childNode->getParentNode());

    if(parentNode== m_rootNode)
        return QModelIndex();
    return createIndex(parentNode->row(), 0, parentNode);
}

int TreeModel::rowCount(const QModelIndex &parent) const{
    if(parent.column() > 0)
        return 0;
    TreeNode *parentItem = getNodeByIndex(parent);
    return parentItem->count();
}

int TreeModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 1;
}

QVariant TreeModel::getTagByIndex(const QModelIndex &index){
    TreeNode *node = getNodeByIndex(index);
    return node->getTag();
}

TreeNode *TreeModel::getNodeByIndex(const QModelIndex &index) const{
    if(!index.isValid())
        return m_rootNode;
    return static_cast<TreeNode*>(index.internalPointer());
}

QModelIndex TreeModel::getIndexByNode(TreeNode *node){
    QVector<int> positions;
    QModelIndex result;
    if(node){
        do{
            int pos = node->row();
            positions.append(pos);
            node = node->getParentNode();
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
    parent->appendChild(child);
    endInsertRows();
}

void TreeModel::editNodeData(const QModelIndex &index, QVariant data){
    TreeNode *node = getNodeByIndex(index);
    node->setData(data);
    emit dataChanged(index, index, QVector<int>{Qt::UserRole});
}

void TreeModel::createEmployment(const QModelIndex &index, QVariantList data){
    TreeNode *parentNode = getNodeByIndex(index);
    TreeNode *employment = new TreeNode("Сотрудник", "employment");
    QList<QString> tags = {"surname", "name", "middleName", "function", "salary"};
    for(int i = 0; i < 5; i++){
        TreeNode *node = new TreeNode(data[i], tags[i], employment);
        employment->appendChild(node);
    }
    appendNode(employment, parentNode);
}

void TreeModel::createDepartment(QVariant data){
    TreeNode *department = new TreeNode(data, "department");
    TreeNode *employments = new TreeNode("Сотрудники", "employments", department);
    department->appendChild(employments);
    appendNode(department, nullptr);
}

void TreeModel::removeNode(const QModelIndex &index){
    TreeNode *node = getNodeByIndex(index);
    TreeNode *parentNode = node->getParentNode();
    if(parentNode == nullptr)
        parentNode = m_rootNode;
    QModelIndex parentIndex = getIndexByNode(parentNode);
    beginRemoveRows(parentIndex, parentNode->getChildIndex(node), parentNode->getChildIndex(node));
    parentNode->removeChild(node);
    delete node;
    endRemoveRows();
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
    delete m_rootNode;
    m_rootNode = new TreeNode();
    endResetModel();
}

void TreeModel::resetRoot(TreeNode *newRoot){
    clear();
    for(int i = 0; i < newRoot->count(); i++){
        appendNode(newRoot->getChild(i), nullptr);
    }
    newRoot->clear();
    delete newRoot;
}
