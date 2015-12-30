#ifndef BARRIERITEM_H
#define BARRIERITEM_H

#include "neededTypes.h"


/*
*   Class BarrierItem - provides a barrier corresponding to given pixmap
*
*/
class BarrierItem : public QGraphicsPixmapItem
{

public:
    enum { Type = UserType + 7 };

    BarrierItem( const Position&, const QPixmap&,
                 BarrierType, QGraphicsScene* scene = 0 );
    ~BarrierItem();

    int type() const;
    bool isType( BarrierType );

private:
    BarrierType m_type;
};

#endif // BARRIERITEM_H
