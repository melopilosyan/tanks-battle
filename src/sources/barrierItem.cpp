#include "../headers/barrierItem.h"

BarrierItem::BarrierItem( const Position&  pos,
                          const QPixmap&   pixmap,
                          BarrierType      type,
                          QGraphicsScene*  scene ):
    QGraphicsPixmapItem( pixmap, 0, scene ),
    m_type( type )
{
    setPos( pos );
    setZValue( ( ( type == COA ) ? 3:
               ( ( type == Water ) ? 0:
               ( ( type == Grass ) ? 2: 0 ) ) ) );
}

BarrierItem::~BarrierItem()
{ }

int BarrierItem::type() const
{ return Type; }

bool BarrierItem::isType( BarrierType type )
{ return ( m_type == type ) ? true: false; }
