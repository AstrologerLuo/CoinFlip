#ifndef PLAYSCENCE_H
#define PLAYSCENCE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScence : public QMainWindow
{
    Q_OBJECT
public:
   //explicit PlayScence(QWidget *parent = nullptr);
    PlayScence(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent*);
    int gameArray[4][4];
    MyCoin* coinBtn[4][4];

    bool isWin;

signals:
    void chooseScenceBack();

};

#endif // PLAYSCENCE_H
