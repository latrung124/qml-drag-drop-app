#include "AssignmentItem.h"

AssignmentItem::AssignmentItem(QObject *parent)
    : QObject(parent)
{
}

AssignmentItem::AssignmentItem(const QString &type, const QString &source, QObject *parent)
    : QObject(parent), m_type(type), m_source(source)
{
}

AssignmentItem::~AssignmentItem()
{
}

QString AssignmentItem::type() const
{
    return m_type;
}

QString AssignmentItem::source() const
{
    return m_source;
}

void AssignmentItem::setType(const QString &type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

void AssignmentItem::setSource(const QString &source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(m_source);
}
