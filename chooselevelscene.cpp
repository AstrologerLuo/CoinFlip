#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include<QLabel>
#include<QSoundEffect>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(320,588);
    setWindowIcon(QIcon(":/Image/Coin0001.png"));
    setWindowTitle("选择关卡");
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startBar=bar->addMenu("开始");
    QAction* quitAction=startBar->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSoundEffect* sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(":/Image/TapButtonSound.wav"));
    QSoundEffect* backsound=new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/Image/BackButtonSound.wav"));

    MyPushButton* backbtn=new MyPushButton(":/Image/BackButton.png",":/Image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    connect(backbtn,&QPushButton::clicked,[=](){
        backsound->play();
        emit chooseScenceBack();
    });

    for(int i = 0; i < 20; i++)
    {
        MyPushButton* meaubtn=new MyPushButton(":/Image/LevelIcon");
        meaubtn->setParent(this);
        meaubtn->move(25+i%4*70,130+i/4*70);

        connect(meaubtn,&QPushButton::clicked,[=](){
            sound->play();

            this->hide();
            play=new PlayScence(i+1);
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlayScence::chooseScenceBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });
        });

        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(meaubtn->width(),meaubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/Image/Title.png");
    painter.drawPixmap(0,30,pix.width(),pix.height(),pix);
}
