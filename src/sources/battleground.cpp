#include "../headers/barrierItem.h"
#include "../headers/battleground.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>


// Auxiliary function
int barrierTypeToInt( BarrierType type )
{
    switch( type ) {
        case COA: return 0;
        case Brick: return 1;
        case Grass: return 2;
        case Water: return 3;
        case Concrete: return 4;
    default: break;
    }
    return 0; // For compiler shut up!!
}

Battleground::Battleground():
    m_timer( 0 ),
    m_sceneWidth( 0 ),
    m_sceneHeight( 0 ),
    m_coa( 0 ),
    m_battleground( 0 ),
    m_pixmaps( 5 ),
    m_barriers()
{
    loadImages();
}

Battleground::Battleground( QGraphicsScene* scene ):
    m_timer( 0 ),
    m_sceneWidth( 0 ),
    m_sceneHeight( 0 ),
    m_coa( 0 ),
    m_battleground( scene ),
    m_pixmaps( 5 ),
    m_barriers()
{
    if( !scene ) return;
    m_sceneWidth = m_battleground->width();
    m_sceneHeight = m_battleground->height();
    loadImages();
}

Battleground::~Battleground()
{
    cleanBattleground();
    foreach( QPixmap* pixmap, m_pixmaps ) {
        delete pixmap;
    }
}

void Battleground::openCavityAtPosition( Position pos, Direction dir, bool delConcrete )
{
    int x      = 0;
    int y      = 0;
    int width  = 0;
    int height = 0;
    if( dir == Up || dir == Down ) {
        x = pos.x() - TankSize.width()/2 + BulletSize.width()/2;
        y = ( dir == Up ) ? pos.y(): pos.y() + 5;
        width = TankSize.width();
        height = BarrierItemSize.width() - 5;
    } else {
        x = ( dir == Left ) ? pos.x() - 5: pos.x() + 5;
        y = pos.y() - TankSize.width()/2 + BulletSize.width()/2;
        width = BarrierItemSize.width() - 5;
        height = TankSize.width();
    }
    QList<QGraphicsItem*> barrierList = m_battleground->items( x, y, width, height );
    // qDebug() << "Liiiiiiiiiiiiiiiiiiiiiiiist leeeeeeeeeeenght =" << barrierList.length();
    foreach( QGraphicsItem* item, barrierList ) {
        if( qgraphicsitem_cast<BarrierItem*>( item ) ) {
            if( (( (BarrierItem*)item )->isType( Concrete ) && !delConcrete) ||
                ( (BarrierItem*)item )->isType( Water ) ||
                ( (BarrierItem*)item )->isType( Grass ) )
                continue;
            m_battleground->removeItem( item );
            //m_barriers.removeOne( (BarrierItem*)item );
            //delete item;
        }
    }
}

void Battleground::level( unsigned num )
{
    if( !m_battleground ) return;
    if( m_timer )
        disconnect( m_timer, SIGNAL( timeout() ), this, SLOT( moveCoa() ) );
    cleanBattleground();
    switch( num ) {
        case 1: level1(); break;
        case 2: level2(); break;
        case 3: level3(); break;
        case 4: level4(); break;
        case 5: level5(); break;
    default: break;
    }
}

void Battleground::level1()
{
    // qDebug() << "Battleground::level1 in";
    int someSize = m_sceneHeight / 2 - 100;
    rectOfBarrierItems( 60, 60, 60, someSize, Brick );
    rectOfBarrierItems( 180, 60 + someSize/2, 60, someSize/2, Brick );
    rectOfBarrierItems( 300, 60, 60, someSize, Brick );
    rectOfBarrierItems( 360, 60 + someSize/4, 30, 30, Concrete );
    rectOfBarrierItems( 390, 60 + someSize/3 * 2, 30, 30, Concrete );
    rectOfBarrierItems( 420, 60, 60, someSize, Brick );
    rectOfBarrierItems( 540, 60 + someSize/2, 60, someSize/2, Brick );
    rectOfBarrierItems( 660, 60, 60, someSize, Brick );

    rectOfBarrierItems( 0, m_sceneHeight/2 + 30, 60, 30, Concrete );
    rectOfBarrierItems( m_sceneWidth - 60, m_sceneHeight/2 + 30, 60, 30, Concrete );
    someSize -= 80;
    rectOfBarrierItems( 120, m_sceneHeight/2 + 60,  45, someSize, Brick );
    rectOfBarrierItems( m_sceneWidth - 165, m_sceneHeight/2 + 60,  45, someSize, Brick );

    rectOfBarrierItems( m_sceneWidth/2 - 90, m_sceneHeight/2 + 30, 60, someSize, Brick );
    rectOfBarrierItems( m_sceneWidth/2 - 30, m_sceneHeight/2 + 60, 60, 30, Water );
    rectOfBarrierItems( m_sceneWidth/2 + 30, m_sceneHeight/2 + 30, 60, someSize, Brick );

    rectOfBarrierItems( 60, m_sceneHeight/2 + 30, m_sceneWidth/2 - 150, 30, Grass );
    rectOfBarrierItems( m_sceneWidth/2 + 90, m_sceneHeight/2 + 30, m_sceneWidth/2 - 150, 30, Grass );
    setCoatOfArms();
    // qDebug() << "Battleground::level1 out";
}

void Battleground::level2()
{
    int someSize = m_sceneHeight / 2 - 100;
    rectOfBarrierItems( 60, 60, 60, someSize, Brick );
    rectOfBarrierItems( 180, 60 + someSize/2, 60, someSize/2, Brick );
    setCoatOfArms();
}

void Battleground::level3()
{
    int someSize = m_sceneHeight / 2 - 100;
    rectOfBarrierItems( 420, 60, 60, someSize, Brick );
    rectOfBarrierItems( 540, 60 + someSize/2, 60, someSize/2, Brick );
    rectOfBarrierItems( 660, 60, 60, someSize, Brick );
    setCoatOfArms();
}

void Battleground::level4()
{
    int someSize = m_sceneHeight / 2 - 200;
    rectOfBarrierItems( 0, m_sceneHeight/2 + 30, 60, 30, Concrete );
    rectOfBarrierItems( m_sceneWidth/2 + 30, m_sceneHeight/2 + 30, 60, someSize, Brick );
    rectOfBarrierItems( m_sceneWidth - 60, m_sceneHeight/2 + 30, 60, 30, Concrete );
    setCoatOfArms();
}

void Battleground::level5()
{
    int someSize = m_sceneHeight / 2 - 200;
    rectOfBarrierItems( m_sceneWidth/2 - 90, m_sceneHeight/2 + 30, 60, someSize, Brick );
    rectOfBarrierItems( m_sceneWidth/2 - 30, m_sceneHeight/2 + 60, 60, 30, Water );
    rectOfBarrierItems( m_sceneWidth/2 + 30, m_sceneHeight/2 + 30, 60, someSize, Brick );
    setCoatOfArms();
}

int Battleground::levelNum()
{ return LevelNum; }

void Battleground::setScene( QGraphicsScene* scene )
{
    if( !scene ) return;
    m_battleground = scene;
    m_sceneWidth = m_battleground->width();
    m_sceneHeight = m_battleground->height();
}

void Battleground::cleanBattleground()
{
    foreach ( BarrierItem* item, m_barriers) {
        if( item->scene() ) {
            m_battleground->removeItem( item );
        }
        delete item;
    }
    m_battleground->removeItem( m_coa );
    delete m_coa;
    m_barriers.clear();
}

void Battleground::rectOfBarrierItems( int x, int y, int width, int height, BarrierType type )
{
    // qDebug() << "Battleground::rectOfBarrierItems in";
    int barrierItemSz = BarrierItemSize.width();
    for( int i = y; i < height + y; i += barrierItemSz ) {
        for( int j = x; j < width + x; j += barrierItemSz ) {
            // qDebug() << "Prepare Barrier added: type" << m_pixmaps[barrierTypeToInt( type )]->width();
            m_barriers.append( new BarrierItem( Position(j+1, i+1),
                                                *m_pixmaps[barrierTypeToInt( type )],
                                                type, m_battleground ) );
            // qDebug() << "Barrier added";
        }
    }
    // qDebug() << "Battleground::rectOfBarrierItems out";
}

void Battleground::loadImages()
{
    // qDebug() << "BarrierItem::initTypes in";
    QPixmap source;
    QPainter painter;
    QStringList names;
    int width = BarrierItemSize.width();
    names << ":/images/coa"
          << ":/images/brick"
          << ":/images/grass"
          << ":/images/water"
          << ":/images/concrete";

    m_pixmaps[0] = new QPixmap( QPixmap( names.first() ).scaled( 60, 60 ) );
    for( int i = 1; i < 5; i++ )
        m_pixmaps[i] = new QPixmap( BarrierItemSize );
    for( int i = 1; i < 5; i++ ) {
        painter.begin( m_pixmaps[i] );
        source.load( names[i] );
        painter.drawPixmap( 0, 0, width, width, source, 0, 0, source.width()/2, source.height()/2 );
        painter.end();
    }
}

void Battleground::setCoatOfArms()
{
    m_coa = new BarrierItem( Position( m_sceneWidth/2 - 35, m_sceneHeight - 60 ),
                             *m_pixmaps[barrierTypeToInt( COA )], COA, m_battleground );
    int x = m_sceneWidth/2 - 75;
    int y = m_sceneHeight - 105;
    rectOfBarrierItems( x, y, 30, 105, Brick );
    rectOfBarrierItems( x + 30, y, 90, 30, Brick );
    rectOfBarrierItems( x + 105, y, 30, 105, Brick );
}

void Battleground::connectToMoveCoa( QTimer* timer )
{
    m_timer = timer;
    m_coa->setPixmap( QPixmap(":/images/crashed_coa").scaled( 60, 60 ) );
    connect( m_timer, SIGNAL( timeout() ), this, SLOT( moveCoa() ) );
}

void Battleground::moveCoa()
{
    if( m_coa->y() > 0 ) {
        m_coa->moveBy( 0, -5 );
    }
}
