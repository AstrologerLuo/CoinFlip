#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QWidget>
#include<QMap>
#include<QVector>

class DataConfig : public QWidget
{
    Q_OBJECT
public:
    explicit DataConfig(QWidget *parent = nullptr);
    QMap<int,QVector<QVector<int> >  >mData;

signals:

};

#endif // DATACONFIG_H
