# Tanks Battle Game

The Qt GUI application using `QGraphicsView` library.

![](/screenshots/greeting.png?raw=true "Game greeting scene")<br/>
![](/screenshots/tanks-1.png?raw=true "The battle starts")<br/>
![](/screenshots/tanks-3.png?raw=true "In the midst of battle")

#### Usage
Download [bin/NewGraphicsTanks.zip](bin/NewGraphicsTanks.zip?raw=true), unzip on Ubuntu (compiled on 22.04), run the `NewGraphicsTanks` executable, enjoy the game :sparkles:

#### Compile from source
Download Qt4.
```sh
cd src

qmake-qt4 NewGraphicsTanks.pro # generates Makefile
make # compiles the project
make clean # cleans build artifacts

./NewGraphicsTanks # runs the game
```

#### Author
[Meliq Pilosyan](https://github.com/melopilosyan)
