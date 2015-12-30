#include "../headers/tanks.h"
#include "../headers/tanksScene.h"
#include "../headers/bulletItem.h"
#include "../headers/barrierItem.h"
//#include "../headers/explosionItem.h"

#include <QPainter>

int TankItem::count = 0;
TankItem::TankItem( const Position& pos,
                    Direction       direction,
                    ItemType        type,
                    Complicity      complicity,
                    QGraphicsScene* scene ):QGraphicsPixmapItem( 0, scene ),
                                            num( count++ ),
                                            m_destroy( false ),
                                            m_pixmaps(),
                                            m_type( type ),
                                            m_direction( direction ),
                                            m_complicity( complicity ),
                                            m_myBullet( 0 ),
                                            m_shotVoice( 0 ),
                                            m_lifeNum( 1  )
{
    // qDebug() << "TankItem" << num;
    m_pixmaps.append( QPixmap(":/images/simple_tank") );
    m_pixmaps.append( QPixmap(":/images/hard_tank") );
    m_pixmaps.append( QPixmap(":/images/hardest_tank") );
    /*m_shotVoice = Phonon::createPlayer(
                Phonon::MusicCategory, Phonon::MediaSource(":/sounds/tank_shot") );*/

    setPixmap( m_pixmaps[m_complicity].scaled( TankSize ) );
    setTransformOriginPoint( boundingRect().center() );
    setDirection( direction );
    setPos( pos );

    if( complicity == Harder )
        m_lifeNum = 2;
    if( type == Gamer )
        m_lifeNum = 3;
    // qDebug() << "TankItem";
}

TankItem::~TankItem()
{
    delete m_shotVoice;
    // qDebug() << "TankItem::~TankItem" << num;
}

bool TankItem::move( Direction direction )
{
    if( m_destroy ) return false;

    bool isMoved = true;
    switch( direction ) {
        case Up: isMoved = moveUpDown( Up ); break;
        case Down: isMoved = moveUpDown( Down ); break;
        case Left: isMoved = moveLeftRight( Left ); break;
        case Right: isMoved = moveLeftRight( Right ); break;
    default: break;
    }
    return isMoved;
}

bool TankItem::moveUpDown( Direction dir )
{
    if( m_destroy ) return false;

    //// qDebug() << ((isType(Gamer))?"Gamer":"Opponent")
    //         << "TankItem::move" << ((dir == Up)?"Up":"Down");
    setDirection( dir );
    Position curPos = pos();
    Position newPos = curPos + Position( 0, ( (dir == Up ) ?
                                               -TankMoveStep: TankMoveStep) );
    if( m_destroy ) return false;
    setPos( newPos );
    const QGraphicsItem* item = collidesWithOtherItems();
    if( item ) {
        if( m_destroy ) return false;
        setPos( curPos );
        return false;
    }
    if( ( dir == Up ) && ( newPos.y() < TankMoveStep ) ) {
        if( m_destroy ) return false;
        newPos.ry() = 0;
        setPos( newPos );
        return false;
    }
    else if( ( dir == Down ) &&
             ( newPos.y() > SceneSize.height() - TankSize.height() ) ) {
        if( m_destroy ) return false;
        newPos.ry() = SceneSize.height() - TankSize.height();
        setPos( newPos );
        return false;
    }
    return true;
}

bool TankItem::moveLeftRight( Direction dir )
{
    if( m_destroy ) return false;

    //// qDebug() << ((isType( Gamer))?"Gamer":"Opponent")
    //         << "TankItem::move" << ((dir == Left)?"Left":"Right");
    setDirection( dir );
    Position curPos = pos();
    Position newPos = curPos + Position( ( (dir == Left ) ?
                                            -TankMoveStep: TankMoveStep ), 0 );
    setPos( newPos );
    const QGraphicsItem* item = collidesWithOtherItems();
    if( m_destroy ) return false;
    if( item ) {
        setPos( curPos );
        return false;
    }
    if( m_destroy ) return false;
    if( ( dir == Left ) && ( newPos.x() < TankMoveStep ) ) {
        if( m_destroy ) return false;
        newPos.rx() = 0;
        setPos( newPos );
        return false;
    }
    else if( ( dir == Right ) &&
             ( newPos.x() > SceneSize.width() - TankSize.height() ) ) {
        if( m_destroy ) return false;
        newPos.rx() = SceneSize.width() - TankSize.height();
        setPos( newPos );
        return false;
    }
    return true;
}

void TankItem::fight()
{
    if( m_destroy ) return;
    /*if( Phonon::PlayingState == m_shotVoice->state())
        m_shotVoice->stop();
    m_shotVoice->play();*/
    Position pos = mapToScene( boundingRect().center() );
    switch( m_direction ) {
        case Up:
            pos.rx() -= BulletSize.width() / 2;
            pos.ry() -= TankSize.height() / 2 + BulletSize.height() + 1;
            break;
        case Down:
            pos.rx() -= BulletSize.width() / 2;
            pos.ry() += TankSize.height() / 2 + 1;
            break;
        case Left:
            pos.rx() -= TankSize.height() / 2 + BulletSize.height();
            pos.ry() -= BulletSize.width() / 2 + 2;
            break;
        case Right:
            pos.rx() += TankSize.height() / 2 + 1;
            pos.ry() -= BulletSize.width() / 2 + 2;
            break;
    default: break;
    }
    if( m_destroy ) return;
    m_myBullet = new BulletItem( pos, m_direction, this );
    ( ( TanksScene* )scene() )->addBullet( m_myBullet );
}

bool TankItem::isType( ItemType type ) const
{ return ( type == m_type ) ? true: false; }

bool TankItem::prepareDestroy()
{
    if( --m_lifeNum == 0 ) {
        m_destroy = true;
        return true;
    }
    if( m_type == Gamer )
        setPos(Position( SceneSize.width()/2 - TankSize.width() - 76,
                         SceneSize.height() - TankSize.height() ) );
    return false;
}

Direction TankItem::direction() const
{ return m_direction; }

Complicity TankItem::complicity() const
{ return m_complicity; }

int TankItem::type() const
{ return Type; }

void TankItem::setDirection( Direction direction )
{
    m_direction = direction;
    setRotation( direction );
}

void TankItem::setComplicity( Complicity complicity )
{
    prepareGeometryChange();
    m_complicity = complicity;
    setPixmap( m_pixmaps[m_complicity].scaled( TankSize ) );
}

const QGraphicsItem* TankItem::collidesWithOtherItems()
{
    if( m_destroy ) return 0;
    QList<QGraphicsItem*> sceneItems =
            scene()->items( mapToScene( boundingRect() ) );
    if( m_destroy ) return 0;
    foreach( QGraphicsItem* item,  sceneItems ) {
        if( m_destroy ) return 0;
        if( ( item != this ) && ( item != m_myBullet ) &&
            !qgraphicsitem_cast<BulletItem*>( item ) &&
            !qgraphicsitem_cast<QGraphicsTextItem*>( item ) )
//            && !qgraphicsitem_cast<ExplosionItem*>( item )
        {
            if( qgraphicsitem_cast<BarrierItem*>( item ) ) {
                if( ( ( BarrierItem* )item )->isType( Grass ) )
                    continue;
            }
            return item;
        }
    }
    return 0;
}


