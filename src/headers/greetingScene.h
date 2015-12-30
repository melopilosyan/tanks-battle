#ifndef GREETINGSCENE_H
#define GREETINGSCENE_H

#include "neededTypes.h"
#include <QGraphicsScene>


/*
*   Class GreetingScene - privides greeting dialog for game
*
*/
class GreetingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GreetingScene();
    ~GreetingScene();

    void configureView();

signals:
    void exit();
    void start( int );

protected:
    void keyPressEvent( QKeyEvent* );

private:
    int m_levelNum;
    int m_cursorStep;
    Direction m_direction;
    const QSize m_sceneSize;
    QGraphicsTextItem* m_levelNumText;
    QGraphicsPixmapItem* m_cursor;
};

#endif // GREETINGSCENE_H
