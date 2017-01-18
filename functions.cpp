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
