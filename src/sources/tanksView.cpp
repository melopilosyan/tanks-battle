#include "../headers/tanksView.h"
#include "../headers/tanksScene.h"
//#include "../headers/explosionItem.h"
#include "../headers/greetingScene.h"


TanksView::TanksView():
    QGraphicsView( ),
    m_gameScene( new TanksScene() ),
    m_greetingScene( new GreetingScene() )
{
    // qDebug() << "TanksView in";
    switchToMenu();
    connect( m_greetingScene, SIGNAL( exit() ), SLOT( close() ) );
    connect( m_greetingScene, SIGNAL( start(int) ), SLOT( switchToGame(int) ) );
    connect( m_gameScene, SIGNAL( backToMenu() ), SLOT( switchToMenu() ) );
    // qDebug() << "TanksView out";
}

TanksView::~TanksView()
{
    delete m_gameScene;
    delete m_greetingScene;
    // qDebug() << "TanksView out";
}

void TanksView::switchToGame( int levelNum )
{
    setScene( m_gameScene );
    m_gameScene->start( levelNum );
}

void TanksView::switchToMenu()
{
    setScene( m_greetingScene );
    m_greetingScene->configureView();
}
