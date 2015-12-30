#ifndef TANKS_H
#define TANKS_H

#include "tankItem.h"

/*
*   Class GamerTank - provides a tank for gamer use
*
*/
class GamerTank : public TankItem
{

public:
    enum { Type = TankItem::Type + 1 };

    GamerTank( const Position& , QGraphicsScene* scene = 0 );
    ~GamerTank();

    int type() const;
};

/*
*   Class OpponentTank - provides a tank for computer use
*
*/
class OpponentTank : public TankItem
{

public:
    enum { Type = TankItem::Type + 2 };

    OpponentTank( const Position&, Direction, Complicity, QGraphicsScene* scene = 0 );
    ~OpponentTank();

    int type() const;
    void advance( int );

private:
    int fightStepCount;
    Direction moveDirection;
};



#endif // TANKS_H
