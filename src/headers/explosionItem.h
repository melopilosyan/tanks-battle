#ifndef COLLISIONITEM_H
#define COLLISIONITEM_H

#include "neededTypes.h"
#include <QObject>
#include <phonon/MediaObject>

class ExplosionItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ExplosionItem( Position, ItemType type = Barrier, QGraphicsScene* scene = 0 );
    ~ExplosionItem();

protected slots:
    void destroy();

private:
    Phonon::MediaObject* m_boom;

};

#endif // COLLISIONITEM_H
