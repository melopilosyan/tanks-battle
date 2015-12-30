#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H

#include "neededTypes.h"


/*
*   Class Battleground - a battleground, providing 5 levels to given scene
*
*/
class Battleground : public QObject
{
    Q_OBJECT

public:
    enum { LevelNum = 5 };

    Battleground();
    Battleground( QGraphicsScene* scene = 0 );
    ~Battleground();

    int levelNum();
    void level( unsigned );
    void setScene( QGraphicsScene* );
    void connectToMoveCoa( QTimer* );
    void openCavityAtPosition( Position, Direction, bool delConcrete = false );

private slots:
    void moveCoa();

private:
    QTimer* m_timer;
    int m_sceneWidth;
    int m_sceneHeight;
    QGraphicsPixmapItem* m_coa;
    QGraphicsScene* m_battleground;
    QVector<QPixmap*> m_pixmaps;
    QList<BarrierItem*> m_barriers;

    void level1();
    void level2();
    void level3();
    void level4();
    void level5();
    void loadImages();
    void setCoatOfArms();
    void cleanBattleground();
    void rectOfBarrierItems( int, int, int, int, BarrierType );
};

#endif // BATTLEGROUND_H
