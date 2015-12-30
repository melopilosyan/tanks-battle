#ifndef BULLETITEM_H
#define BULLETITEM_H

#include "neededTypes.h"


/*
*   Class BulletItem - provides a tank bullet
*
*/
class BulletItem : public QGraphicsPixmapItem
{

public:
    static int count; // Just for debugging
    int num;

    enum { Type = UserType + 5 };

    BulletItem( const Position&, Direction,
                const TankItem*, QGraphicsScene*  scene = 0 );
    ~BulletItem();


    int type() const;
    void advance( int );
    const TankItem* myTank() const;

private:
    Position m_step;
    Direction m_direction;
    const TankItem* m_myTank;
    // Mark pointers for later deleting
    bool deleteMe;
    QGraphicsItem* tank;

    QGraphicsItem* collidesWithOtherItems();
};

#endif // BULLETITEM_H
