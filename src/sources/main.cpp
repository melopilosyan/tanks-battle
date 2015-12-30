#include "headers/tanksView.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    app.setApplicationName("TANKS");
    qsrand( QTime::currentTime().second() );
    TanksView gameVew;
    gameVew.show();
    return app.exec();
}
