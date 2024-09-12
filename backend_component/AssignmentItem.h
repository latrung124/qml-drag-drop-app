#include <QObject>

class AssignmentItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    AssignmentItem(QObject *parent = nullptr);
    AssignmentItem(const QString &type, const QString &source, QObject *parent = nullptr);
    ~AssignmentItem() override;

    QString type() const;
    QString source() const;

    void setType(const QString &type);
    void setSource(const QString &source);

signals:
    void typeChanged(const QString &type);
    void sourceChanged(const QString &source);

private:
    QString m_type;
    QString m_source;
};
