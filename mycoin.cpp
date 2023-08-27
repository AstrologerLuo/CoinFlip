#include "mycoin.h"
#include<QDebug>
#include<QPixmap>

//MyCoin::MyCoin(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    isWin=false;
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        qDebug()<<"图片 %1 加载失败"<<btnImg;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    timer1= new QTimer(this);
    timer2= new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1").arg(min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(min>max)
        {
            min=1;
            timer1->stop();
            isAnimation=false;
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1").arg(max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(max<min)
        {
            max=8;
            timer2->stop();
            isAnimation=false;
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if(isAnimation||isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isAnimation=true;
        flag=false;
    }
    else
    {
        timer2->start(30);
        isAnimation=true;
        flag=true;
    }
}
