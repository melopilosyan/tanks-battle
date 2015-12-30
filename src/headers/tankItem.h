#ifndef TANKITEM_H
#define TANKITEM_H

#include "neededTypes.h"
#include <phonon/MediaObject>


/*
*   Class TankItem - provides a tank
*
*/
class TankItem : public QGraphicsPixmapItem
{

public:
    static int count; // Just for debugging
    int num;

    enum { Type = UserType + 1 };

    TankItem( const Position&, Direction, ItemType,
              Complicity complicity = Simple, QGraphicsScene* scene = 0 );
    ~TankItem();

    void fight();
    bool prepareDestroy();
    bool move( Direction );
    bool isType( ItemType ) const;

    void setDirection( Direction );
    void setComplicity( Complicity );

    Direction direction() const;
    Complicity complicity() const;

    virtual int type() const;

protected:
    bool m_destroy;

private:
    QVector<QPixmap> m_pixmaps;
    ItemType m_type;
    Direction m_direction;
    Complicity m_complicity;
    BulletItem* m_myBullet;
    Phonon::MediaObject* m_shotVoice;

    int m_lifeNum;

    bool moveUpDown( Direction );
    bool moveLeftRight( Direction );
    // Return collides item pionter if it is, but not bullets
    // otherwise return NULL
    const QGraphicsItem* collidesWithOtherItems();
};


#endif // TANKITEM_H

