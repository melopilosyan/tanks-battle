#include "../headers/tanks.h"

GamerTank::GamerTank( const Position&  pos,
                      QGraphicsScene*  scene ):TankItem( pos, Up, Gamer, Simple, scene )
{
    // qDebug() << "GamerTank" << num;
}

GamerTank::~GamerTank()
{
    // qDebug() << "GamerTank::~GamerTank" << num;
}

int GamerTank::type() const
{ return Type; }


/*****************************************************/
OpponentTank::OpponentTank( const Position&  position,
                            Direction        direction,
                            Complicity       complicity,
                            QGraphicsScene*  scene ):TankItem( position, direction, Opponent,
                                                     complicity, scene ),
                                                     fightStepCount( 0 ),
                                                     moveDirection( this->direction() )
{
    // qDebug() << "OpponentTank" << num;
}

OpponentTank::~OpponentTank()
{
    // qDebug() << "OpponentTank::~OpponentTank" << num;
}

// Auxiliary function - return random direction
Direction randomDirection()
{
    switch( qrand() % 4 ) {
        case 0: return Up;
        case 1: return Down;
        case 2: return Left;
        case 3: return Right;
    }
    return Up;      // For compiler shut up!!!
}

int OpponentTank::type() const
{ return Type; }

void OpponentTank::advance( int phase )
{
    if( m_destroy ) return;
    // qDebug() << "OpponentTank" << num << "advance" << phase << "in";
    if( phase ) {
        if( m_destroy ) return;
        move( moveDirection );
        // qDebug() << "OpponentTank" << num << "advance" << phase << "out";
    } else {
        if( m_destroy ) return;
        if( ++fightStepCount == 30 ) {
            fightStepCount = 0;
            fight();
        }

        Position curPos = pos();
        Direction curDir = direction();

        if( move( curDir ) ) {
            if( m_destroy ) return;
            setPos( curPos );
            moveDirection = curDir;
        } else {
            if( m_destroy ) return;
            Direction anotherDir = randomDirection();
            if( move( anotherDir ) ) {
                if( m_destroy ) return;
                setPos( curPos );
                moveDirection = anotherDir;
            } else {
                if( m_destroy ) return;
                setPos( curPos );
                moveDirection = curDir;
            }
        }
        // qDebug() << "OpponentTank" << num << "advance" << phase << "out";
    }
}
