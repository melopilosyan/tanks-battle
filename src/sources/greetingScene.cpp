#include "../headers/greetingScene.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>


GreetingScene::GreetingScene():
    QGraphicsScene( 0 ),
    m_levelNum( 1 ),
    m_cursorStep( 60 ),
    m_direction( Up ),
    m_sceneSize( QSize( 500, 350 ) ),
    m_levelNumText( new QGraphicsTextItem( 0, this ) ),
    m_cursor( new QGraphicsPixmapItem( QPixmap(":/images/cursor_tank"), 0, this ) )
{
    setSceneRect( 0, 0, m_sceneSize.width() - 2, m_sceneSize.height() - 2 );
    setBackgroundBrush(QBrush(QPixmap(":/images/dialog_background").scaled(m_sceneSize)));

    int cursorPosY = m_sceneSize.height() / 2 - 20;
    int halfSceneWidth = m_sceneSize.width() / 2;
    m_levelNumText->setPlainText("1");
    m_levelNumText->setFont( QFont( "Serif", 25, 25) );
    m_levelNumText->setDefaultTextColor( QColor( Qt::blue ) );
    m_levelNumText->setPos( halfSceneWidth + 65, cursorPosY - 12 );

    m_cursor->setPos( halfSceneWidth - m_cursor->boundingRect().height() - 85,
                      cursorPosY );
    m_cursor->setRotation( 90 );
    m_cursor->setTransformOriginPoint( m_cursor->boundingRect().center() );

    QGraphicsTextItem* item = addText( "TANKS BATTLE", QFont("Serif", 30, 30) );
    item->setDefaultTextColor( QColor( Qt::white ) );
    item->setPos( 90, 5 );

    item = addText( "Level", QFont( "Serif", 23, 20 ) );
    item->setDefaultTextColor( QColor( Qt::blue ) );
    item->setPos( halfSceneWidth - 35, cursorPosY - 10);

    item = addText( "EXIT", QFont( "Serif", 20, 15 ) );
    item->setDefaultTextColor( QColor( Qt::cyan ) );
    item->setPos( halfSceneWidth - 5, cursorPosY + m_cursorStep - 8 );
}

GreetingScene::~GreetingScene()
{
    delete m_cursor;
    delete m_levelNumText;
}

void GreetingScene::keyPressEvent( QKeyEvent* ev )
{
    switch( ev->key() ) {
    case Qt::Key_Up:
        if( m_direction == Down ) {
            m_cursor->setY( m_cursor->y() - m_cursorStep );
            m_cursor->setRotation( 90 );
        }
        m_direction = Up;
        break;
    case Qt::Key_Down:
        if( m_direction == Up ) {
            m_cursor->setY( m_cursor->y() + m_cursorStep );
            m_cursor->setRotation( 90 );
        }
        m_direction = Down;
        break;
    case Qt::Key_Left:
        if( m_direction == Up ) {
            m_cursor->setRotation( 270 );
            if( --m_levelNum <= 0 )
                m_levelNum = 5;
            m_levelNumText->setPlainText( tr( "%1" ).arg( m_levelNum ) );
        }
        break;
    case Qt::Key_Right:
        if( m_direction == Up ) {
            m_cursor->setRotation( 90 );
            if( ++m_levelNum >= 5 )
                m_levelNum = 1;
            m_levelNumText->setPlainText( tr( "%1" ).arg( m_levelNum ) );
        }
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if( m_direction == Up ) {
            emit start( m_levelNum );
        } else {
            emit exit();
        }
        break;
    case Qt::Key_Escape:
        emit exit();
        break;
    default: QGraphicsScene::keyPressEvent( ev );
        break;
    }
}


void GreetingScene::configureView()
{
    if( !views().isEmpty() ) {
        QGraphicsView* view = views().first();
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setRenderHint(QPainter::Antialiasing);
        view->setFixedSize( m_sceneSize );
        m_levelNum = 1;
        m_levelNumText->setPlainText( tr( "%1" ).arg( m_levelNum ) );
    }
}
