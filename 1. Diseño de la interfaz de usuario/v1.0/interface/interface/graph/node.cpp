#include "node.hpp"

void Node::init( QString id,
                 QString title,
                 QString icon,
                 QStringList children )
{
    this->setId( id );
    this->setTitle( title );
    this->setIcon( icon );
    this->setChildren( children );
}

Node::Node( QString id,
            QString title,
            QString icon,
            QStringList children,
            QObject *parent ) :
    QObject( parent )
{
    this->init( id, title, icon, children );
}

Node::~Node()
{

}

QString Node::getId() const
{
    return id;
}

void Node::setId( const QString &value )
{
    id = value;
}

QString Node::getTitle() const
{
    return title;
}

void Node::setTitle( const QString &value )
{
    title = value;
}

QString Node::getIcon() const
{
    return icon;
}

void Node::setIcon(const QString &value )
{
    icon = value;
}

QStringList Node::getChildren() const
{
    return children;
}

void Node::setChildren( const QStringList &value )
{
    children = value;
}
