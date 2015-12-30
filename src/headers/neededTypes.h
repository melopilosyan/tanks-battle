#ifndef NEEDEDTYPES_H
#define NEEDEDTYPES_H


#include <QPointF>
#include <QGraphicsPixmapItem>

// No longer needed
//#include <QtGlobal>
//#include <QDebug>

#define TankMoveStep 4
#define BulletMoveStep 7
#define BarrierCubeWidth 12
#define TankSize QSize( 50, 54 )
#define BulletSize QSize( 7, 12 )
#define SceneSize QSize( 780, 650 )
#define BarrierItemSize QSize( 15, 15 )

enum Complicity {
    Simple              = 0x0000,
    Hard                = 0x0001,
    Harder              = 0x0002
};
enum Gift {
    NoGift              = 0x0010,
    Armor               = 0x0020,
    Spade               = 0x0030
};
enum ItemType {
    Gamer               = 0x0100,
    Opponent            = 0x0200,
    Barrier             = 0x0300,
    Bullet              = 0x0400,
    Explosion           = 0x0500,
    Tank                = 0x0600
};
enum BarrierType {
    Brick               = 0x1000,
    Concrete            = 0x2000,
    Grass               = 0x3000,
    Water               = 0x4000,
    COA                 = 0x5000
};
enum Direction {        // members describe the rotation angles
    Up                  = 0,
    Right               = 90,
    Down                = 180,
    Left                = 270
};

typedef QPointF Position;

class TankItem;
class GamerTank;
class BulletItem;
class BarrierItem;
class Battleground;
class OpponentTank;
class QGraphicsView;
class QGraphicsScene;


#endif // NEEDEDTYPES_H
