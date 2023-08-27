#include "playscence.h"
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSoundEffect>


//PlayScence::PlayScence(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

PlayScence::PlayScence(int levelNum)
{
    levelIndex=levelNum;
    setFixedSize(320,588);
    setWindowIcon(QPixmap(":/Image/Coin0001.png"));
    setWindowTitle("翻金币游戏");
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startBar=bar->addMenu("开始");
    QAction* quitAction=startBar->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSoundEffect* backsound=new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/Image/BackButtonSound.wav"));
    QSoundEffect* coinsound=new QSoundEffect(this);
    coinsound->setSource(QUrl::fromLocalFile(":/Image/ConFlipSound.wav"));
    QSoundEffect* winsound=new QSoundEffect(this);
    winsound->setSource(QUrl::fromLocalFile(":/Image/LevelWinSound.wav"));

    MyPushButton* backbtn=new MyPushButton(":/Image/BackButton.png",":/Image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    connect(backbtn,&QPushButton::clicked,[=](){
        backsound->play();
        QTimer::singleShot(300,this,[=](){
            emit this->chooseScenceBack();
        });
    });
    QLabel* label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1=QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);

    DataConfig config;
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    QLabel* winLabel=new QLabel;
    QPixmap winPix;
    winPix.load(":/Image/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,winPix.width(),winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-winPix.width())*0.5,-winPix.height());

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel* label1=new QLabel;
            label1->setGeometry(0,0,50,50);
            label1->setPixmap(QPixmap(":/Image/BoardNode(1).png"));
            label1->setParent(this);
            label1->move(57+i*50,200+j*50);

            QString str1;
            if(this->gameArray[i][j]==1)
            {
                str1=":/Image/Coin0001.png";
            }
            else
            {
                str1=":/Image/Coin0008.png";
            }

            MyCoin* coin=new MyCoin(str1);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];

            coinBtn[i][j] = coin;

            connect(coin,&QPushButton::clicked,[=](){
                coinsound->play();
                for(int i=0;i<4;i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }

                coin->changeFlag();
                gameArray[i][j]=gameArray[i][j]==0?1:0;

                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]= gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]= gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]= gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]= gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    for(int i=0;i<4;i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            coinBtn[i][j]->isWin=false;
                        }
                    }

                    isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                        qDebug()<<"游戏胜利";
                        winsound->play();
                        for(int i=0;i<4;i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }

                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScence::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Image/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
