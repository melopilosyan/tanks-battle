#ifndef TANKSVIEW_H
#define TANKSVIEW_H

#include <QGraphicsView>
class TanksScene;
class GreetingScene;


/*
*   Class TanksView - privides a view to show game and greeting scnenes
*
*/
class TanksView : public QGraphicsView
{
    Q_OBJECT

public:
    TanksView();
    ~TanksView();

private slots:
    void switchToMenu();
    void switchToGame( int );

private:
    TanksScene* m_gameScene;
    GreetingScene* m_greetingScene;
};

#endif // TANKSVIEW_H
