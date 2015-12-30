#include "../headers/explosionItem.h"

#include <QGraphicsScene>
#include <QTimer>


ExplosionItem::ExplosionItem( Position pos, ItemType /*type*/, QGraphicsScene* scene ):
    QObject( 0 ),
    QGraphicsPixmapItem( 0, scene ),
    m_boom( 0 )
{
    setPixmap( QPixmap(":/images/explosion").scaled( 35, 35 ) );
    setTransformOriginPoint( boundingRect().center() );
    setPos( pos + Position( -35/2, -35/2 ) );
    setRotation( qrand() % 360 );
    setZValue( 4 );

    m_boom = Phonon::createPlayer( Phonon::MusicCategory, Phonon::MediaSource(":/sounds/boom"));
    m_boom->play();
    QTimer::singleShot( 70, this, SLOT( destroy() ) );
}

ExplosionItem::~ExplosionItem()
{
    delete m_boom;
}

void ExplosionItem::destroy()
{
    //m_boom->stop();
    scene()->removeItem( this );
    delete this;
}

