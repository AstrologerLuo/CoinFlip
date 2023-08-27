#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPixmap>
#include"mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/Image/Coin0001.png"));
    setWindowTitle("翻金币");

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    QSoundEffect* sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(":/Image/TapButtonSound.wav"));

    MyPushButton* startbtn=new MyPushButton(":/Image/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    chooseScence=new ChooseLevelScene;

    connect(chooseScence,&ChooseLevelScene::chooseScenceBack,[=](){
        QTimer::singleShot(300,this,[=](){
            this->setGeometry(chooseScence->geometry());
            chooseScence->hide();
            this->show();
        });
    });
    connect(startbtn,&QPushButton::clicked,[=](){
        sound->play();
        startbtn->zoom1();
        startbtn->zoom2();
        QTimer::singleShot(300,this,[=](){
            chooseScence->setGeometry(this->geometry());
            this->hide();
            chooseScence->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Image/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,0,pix);
}

