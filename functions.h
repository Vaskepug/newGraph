#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QDebug>
void deleteArray(int **array1, int xlen);
void locateArray(int ** &array1, int xlen, int ylen);
int ** locateArray1(int xlen,int ylen);
void allocateVector( QVector< QVector<int> > &v, int xlen, int ylen );
void deleteVectorContent( QVector< QVector<int> > &v,  int ylen );
int setToGridCommon( qreal t , int del);
#endif // FUNCTIONS_H
