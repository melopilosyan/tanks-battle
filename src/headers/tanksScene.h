#ifndef TANKSSCENE_H
#define TANKSSCENE_H

#include "neededTypes.h"
#include <QGraphicsScene>


/*
*   Class TanksScene - privides a scene where taking place game actions
*
*/
class TanksScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TanksScene();
    ~TanksScene();

    void coaCrashed();
    void addBullet( BulletItem* );
    void removeMyItem( QGraphicsItem* );
    void brickBarrier( Position, Direction, bool delConcrete = false );

protected:
    void keyPressEvent( QKeyEvent* );
    void keyReleaseEvent( QKeyEvent* );

signals:
    void backToMenu();

public slots:
    void start( int );

private slots:
    void manager();
    void endLevel();
    void moveGamer();
    void gamerFight();
    void onNextLevel();

private:
    QTimer* m_gameTimer;
    QTimer* m_gamerMoveTimer;
    QTimer* m_gamerFightTimer;
    GamerTank* m_gamer;
    Battleground* m_battleground;
    QList<BulletItem*> m_bullets;
    QGraphicsTextItem* m_gameOverText;
    QGraphicsTextItem* m_nextLevelText;
    QList<OpponentTank*> m_opponents;
    QList<QGraphicsItem*> m_needlessItems;

    Direction m_gamerMoveDirection;

    bool m_gameOver;

    int m_levelNum;
    int m_gameSpeed;
    int m_opponentNum;
    int m_gamerMoveSpeed;
    int m_gamerFightSpeed;
    int m_levelOpponentNum;

    void gameOver();
    void nextLevel();
    void addOpponent();
    void deleteBullets();
    void deleteOpponents();
    void deleteNeedlessItems();

    void configureView();

    Complicity opponentComplicity();
    Position opponentPosition( int );
    Direction opponentDirection( int );
};

#endif // TANKSSCENE_H
