#include "functions.h"

void deleteArray(int **array1,int xlen)
{
  //  if ( selectedArray != nullptr )
  //  {
      for( int i = 0; i < xlen; i++ )
      {
        //  qDebug() << "deleted " << selectedArrayXSize << ' ' << selectedArrayYSize;
             delete [] array1[i];
       }
        delete array1;
        //array = nullptr;
//       wasDeleted = true;
   // }
}

void locateArray(int ** &array1,int xlen, int ylen)
{
    qDebug() << "in lock " << ylen << ' ' << xlen;
    array1 = new int *[xlen];
    for (int i = 0; i < xlen; i ++)
    {
        array1[i] = new int [ylen];
     //   for (int k = 0; k < selectedArrayYSize; k++)
            //selectedArray[i][k] = 0;
           // selectedArray[i][k] = 1;
    }
}

int ** locateArray1(int xlen, int ylen)
{
    int ** array1;
    qDebug() << "in lock " << ylen << ' ' << xlen;
    array1 = new int *[xlen];
    for (int i = 0; i < xlen; i ++)
    {
        array1[i] = new int [ylen];
     //   for (int k = 0; k < selectedArrayYSize; k++)
            //selectedArray[i][k] = 0;
           // selectedArray[i][k] = 1;
    }
    return array1;
}


void allocateVector( QVector< QVector<int> > &v, int xlen, int ylen )
{
    QVector <int> tmp (ylen);
   //  qDebug() << "allocated 111" << tmp.size();
    for (unsigned int i = 0; i < xlen; i ++)
    {
      //  sceneArray[i].reserve(vertCells);
      //  for (unsigned int j = 0; j < vertCells; j ++)
      //      sceneArray[i][j] << 0;
        v.append(tmp);
    }
    //qDebug() << "allocated " << v.size();
}

void deleteVectorContent( QVector< QVector<int> > &v,  int ylen )
{
  //  if ( v.size() > 0 )
  //  {
        for (unsigned int i = 0; i < ylen; i ++)
        {
          //  sceneArray[i].reserve(vertCells);
          //  for (unsigned int j = 0; j < vertCells; j ++)
          //      sceneArray[i][j] << 0;
            v[i].clear();
        }
        if ( v.size() > 0 )
            v.clear();
   // }
    //qDebug() << "deleted" << v.size();
}

int setToGridCommon( qreal t , int del)
{
    int s;
    s = int ( t / del ) *del;
    //s = round( s );
   // return s;
     return (int) floor(s + 0.5);
}
