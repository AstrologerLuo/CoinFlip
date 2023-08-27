#include "dataconfig.h"

DataConfig::DataConfig(QWidget *parent)
    : QWidget{parent}
{
    int array1[4][4]={{1,1,1,1},
                      {1,1,0,1},
                      {1,0,0,0},
                      {1,1,0,1}};
    QVector<QVector<int>> v;
    for (int i = 0; i < 4; i++)
    {
        QVector<int> v1;
        for(int j = 0; j < 4; j++)
        {
            v1.push_back(array1[i][j]);
        }
        v.push_back(v1);
    }
    mData.insert(1,v);

    int array2[4][4]={{1,0,1,1},
                      {0,0,1,1},
                      {1,1,0,0},
                      {1,1,0,1}};
    v.clear();
    for (int i = 0; i < 4; i++)
    {
        QVector<int> v1;
        for(int j = 0; j < 4; j++)
        {
            v1.push_back(array2[i][j]);
        }
        v.push_back(v1);
    }
    mData.insert(2,v);
}
