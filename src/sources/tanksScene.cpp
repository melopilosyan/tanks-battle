#include "../headers/battleground.h"
#include "../headers/tanksScene.h"
#include "../headers/bulletItem.h"
#include "../headers/tanks.h"

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>


TanksScene::TanksScene():QGraphicsScene( 0 ),
                         m_gameTimer( new QTimer( this ) ),
                         m_gamerMoveTimer( new QTimer( this ) ),
                         m_gamerFightTimer( new QTimer( this ) ),
                         m_gamer( new GamerTank( Position( 0, 0 ) ) ),
                         m_battleground( new Battleground( this ) ),
                         m_bullets( ),
                         m_gameOverText( new QGraphicsTextItem( "GAME OVER" ) ),
                         m_nextLevelText( new QGraphicsTextItem ),
                         m_opponents(),
                         m_needlessItems(),
                         m_gamerMoveDirection( Up ),
                         m_gameOver( false ),
                         m_levelNum( 0 ),
                         m_gameSpeed( 40 ),
                         m_opponentNum( 0 ),
                         m_gamerMoveSpeed( 35 ),
                         m_gamerFightSpeed( 300 ),
                         m_levelOpponentNum( 0 )
{
    // qDebug() << "TanksScene in";
    setBackgroundBrush( Qt::black );
    setSceneRect( 0, 0, SceneSize.width() - 2, SceneSize.height() - 2 );

    m_bullets.clear();
    m_opponents.clear();
    m_needlessItems.clear();
    m_battleground->setScene( this );
    m_gameOverText->setFont( QFont("Serif", 40, 40) );
    m_nextLevelText->setFont( QFont("Serif", 40, 40) );
    m_gameOverText->setPos( width()/2 - 180, height()/2 - 20 );
    m_nextLevelText->setPos( width()/2 - 80, height()/2 - 20 );

    connect( m_gameTimer, SIGNAL( timeout() ), SLOT( manager() ) );
    connect( m_gameTimer, SIGNAL( timeout() ), SLOT( advance() ) );
    connect( m_gamerMoveTimer, SIGNAL( timeout() ), SLOT( moveGamer() ) );
    connect( m_gamerFightTimer, SIGNAL( timeout() ), SLOT( gamerFight() ) );

    // qDebug() << "TanksScene out";
}

TanksScene::~TanksScene()
{
    delete m_gameTimer;
    delete m_gamer;
    delete m_battleground;
    delete m_gameOverText;
    delete m_nextLevelText;
    delete m_gamerMoveTimer;
    delete m_gamerFightTimer;

    deleteBullets();
    deleteOpponents();
    deleteNeedlessItems();
    // qDebug() << "TanksScene::~TanksScene";
}

void TanksScene::keyPressEvent( QKeyEvent* event )
{
    switch( event->key() ) {
        case Qt::Key_Up:
            if( !event->isAutoRepeat() ) {
                if( !m_gamerMoveTimer->isActive() )
                    m_gamerMoveTimer->start( m_gamerMoveSpeed );
                m_gamerMoveDirection = Up;
                moveGamer();
            }
            break;
        case Qt::Key_Down:
            if( !event->isAutoRepeat() ) {
                if( !m_gamerMoveTimer->isActive() )
                    m_gamerMoveTimer->start( m_gamerMoveSpeed );
                m_gamerMoveDirection = Down;
                moveGamer();
            }
            break;
        case Qt::Key_Left:
            if( !event->isAutoRepeat() ) {
                if( !m_gamerMoveTimer->isActive() )
                    m_gamerMoveTimer->start( m_gamerMoveSpeed );
                m_gamerMoveDirection = Left;
                moveGamer();
            }
            break;
        case Qt::Key_Right:
            if( !event->isAutoRepeat() ) {
                if( !m_gamerMoveTimer->isActive() )
                    m_gamerMoveTimer->start( m_gamerMoveSpeed );
                m_gamerMoveDirection = Right;
                moveGamer();
            }
            break;
        case Qt::Key_F:
        case Qt::Key_Space:
            if( !event->isAutoRepeat() ) {
                if( !m_gamerFightTimer->isActive() )
                    m_gamerFightTimer->start( m_gamerFightSpeed );
                gamerFight();
            }
            break;
        case Qt::Key_Escape:
            endLevel();
            break;
        default: break;
    }
    QGraphicsScene::keyPressEvent( event );
}

void TanksScene::keyReleaseEvent( QKeyEvent* event )
{
    switch( event->key() ) {
        case Qt::Key_Up:
            if( !event->isAutoRepeat() ) {
                if( m_gamerMoveTimer->isActive() )
                    m_gamerMoveTimer->stop();
            }
            break;
        case Qt::Key_Down:
        if( !event->isAutoRepeat() ) {
            if( m_gamerMoveTimer->isActive() )
                m_gamerMoveTimer->stop();
        }
            break;
        case Qt::Key_Left:
        if( !event->isAutoRepeat() ) {
            if( m_gamerMoveTimer->isActive() )
                m_gamerMoveTimer->stop();
        }
            break;
        case Qt::Key_Right:
        if( !event->isAutoRepeat() ) {
            if( m_gamerMoveTimer->isActive() )
                m_gamerMoveTimer->stop();
        }
            break;
        case Qt::Key_F:
        case Qt::Key_Space:
            if( !event->isAutoRepeat() ) {
                if( m_gamerFightTimer->isActive() )
                    m_gamerFightTimer->stop();
            }
            break;
        case Qt::Key_Escape:
            endLevel();
            break;
        default: break;
    }
    QGraphicsScene::keyPressEvent( event );
}

void TanksScene::moveGamer()
{
    if( m_gamer->scene() )
        m_gamer->move( m_gamerMoveDirection );
}

void TanksScene::gamerFight()
{
    if( m_gamer->scene() )
        m_gamer->fight();
}

void TanksScene::removeMyItem( QGraphicsItem* item )
{
    // qDebug() << "TanksScene::eliminateSceneItem in";

    if( qgraphicsitem_cast<GamerTank*>( item ) ) {
        if( ( (GamerTank*)item )->prepareDestroy() ) {
            m_gameOver = true;
            removeItem( item );
        }
    } else if( qgraphicsitem_cast<OpponentTank*>( item ) ) {
        if( ( (OpponentTank*)item )->prepareDestroy() ) {
            removeItem( item );
            m_opponents.removeOne( (OpponentTank*)item );
            m_needlessItems.append( item );
        }
    } else if( qgraphicsitem_cast<BulletItem*>( item ) ) {
        removeItem( item );
        m_bullets.removeOne( (BulletItem*)item );
        m_needlessItems.append( item );
        //delete item;
    }

    // qDebug() << "TanksScene::eliminateSceneItem out";
}

void TanksScene::manager()
{
    // qDebug() << "TanksView::manageeeeeeeeeeeeeeeeeer" << "in";
    static int count = 0;
    if( m_opponentNum != m_levelOpponentNum )
        if( ++count == 145 ) {
            addOpponent();
            count = 0;
        }
    // qDebug() << "if 1";
    if( ( m_opponentNum == m_levelOpponentNum ) && m_opponents.isEmpty() )
        nextLevel();
    // qDebug() << "if 2";

    if( m_gameOver )
        gameOver();
    // qDebug() << "TanksView::manager" << "out";
}

void TanksScene::start( int levelNum )
{
    // qDebug() << "TanksScene::start level" << levelNum << "in";

    if( levelNum > 2 ) m_levelOpponentNum = 15;
    else m_levelOpponentNum = 10;
    m_levelNum = levelNum;
    m_gameOver = false;
    m_opponentNum = 0;

    m_battleground->level( levelNum );

    for( int i = 0; i < 2; i++ )
        addOpponent();

    m_gamer->setDirection( Up );
    m_gamer->setPos( Position( width()/2 - TankSize.width() - 76, height() - TankSize.height() ) );
    if( !m_gamer->scene() )
        addItem( m_gamer );
    if( m_gameOverText->scene() )
        removeItem( m_gameOverText );
    if( m_nextLevelText->scene() )
        removeItem( m_nextLevelText );

    configureView();
    m_gameTimer->start( m_gameSpeed );

    // qDebug() << "TanksScene::start level" << levelNum << "out";
}

void TanksScene::nextLevel()
{
    // qDebug() << "TanksScene::nextLevel: level -" << m_levelNum + 1;
    if( ++m_levelNum > m_battleground->levelNum() ) {
        m_nextLevelText->setPlainText( "THE AND" );
        addItem( m_nextLevelText );
        //QTimer::singleShot( 2500, this, SLOT( endLevel() ) );
        endLevel();
        return;
    }
    if( !m_nextLevelText->scene() ) {
        m_nextLevelText->setPlainText( tr( "LEVEL %1" ).arg( m_levelNum ) );
        addItem( m_nextLevelText );
    }
    //qDebug() << "TanksScene::nextLevel out";
    onNextLevel();
    //QTimer::singleShot( 2500, this, SLOT( onNextLevel() ) );
}

void TanksScene::onNextLevel()
{
    // qDebug() << "TanksScene::onNextLevel in";
    deleteBullets();
    deleteOpponents();
    deleteNeedlessItems();
    if( m_nextLevelText->scene() )
        removeItem( m_nextLevelText );
    start( m_levelNum );
    // qDebug() << "TanksScene::onNextLevel out";
}

void TanksScene::gameOver()
{
    // qDebug() << "TanksScene::gameOver in";

    if( !m_gameOverText->scene() )
        addItem( m_gameOverText );

    QTimer::singleShot( 2500, this, SLOT( endLevel() ) );
    // qDebug() << "TanksScene::gameOver out";
}

void TanksScene::endLevel()
{
    // qDebug() << "TanksScene::endLevel in";
    m_gameTimer->stop();
    m_gamerMoveTimer->stop();
    m_gamerFightTimer->stop();
    deleteBullets();
    deleteOpponents();
    deleteNeedlessItems();
    emit backToMenu();
    // qDebug() << "TanksScene::endLevel out";
}

void TanksScene::addOpponent()
{
    // qDebug() << "TanksView::addOpponent in";

    int x = qrand();
    OpponentTank* tank = new OpponentTank( opponentPosition(x),
                                           opponentDirection(x),
                                           opponentComplicity() );
    addItem( tank );
    m_opponents.append( tank );
    m_opponentNum++;
    // qDebug() << "TanksView::addOpponent out";
}

void TanksScene::addBullet( BulletItem* bullet )
{
    addItem( bullet );
    m_bullets.append( bullet );
}

void TanksScene::deleteOpponents()
{
    if( !m_opponents.isEmpty() ) {
        foreach( OpponentTank* tank, m_opponents ) {
            tank->prepareDestroy();
            if( tank->scene() ) {
                removeItem( tank );
            }
            delete tank;
        }
        m_opponents.clear();
    }
}

void TanksScene::deleteNeedlessItems()
{
    // qDebug() << "TanksScene::deleteNeedlessItems in";
    if( !m_needlessItems.isEmpty() ) {
        foreach( QGraphicsItem* item, m_opponents ) {
            delete item;
        }
        m_needlessItems.clear();
    }
    // qDebug() << "TanksScene::deleteNeedlessItems out";
}

void TanksScene::deleteBullets()
{
    if( !m_bullets.isEmpty() ) {
        foreach( BulletItem* bullet, m_bullets ) {
            if( bullet->scene() ) {
                removeItem( bullet );
            }
            delete bullet;
        }
        m_bullets.clear();
    }
}

void TanksScene::brickBarrier( Position pos, Direction dir, bool delConcrete )
{
    // qDebug() << "TanksScene::brickBarrier in";
    m_battleground->openCavityAtPosition( pos, dir, delConcrete );
    // qDebug() << "TanksScene::brickBarrier out";
}

void TanksScene::coaCrashed()
{
    m_battleground->connectToMoveCoa( m_gameTimer );
    m_gameOver = true;
}

void TanksScene::configureView()
{
    if( !views().isEmpty() ) {
        QGraphicsView* view = views().first();
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setRenderHint(QPainter::Antialiasing);
        view->setFixedSize( SceneSize );
    }
}

Position TanksScene::opponentPosition( int x )
{
    x = x % ( SceneSize.width() - TankSize.width() );
    QList<QGraphicsItem*> collides = items( x, 1, TankSize.height(), TankSize.height() );
    foreach( QGraphicsItem* item, collides ) {
        if( qgraphicsitem_cast<OpponentTank*>( item ) ||
            qgraphicsitem_cast<GamerTank*>( item ) ) {
            return opponentPosition( qrand() );
        }
    }
    return Position( x, 1 );
}

Direction TanksScene::opponentDirection( int _i )
{
    if( _i < ( SceneSize.width() - TankSize.height() ) / 3 ) {
        return Right;
    } else if( _i > SceneSize.width() / 3 * 2 ){
        return Left;
    } else {
        return Down;
    }
}

Complicity TanksScene::opponentComplicity()
{
    if( m_opponentNum < m_levelOpponentNum / 3 ) {
        return Simple;
    } else if( m_opponentNum < m_levelOpponentNum / 3 * 2 ) {
        return Hard;
    } else {
        return Harder;
    }
}
