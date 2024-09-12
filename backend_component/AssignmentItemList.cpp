#include "AssignmentItem.h"
#include "AssignmentItemList.h"

AssignmentItemList::AssignmentItemList(const std::shared_ptr<ImageProvider> &provider, QObject *parent)
    : QAbstractListModel(parent),
    m_imageProvider(provider)
{
    m_roles[TypeRole] = "type";
    m_roles[SourceRole] = "source";
}

AssignmentItemList::~AssignmentItemList()
{
}

void AssignmentItemList::exampleInitialize()
{
    beginResetModel();
    m_assignmentItems.clear();
    QVector<QPixmap> pixmaps;
    m_imageProvider->getImages(pixmaps);
    for (int i = 0; i < pixmaps.size(); ++i)
    {
        std::string source = "";
        source.append(ImageProviderConstants::IMAGE_PROVIDER_PATH.begin(), ImageProviderConstants::IMAGE_PROVIDER_PATH.end());
        std::string index = std::to_string(i);
        source.append(index.begin(), index.end());
        m_assignmentItems.push_back(std::make_unique<AssignmentItem>("type", QString(source.c_str())));
    }
    endResetModel();
}

void AssignmentItemList::addAssignmentItem()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_assignmentItems.push_back(std::make_unique<AssignmentItem>());
    endInsertRows();
}

void AssignmentItemList::removeAssignmentItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_assignmentItems.erase(m_assignmentItems.begin() + index);
    endRemoveRows();
}

int AssignmentItemList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (int)(m_assignmentItems.size());
}

QVariant AssignmentItemList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_assignmentItems.size() || index.row() < 0)
        return QVariant();

    if (role == TypeRole)
    {
        return m_assignmentItems.at(index.row())->type();
    }
    else if (role == SourceRole)
    {
        return m_assignmentItems.at(index.row())->source();
    }

    return QVariant();
}

QHash<int, QByteArray> AssignmentItemList::roleNames() const
{
    return m_roles;
}

bool AssignmentItemList::moveRow(const QModelIndex &sourceParent, int sourceRow, const QModelIndex &destinationParent, int destinationChild)
{
    if (sourceRow < 0 || sourceRow >= rowCount(sourceParent) ||
        destinationChild < 0 || destinationChild > rowCount(destinationParent)) {
        return false;
    }

    auto screenMode = std::move(m_assignmentItems[sourceRow]);
    m_assignmentItems.erase(m_assignmentItems.begin() + sourceRow);

    if (sourceRow < destinationChild) {
        --destinationChild;
    }

    m_assignmentItems.insert(m_assignmentItems.begin() + destinationChild, std::move(screenMode));
    // std::swap(m_assignmentListModel[sourceRow], m_assignmentListModel[destinationChild]);

    emit dataChanged(index(sourceRow), index(destinationChild));

    return true;
}

bool AssignmentItemList::moveAssignmentItem(int sourceRow, int destinationRow)
{
    return moveRow(QModelIndex(), sourceRow, QModelIndex(), destinationRow);
}
