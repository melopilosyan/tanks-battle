//#include "../headers/explosionItem.h"
#include "../headers/barrierItem.h"
#include "../headers/bulletItem.h"
#include "../headers/tanksScene.h"
#include "../headers/tanks.h"

#include <QPainter>

int BulletItem::count = 0;
BulletItem::BulletItem( const Position&  pos,
                        Direction        direction,
                        const TankItem*  myTank,
                        QGraphicsScene*  scene ):
    QGraphicsPixmapItem( QPixmap(":/images/bullet").scaled(BulletSize), 0, scene ),
    num(count++),
    m_step( ),
    m_direction( direction ),
    m_myTank( 0 ),
    deleteMe( false ),
    tank( 0 )
{
    setPos( pos );
    setZValue( 1 );
    setRotation( direction );
    setTransformOriginPoint( boundingRect().center() );
    qreal x = 0, y = 0;
    switch( direction ) {
        case Up: y = -BulletMoveStep; break;
        case Down: y = BulletMoveStep; break;
        case Left: x = -BulletMoveStep; break;
        case Right: x = BulletMoveStep; break;
    default: break;
    }
    m_step = Position( x, y );
    this->m_myTank = myTank;
    // qDebug() << "BulletItem";
}

BulletItem::~BulletItem()
{
    // qDebug() << "BulletItem::~BulletItem" << num;
}

const TankItem* BulletItem::myTank() const
{ return m_myTank; }

int BulletItem::type() const
{ return Type; }

QGraphicsItem* BulletItem::collidesWithOtherItems()
{
    //// qDebug() << "BulletItem" << num <<"collidesWithOtherItems in";
    QList<QGraphicsItem*> sceneItems =
            scene()->items( mapToScene( boundingRect() ) );
    foreach( QGraphicsItem* item, sceneItems ) {
        if( ( item != this ) && ( item != m_myTank ) &&
            !qgraphicsitem_cast<QGraphicsTextItem*>( item ) ) {
            if( qgraphicsitem_cast<BarrierItem*>( item ) ) {
                if( ( ( BarrierItem* )item )->isType( Water ) ||
                    ( ( BarrierItem* )item )->isType( Grass ) )
                    continue;
            }
            return item;
        }
    }
    //// qDebug() << "BulletItem::collidesWithOtherItems return NULL";
    return NULL;
}

void BulletItem::advance( int phase )
{
    // qDebug() << "BulletItem" << num << "advance" << phase;
    if( phase ) {
        setPos( pos() + m_step );
    } else {
        Position curPos = pos();
        setPos( curPos + m_step );
        switch( m_direction ) {
            case Up:
                if( pos().y() < 0 ) {
                    ( ( TanksScene* )scene() )->removeMyItem( this );
                    return;
                }
                break;
            case Down:
                if( pos().y() > SceneSize.height() ) {
                    ( ( TanksScene* )scene() )->removeMyItem( this );
                    return;
                }
                break;
            case Left:
                if( pos().x() < 0 ) {
                    ( ( TanksScene* )scene() )->removeMyItem( this );
                    return;
                }
                break;
            case Right:
                if( pos().y() > SceneSize.width() ) {
                    ( ( TanksScene* )scene() )->removeMyItem( this );
                    return;
                }
                break;
        default: break;
        }
        QGraphicsItem* item = collidesWithOtherItems();
        if( item ) {
            if( qgraphicsitem_cast<OpponentTank*>( item ) ||
                qgraphicsitem_cast<GamerTank*>( item ) )
            {
                // qDebug() << "Bullet reach to some tank";
                if( m_myTank && m_myTank->isType( Opponent ) ) {
                    if( ( ( TankItem* )item )->isType( Gamer ) ) {
                        // qDebug() << "Bullet tank is opponent and collides tank is gamer";
//                        new ExplosionItem( pos(), Tank, scene() );
                        ( ( TanksScene* )scene() )->removeMyItem( item );
                        ( ( TanksScene* )scene() )->removeMyItem( this );
                        return;
                    }
                } else {
                    if( ( ( TankItem* )item )->isType( Opponent ) ) {
                        // qDebug() << "Bullet tank is gamer and collides tank is oppenent";
//                        new ExplosionItem( pos(), Tank, scene() );
                        ( ( TanksScene* )scene() )->removeMyItem( item );
                        ( ( TanksScene* )scene() )->removeMyItem( this );
                        return;
                    }
                }
            } else if( qgraphicsitem_cast<BulletItem*>( item ) ) {
                // qDebug() << "Bullet reach to another bullet";
                if( ( ( BulletItem* )item )->myTank()->isType( Opponent ) &&
                    m_myTank->isType( Opponent ) && m_myTank ) {
                    // qDebug() << "Opponent shoots to opponent";
                    setPos( curPos );
                    return;
                }
//                new ExplosionItem( pos(), Bullet, scene() );
                // qDebug() << "Gamer shoots to opponent or hakarak@";
                ( ( TanksScene* )scene() )->removeMyItem( this );
                return;
            } else if( qgraphicsitem_cast<BarrierItem*>( item ) ){
                // qDebug() << "Bullet reach to barriers";
//                new ExplosionItem( pos(), Barrier, scene() );
                if( ( ( BarrierItem* )item )->isType( Concrete ) &&
                        m_myTank->complicity() == Harder ) {
                    ( ( TanksScene* )scene() )
                            ->brickBarrier( mapToScene(boundingRect().center()),
                                            m_direction, true );
                    ( ( TanksScene* )scene() )->removeMyItem( this );
                    return;
                }
                if( ( ( BarrierItem* )item )->isType( Brick ) ){
                    ( ( TanksScene* )scene() )->brickBarrier( pos() , m_direction );
                }
                if( ( ( BarrierItem* )item )->isType( COA ) ) {
                    ( ( TanksScene* )scene() )->coaCrashed();
                }
                ( ( TanksScene* )scene() )->removeMyItem( this );
                return;
            }
        }
        setPos( curPos );
    }
}
