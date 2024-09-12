#include <memory>
#include <vector>

#include "ImageProvider.h"

#include <QHash>
#include <QAbstractListModel>

class AssignmentItem;

class AssignmentItemList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AssignmentItemList(const std::shared_ptr<ImageProvider> &provider
                                , QObject *parent = nullptr);
    ~AssignmentItemList() override;

    enum AssignmentItemRoles
	{
		TypeRole = Qt::UserRole + 1,
        SourceRole
	};

    void exampleInitialize();

    void addAssignmentItem();
    void removeAssignmentItem(int index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;
    bool moveRow(const QModelIndex &sourceParent, int sourceRow, const QModelIndex &destinationParent, int destinationChild);

    Q_INVOKABLE bool moveAssignmentItem(int sourceRow, int destinationRow);

protected:
    QHash<int, QByteArray> m_roles;
    std::vector<std::unique_ptr<AssignmentItem>> m_assignmentItems;
    std::shared_ptr<ImageProvider> m_imageProvider;
};
