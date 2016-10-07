#include "makeselected.h"
#include "tabclass.h"
//#include "twoheaders.h"
#include "commands.h"


MakeSelected::MakeSelected (qreal w, qreal h , int d, QWidget *widget)
{
    width = w;
    height = h;
    del = d;
    selected = false;
    setWasShift( false );
    wasSelected = false;
    setShiftPressed(false);
    renderSelected = false;
    mouseWasPressed = false;
    shiftPressedOnce = false;
    rectWidth = del;
    rectHeight = del;
    delX = 0;
    delY = 0;
    itemsCount = 0;
    //itemToDraw = false;
  //  itemToDraw = NotDraw;
    horizCells = int (width / del);
    vertCells = int (height / del);
    sceneArray.reserve(horizCells);
    QVector <int> tmp (vertCells,0);
  //  qDebug() << "horiz=" << width << ' ' << height;
    drawFunctions[0] = &MakeSelected::drawCross;
    drawFunctions[1] = &MakeSelected::drawCorn;
	drawFunctions[2] = &MakeSelected::drawCrossed;
    drawFunctions[3] = &MakeSelected::drawMiddle;
	drawFunctions[4] = &MakeSelected::drawM;
    drawFunctions[5] = &MakeSelected::drawBrick;
    //drawFunctions = new DrawFunctionsPtr[2];
  //  DrawFunctionsPtr drawFunctions[6] = {&MakeSelected::drawCorn,&MakeSelected::drawCross,
  //                                       &MakeSelected::drawCorn,&MakeSelected::drawCross,
 //                                        &MakeSelected::drawCorn,&MakeSelected::drawCross};
    //drawFunctions[] = {drawCorn,drawCross};
  //  drawFunctions[0] = &MakeSelected::drawCross ;
  //  drawFunctions[1] = &MakeSelected::drawCorn ;
  //  drawFunctions = new drawFunctionsPtr [5];
   // drawFunctions[0] = drawCorn;
  /*  drawFunctionsPtr drawFunctions[2] =
        {
            &MakeSelected::drawCross,
            &MakeSelected::drawCorn
        };*/
   //vector<int> c(n, -1);
   for (unsigned int i = 0; i < horizCells; i ++)
   {
     //  sceneArray[i].reserve(vertCells);
     //  for (unsigned int j = 0; j < vertCells; j ++)
     //      sceneArray[i][j] << 0;
       sceneArray.append(tmp);
   }
   selectedArrayXSize = 0;
   selectedArrayYSize = 0;
   selectedArray = nullptr;
   wasDeleted = true;
   copied = false;
   int a,b,rez;
   a = 7;
   b = 2;
   rez = a/b;

   qDebug() << "rez=" << dynamic_cast<TabClass *>(widget)->test;

   qst = dynamic_cast<TabClass *>(widget)->undoStack;
  // qDebug() << qst;
    //installSceneEventFilter(this);
}


MakeSelected::~MakeSelected()
{
}

QPointF MakeSelected::getStartPoint()
{
    return startPoint;
}

QPointF MakeSelected::getEndPoint()
{
    return endPoint;
}

QPointF MakeSelected::getOldStartPoint()
{
    return oldStartPoint;
}

QPointF MakeSelected::getOldEndPoint()
{
    return oldEndPoint;
}

void MakeSelected::setStartPoint(QPointF pf)
{
    startPoint = pf;
}

void MakeSelected::setEndPoint(QPointF pf)
{
   endPoint = pf;
}


void MakeSelected::setRenderSelected(bool meaning)
{
    renderSelected = meaning;
}


void MakeSelected::setWasShift(bool meaning)
{
    wasShift = meaning;
}

void MakeSelected::setShiftPressed(bool meaning)
{
    shiftPressed = meaning;
}


void MakeSelected::setMouseWasPressed(bool meaning)
{
    mouseWasPressed = meaning;
}

bool MakeSelected::getMouseWasPressed(void)
{
    return  mouseWasPressed;
}

void MakeSelected::setShiftPressedOnce(bool meaning)
{
    shiftPressedOnce = meaning;
}

void MakeSelected::rotateClockWise()
{
    rotate(false);
}


void MakeSelected::rotateCounterClockWise()
{
    rotate(true);
}

void MakeSelected::saveAsImage()
{
    qDebug() << "save";
}


void MakeSelected::rotate(bool clo)
{
    if (selectedArray != nullptr)
    {
       // int halfx = selectedArrayXSize / 2;
       // int halfy = selectedArrayYSize / 2;
        int ysize = selectedArrayXSize;
        int xsize = selectedArrayYSize;

        // locateNew Array
        int ** array1;
        array1 = new int *[xsize];
        for (int i = 0; i <xsize; i ++)
        {
           array1[i] = new int [ysize];
        }
        int k = 0;
        int k1 = 0;
        for (int i = 0; i < selectedArrayXSize; i++)
        {
            k1 = i;
            if ( clo )
                k1 = selectedArrayXSize -i -1;
            for (int j = 0; j < selectedArrayYSize; j++)
            {
             //   qDebug() << "i = " << i << ' ' <<j <<' ' << selectedArray[i][j];
                k = j;
                if ( !clo )
                    k = selectedArrayYSize - j - 1;
               // int j1 = selectedArrayYSize - j;
               // qDebug() << "j1 " << j1;
               // array1 [j][i] = selectedArray[i][selectedArrayYSize - j - 1];
                 array1 [j][i] = selectedArray[k1][k];
            }
        }

     //   showArray(selectedArray, selectedArrayXSize, selectedArrayYSize );
      //  showArray(array1, xsize, ysize );
        deleteArray(selectedArray, selectedArrayXSize);
        ///

        int delt = ( selectedArrayXSize -selectedArrayYSize ) * del  / 2 ;
       // delt = Math.floor ( delt );
        int xn = setToGrid(startPoint.x() +  delt);
        int yn = setToGrid(startPoint.y() -  delt);
        int xk = setToGrid(endPoint.x() -  delt);
        int yk = setToGrid(endPoint.y() +  delt);


        //var xn = maker.select.lastSelected.xb + clockWise * delt;
        //var yn = maker.select.lastSelected.yb - clockWise * delt;
      //  if ( yn < 0 ) yn = 0;
        ///
        selectedArrayXSize = xsize;
        selectedArrayYSize = ysize;

        if (xn <0)
        {
            xn = 0;
            xk = selectedArrayXSize*del;
        }
        if (yn <0)
        {
            yn = 0;
            yk = selectedArrayYSize*del;
        }
        if (xk > width)
        {
            xk = width;
            xn = xk - selectedArrayXSize*del;
        }
        if (yk > height )
        {
            yk = height;
            yn = yk - selectedArrayYSize*del;
        }
        startPoint.setX(xn);
        startPoint.setY(yn);
        endPoint.setX(xk);
        endPoint.setY(yk);
      //  qDebug() << "x="<< yn <<' '<< yk;
        selectedArray = array1;
     //   showArray(selectedArray, selectedArrayXSize, selectedArrayYSize );

       // deleteArray(array1,xsize);

    }

    renderSelected = true;
    this->update();
    qDebug() << "rotate";
}

void MakeSelected::flipHorizontally()
{
    flip(false);
}


void MakeSelected::flipVertically()
{
    flip(true);
}


void MakeSelected::pasteSelected(QPointF point1)
{
    if ( copied )
    {
        qDebug () << "pste";
        int xp = point1.x();
        int yp = point1.y();
        startPoint.setX(xp);
        startPoint.setY(yp);
        endPoint.setX(xp + selectedArrayXSize*del);
        endPoint.setY(yp + selectedArrayYSize*del);
        renderSelected = true;
        this->update();
    }
}

void MakeSelected::copySelected()
{
    copied = true;
    qDebug () << "set to clip";
}

void MakeSelected::cutSelected()
{

}

void MakeSelected::flip(bool vert)
{
    if (selectedArray != nullptr)
    {

        int halfx = selectedArrayXSize / 2;
        int halfy = selectedArrayYSize / 2;
        if (! vert )
        {
            for (int i = 0; i < selectedArrayYSize; i++) // horiz
            {
                for (int j = 0; j < halfx; j++)
                {
                  //   qDebug() << "v "<<i<<' '<<j <<' '<<selectedArrayXSize - j - 1;
                  //   qDebug() << "and " << selectedArray [j][i] << ' ' << selectedArray [selectedArrayXSize - j - 1][i] ;
                    int tmp = selectedArray [j][i];
                    selectedArray [j][i] =selectedArray [selectedArrayXSize - j - 1][i];
                    selectedArray [selectedArrayXSize - j - 1][i] =  tmp;
                }
            }
        }
        else
        {
            for (int i = 0; i < selectedArrayXSize; i++)
            {
                for (int j = 0; j <halfy; j++)
                {
                   // qDebug() << "v "<<i<<' '<<j <<' '<<selectedArrayYSize - j - 1;
                    //qDebug() << "and " << selectedArray [i][j] << ' ' << selectedArray [i][selectedArrayYSize - j - 1] ;
                    int tmp = selectedArray [i][j];
                   selectedArray [i][j] =selectedArray [i][selectedArrayYSize - j-1];
                    selectedArray [i][selectedArrayYSize - j-1] =  tmp;

                }
            }
        }
        // showSelectedArray( );
       }
    renderSelected = true;
    this->update();
}

void MakeSelected::showArray(int **array1, int xlen, int ylen )
{
   // int sz = 33;
   int sz = xlen;
    char reg[31] =      "  0  1  2  3  4  5  6  7  8  9";
    char regEmpty[31] = "                              ";
    reg[30] = '\0';
    regEmpty[30] = '\0';
    if ( sz > 0 )
    {
        int dec = sz / 10;
        int ost = sz % 10;
        char* str = new char[dec * 30 + ost * 3 + 2 + 1];
        char* str1 = new char[dec * 30 + ost * 3 + 2 + 1];
        str [dec * 30 + ost * 3 + 2] = '\0';
        int i;
        str [0] = ' ';
        str[1] = ' ';
        str1[0] = ' ';
        str1[1] = ' ';
        str1[2] = ' ';
        str1[3] = ' ';
        str1[4] = '\0';
      //  qDebug () << "len " <<  dec * 30 + ost * 3 + 2 + 1;
        int k1 = 4;
        for (i = 0; i < dec; i ++ )
        {
            char strdig[3] = "";
            itoa(i%10, strdig, 10);
            strcpy(str+ i * 30+2, reg);
            str1[k1] = strdig[0];
            k1 ++;
            for (int k = 0; k < 29;k ++)
            {
                str1[k1] = ' ';
                k1 ++;
            }
          //  str1[k1] = strdig[0];
          //  k1 ++;
         //   regEmpty [2] = strdig[0];
          //  strcpy(str1+ i * 30+2, regEmpty);
        }
    //    qDebug() << "k1 =" << k1;
        str1[k1] = '\0';
        int j1 = 0;
        int j = 0;
        for (j = 0; j < ost * 3; j +=3)
        {
            char strdig[3] = "";
            itoa(j1, strdig, 10);
            str[i*30+j+2] = ' ';
            str[i*30+j+1+2] = ' ';
            str[i*30+j+2+2] = strdig[0];
           // qDebug() << strdig[0] << ' ' <<ost << ' ' << dec;
            j1 ++;
        }
        str [i * 30 + j+2] = '\0';
   //     qDebug () << "len1 " <<  i * 30 +j;
       //  str [i * 30 + j] = '\0';
        qDebug() << str1;
        qDebug() << str;
     //   str = "";
        str[0] = ' ';
        str[1] = ' ';
        for (int i1 = 0; i1 < ylen; i1 ++ )
        {
                int k2 = 2;
                for (int j1 = 0; j1 < xlen; j1 ++)
                {
                  //  qDebug() << "k2 " << k2;
                   // str[k2] = 'a';
                    char strdig[3] = "";
                    itoa(array1[j1][i1], strdig, 10);
                    if (array1[j1][i1] < 10)
                    {
                        str[k2] = ' ';
                        k2 ++;
                        str[k2] = ' ';
                        k2 ++;
                        str[k2] = strdig[0];
                        //qDebug () << "di" << strdig[0];
                    }
                    else
                    {
                        str[k2] = ' ';
                        k2 ++;
                        str[k2] = strdig[0];
                        k2 ++;
                        str[k2] = strdig[1];
                     //   qDebug () << "in arr " << selectedArray[j1][i1];
                    }
                    k2 ++;
                }
                str[k2] = '\0';
                qDebug() << str;
        }
        delete str;
        delete str1;
     }

}


void MakeSelected::showSelectedArray(void )
{
    showArray(selectedArray,selectedArrayXSize,selectedArrayYSize);

}

void MakeSelected::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  /*  event->ignore();
   QPointF point2 = event->scenePos();//get global position according to ur parent-child relationship
    QPainter painter(this);
    painter->drawRect(origPoint, point2);*/
  /*  bool ctrl = (event->modifiers() == Qt::ControlModifier);

    QPainterPath tmpPath = selectionArea();
    if(tmpPath.isEmpty())
    {
      // if ctrl pressed, then toggle selection
      emit select(event->scenePos(), ctrl);
    }
    else
    {
      // if ctrl pressed, then add selection
      emit select(tmpPath, ctrl);
    }   */
 //  itemToDraw = 0;
  if ( selected )
  {

        //MakeSelected::coord1 cc = getNumberInArray(startPoint);
       // int sx = cc.i;
       // int sy = cc.j;
        // first point
      if ( !shiftPressed )
      {
            selectedArrayXSize = int ( (endPoint.x() - startPoint.x()) / del  );// + sx;
            selectedArrayYSize= int ( (endPoint.y() - startPoint.y()) / del  ); //+ sy;
           // addSelectedArray(); it s to mousepress after selected
         //    this->update();
            // not was
            renderSelected = true;
            QUndoCommand *selectCommand = new SelectCommand(this);
            qst ->push(selectCommand);
            qDebug() << "mouse release " << startPoint.x();
      }
      else
      {
          QUndoCommand *moveCommand = new MoveCommand(this);
          qst ->push(moveCommand);
      }
      if ( wasDeleted == true)
      {
          if ( itemsCount > 0)
          {
              locateSelectedArray();
              fillSelectedArray();
          }
          else
              qDebug() << "item count zero";
      }
      else qDebug() << "was deleted false";

    }
    else
    {
//        deleteSelectedArray();
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void MakeSelected::deleteAllInside(void)
{
    if (selected && selectedArray != nullptr )
    //if (selectedArray != nullptr )
    {
        //qDebug() << "delete all inside";
        deleteSelectedArray();
        this->update();
    }
    else qDebug() << "delete all inside nullptr";
}

void MakeSelected::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if( selected )
    {
        if ( shiftPressed == false )
        {
         //  qDebug() <<" not shift";
            endPoint = event->scenePos();
           // int xend = int (endPoint.x() / del ) * del;
          //  int yend = int (endPoint.y() / del ) * del;
            if ( endPoint.x() > width ) endPoint.setX(width);
            if ( endPoint.y() > height ) endPoint.setY(height);
            int xend = setToGrid(endPoint.x());
            int yend = setToGrid(endPoint.y());
            endPoint.setX(xend);
            endPoint.setY(yend);
            rectWidth = endPoint.x() - startPoint.x();
            rectHeight = endPoint.y() - startPoint.y();
    //        qDebug() << "xx=" << xend << ' ' << yend <<' '<< startPoint.x();
            this->update();
        }
        else
        { // shift Pressed
           //whereClickedWithShift =
            QPointF  tmp = event->scenePos();
            int sx = setToGrid(tmp.x()+delX);
            int sy = setToGrid(tmp.y()+delY);
            // getNumber
            startPoint.setX(sx);
            startPoint.setY(sy);
           // startPoint.setY(tmp.y()+delY);
            endPoint.setX(startPoint.x() + rectWidth);
            endPoint.setY(startPoint.y() + rectHeight);

            this->update();
          // qDebug() <<"shift "<< rectWidth;
        }
    }
    else // draw
    {
        QPointF  tmp = event->scenePos();
        int sx = setToGrid(tmp.x());//+delX);
        int sy = setToGrid(tmp.y());//+delY);
        // getNumber
        startPoint.setX(sx);
        startPoint.setY(sy);
        MakeSelected::coord1 cc = getNumberInArray(startPoint);
     //   int cellX = cc.i;
     //   int cellY = cc.j;
        int b = event->buttons() & Qt::LeftButton;
       // qDebug() << "butt" <<  b;
        if( b )
        {
         //   qDebug() << "in move "<< cc.i << ' ' << cc.j;
            //  drawElement(cc); // here is the bottle neck
            int cellX = cc.i;
            int cellY = cc.j;
            if ( sceneArray[cellX][cellY] == 0 )
            {
                 QUndoCommand *addCommand = new AddCommand(this,cc);
                 qst ->push(addCommand);
            }

        }
   // else
     }
        QGraphicsItem::mouseMoveEvent(event);

}

void MakeSelected::setRedCoordinates(void)
{

}

void MakeSelected::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // startPoint = event->scenePos();
  // itemToDraw = false;
   qDebug() << "pressed";
   if( selected )
   {
       mouseWasPressed = true;
        qDebug() << "selectednddd " << shiftPressed;
       if ( shiftPressed == false )
       {
           if ( selectedArray != nullptr )
           {
               qDebug() << "added 3 ";
             addSelectedArray();
             deleteSelectedArray();
           }
         //  qDebug() << "no shift in press";
            startPoint = event->scenePos();
            int xbeg = setToGrid(startPoint.x());
            int ybeg = setToGrid(startPoint.y());
            startPoint.setX(xbeg);
            startPoint.setY(ybeg);
            endPoint.setX(xbeg+del);
            endPoint.setY(ybeg+del);
            rectWidth = 10;
            rectHeight = 10;

       //     qDebug() << "no shift in press " << rectWidth;
            this->update();
       }
       else
       { // shift pressed
          whereClickedWithShift =  event->scenePos();
        //  qDebug() << "x1 " <<  startPoint.x() << ' ' << whereClickedWithShift.x();
         // qDebug() << "y1 " <<  startPoint.y() <<' ' << whereClickedWithShift.y();
          qreal sx = startPoint.x() - whereClickedWithShift.x();
          qreal sy = startPoint.y() - whereClickedWithShift.y();
          qreal ex = endPoint.x() - whereClickedWithShift.x();
          qreal ey = endPoint.y() - whereClickedWithShift.y();
        //  qDebug() << "x11 " <<  sx << ' ' << sy << ' '<< ex <<' '<< ey;
          if ( sx <= 0
                 && sy <= 0
                 && ex > 0
                 && ey > 0 )
          {
            delX = setToGrid(sx);
            delY = setToGrid(sy);

          }
          else qDebug() << "not in the area";
       }
   }
   else  // draw
   {
        startPoint = event->scenePos();

    /*   MakeSelected::coord1 cc = getNumberInArray(origPoint);
       int cellX = 0;
       int cellY = 0;
       cellX = cc.i;
       cellY = cc.j;*/
       MakeSelected::coord1 cc = getNumberInArray(startPoint);
       if(event->button() == Qt::LeftButton)
       {
           qDebug() << "nnnooo selectedddd";
           int cellX = cc.i;
           int cellY = cc.j;
           if ( sceneArray[cellX][cellY] == 0 )
           {
               QUndoCommand *addCommand = new AddCommand(this,cc);
               qst ->push(addCommand);
           }
       }
       else // right button
       {
           int elemType = getElemType(cc);
           if ( elemType > 0 )
           {
                QUndoCommand *deleteCommand = new DeleteCommand( this, cc, elemType );
                qst ->push(deleteCommand);
           }

       }
       int xbeg = setToGrid(startPoint.x());
       int ybeg = setToGrid(startPoint.y());
       startPoint.setX(xbeg);
       startPoint.setY(ybeg);

   }
   QGraphicsItem::mousePressEvent(event);
}

int MakeSelected::getElemType(MakeSelected::coord1 cc)
{
    int cellX = cc.i;
    int cellY = cc.j;
    return sceneArray[cellX][cellY];
}

void MakeSelected::removeElement(MakeSelected::coord1 cc)
{
    int cellX = cc.i;
    int cellY = cc.j;
    int etype = getElemType(cc);
    if ( sceneArray[cellX][cellY] > 0 )
    {
          if ( etype  <= 4 )
          {
               sceneArray[cellX][cellY] = 0;
          }
          else if ( etype < 10 )
          {
              sceneArray[cellX][cellY] = 0;
              sceneArray[cellX+1][cellY] = 0;
          }
          else
          {
              sceneArray[cellX][cellY] = 0;
              sceneArray[cellX-1][cellY] = 0;
          }
          itemsCount --;
      }
          qDebug() << "else than left" << itemsCount;
          this->update();
         //  itemToDraw = Delete;
  //            }
}

void MakeSelected::drawElement(MakeSelected::coord1 cc)
{
  //  MakeSelected::coord1 cc = getNumberInArray(startPoint);
    int cellX = cc.i;
    int cellY = cc.j;
    qDebug() << "itemmmm " << itemsCount;
     //   qDebug() << "itemmmm " << sceneArray[cellX][cellY] << ' ' << cellX << ' ' << cellY;
  //  if ( sceneArray[cellX][cellY] == 0 )
  //  {
         //itemToDraw = Draw;
         switch (choice)
         {
             case MakeCross:
             case MakeCorn:
             case MakeCrossed:
             case MakeMiddle:
             //     itemToDraw = Draw;
                  sceneArray[cellX][cellY] = choice;
                  itemsCount ++;
             break;
             case MakeM:
             case MakeBrick:
                 if ( sceneArray[cellX+1][cellY] == 0 )
                 {
                   //  itemToDraw = Draw;
                     sceneArray[cellX][cellY] = choice;
                     sceneArray[cellX+1][cellY] = choice*10;
                     itemsCount ++;
                 }
                 else
                 {
                   //  itemToDraw = NotDraw;
                 }
             break;
             default:
             break;
         }
        //     itemsCount ++;
          //   qDebug() << "icount =" <<  itemsCount;
             this->update();
     //   }
}


void MakeSelected::fillSelectedArray()
{
    MakeSelected::coord1 cc = getNumberInArray(startPoint);
    int begx = cc.i;
    int begy = cc.j;
    int i1 = 0;
    int j1 = 0;
  //  qDebug() << begx << ' '<<begy << ' ' << begx+selectedArrayXSize << ' ' <<begy+selectedArrayYSize;
    for ( int i = begx; i < begx + selectedArrayXSize; i ++)
    {
        j1 = 0;
        for ( int j = begy; j < begy + selectedArrayYSize ; j ++)
        {
            //if ( selectedArray[i1][j1] > 0)
            selectedArray[i1][j1] = sceneArray[i][j];
            sceneArray[i][j] = 0;
            if ( sceneArray[i][j] > 0)
            {
               // selectedArray[i1][j1] = sceneArray[i][j];
               // sceneArray[i][j] = 0;
                itemsCount --;
              //  qDebug() <<"fillselectedarray " <<itemsCount;
            }

             //          ' '<<selectedArray[i1][j1] << ' '<<selectedArrayYSize;
            j1 ++;
        }
        i1 ++;
    }
  /*  for (int i = 0 ; i < selectedArrayXSize; i ++)
    {
        for ( int j = 0; j < selectedArrayYSize ; j ++)
            qDebug() << "i="<< i << ' ' << "j="<<j << ' ' << selectedArray[i][j];
    }*/
}

void MakeSelected::locateSelectedArray()
{
    qDebug() << "locate";
    if ( itemsCount > 0 && selectedArray == nullptr )
    {
          selectedArray = new int *[selectedArrayXSize];
          for (int i = 0; i < selectedArrayXSize; i ++)
          {
              selectedArray[i] = new int [selectedArrayYSize];
           //   for (int k = 0; k < selectedArrayYSize; k++)
                  //selectedArray[i][k] = 0;
                 // selectedArray[i][k] = 1;
          }
          wasDeleted = false;
    }

}



void MakeSelected::deleteSelectedArray()
{
    qDebug() << "delete selected array";
    if ( selectedArray != nullptr )
    {
        deleteArray(selectedArray,selectedArrayXSize);
    /*  for( int i = 0; i < selectedArrayXSize; i++ )
      {
        //  qDebug() << "deleted " << selectedArrayXSize << ' ' << selectedArrayYSize;
             delete [] selectedArray[i];
       }
        delete selectedArray;*/
       selectedArray = nullptr;
       wasDeleted = true;
    }
}


void MakeSelected::deleteArray(int **array1,int xlen)
{
    qDebug() << "delete selected array";
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

int MakeSelected::setToGrid( qreal t )
{
    int s;
    s = int ( t / del ) *del;
    //s = round( s );
   // return s;
     return (int) floor(s + 0.5);
}


void MakeSelected::paint (QPainter *painter,
                          const QStyleOptionGraphicsItem *, QWidget *)
{
    //int cellX = 0;
    //int cellY = 0;
    if ( selected )
    {
     //   qDebug() << "paint selected";
        QPointF topLeft (startPoint);
        QPointF bottomRight ( endPoint);
        QRectF rect (topLeft, bottomRight);
        painter->setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
         //painter->drawRoundRect(rect,25,25);

         painter->drawRect(rect);
       /*  if (wasDeleted)
         {
             clearArea(painter);
             qDebug() << "was deleted in paint";

         }
         else qDebug() << "was not deleted in paint";*/
       //  qDebug() << "renren" << renderSelected;
         if ( shiftPressed || renderSelected )
         {
            if (shiftPressedOnce)
            {
                oldStartPoint = startPoint;
                oldEndPoint = endPoint;
                shiftPressedOnce = false;
            }
         //   qDebug() << "here is shift or render";

        //    if ( renderSelected ) renderSelected = false; // here is the problem

         }
        // renderSelectedArea(painter); goes to the new start point when mouse prfessed
         //addSelectedArray();
        // if (renderSelected) qDebug() << " render";

        // renderArea(painter);
     }
     else
    {
        qDebug() << "cleared";
       // clearArea(painter); why is this here

    }
    if ( selectedArray != nullptr )
    {
      //  qDebug() << "shift in paint and render";
        renderSelectedArea(painter); // here pay attention to shift

    }
    else qDebug() << "no selected array";
     renderArea(painter);
 }

void MakeSelected ::clearArea(QPainter *painter)
{
    QPointF topLeft (startPoint);
    QPointF bottomRight ( endPoint);
    QRectF rect (topLeft, bottomRight);
    QColor c (0,0,250,125);
    //painter->setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    painter->setPen(QPen(c, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawRect(rect);
}


bool MakeSelected ::addSelectedArray(void)
{
    if (selectedArray == nullptr)
    {
       // qDebug () << "in add nulllll";
        return false;
    }
    qDebug () << "in add " << startPoint.x() <<' '<<selectedArrayXSize ;
    MakeSelected::coord1 cc = getNumberInArray(startPoint);
    int sx = cc.i;
    int sy = cc.j;
    int i1 = 0;
    int j1 = 0;
    for (int i = sx; i < sx + selectedArrayXSize; i ++)
    {
        j1 = 0;
        for (int j = sy; j < sy + selectedArrayYSize; j ++)
        {
            //if ( sceneArray[i][j] == 0 )
            if ( selectedArray[i1][j1] > 0 && sceneArray[i][j] == 0 )
            {
                sceneArray[i][j] = selectedArray[i1][j1];
                itemsCount ++;
               // qDebug() << "added to "<< itemsCount;
            }
            //else
            j1 ++;
        }
        i1 ++;
    }
    renderSelected = false;
    return true;
}

void MakeSelected :: renderSelectedArea(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    //int begx= startPoint.x();
    //int begy= startPoint.y();
    MakeSelected::coord1 cc = getNumberInArray(startPoint);
    int bx = cc.i;
    int by = cc.j;
    int i1 = 0;
   //  qDebug() << "in="<< bx << ' ' << by <<' '<<selectedArrayXSize << ' ' << selectedArrayYSize;
    for (int i = bx; i < bx + selectedArrayXSize; i++)
    {
        int j1 = 0;
        for (int j = by ; j < by + selectedArrayYSize; j ++)
        {
            //int dei = sceneArray [i][j];
            int dei = selectedArray [i1][j1];
        //    qDebug() << "dei="<< i1 << ' ' << j1 <<' '<< dei;
       // (this->*drawFunctions[ choice - 1 ])( painter );
            if ( dei > 0 )
            {
                if ( dei < 20)
                {
                 //   qDebug()<< "i=" << i << " j=" << j << " " << dei;
               //     drawCross1(painter,i * del, j * del, i * del + del, j * del + del);
                    int xb = i * del;
                    int yb = j * del;
                    int xe = xb + del;
                    int ye = yb + del;
                   (this->*drawFunctions[ dei-1 ])( painter, xb, yb, xe, ye );
                    // here think of coordinates
                 //   painter->drawLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
                 //   painter->drawLine(endPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());
                }
            }
            j1 ++;
        }
        i1 ++;
    }
}


void MakeSelected :: renderArea(QPainter *painter)
{
   // qDebug() << "here render scene array " << horizCells;
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    for (unsigned int i = 0; i < horizCells; i++)
    {
        for (unsigned int j = 0 ; j < vertCells; j ++)
        {
            int dei = sceneArray [i][j];
       // (this->*drawFunctions[ choice - 1 ])( painter );
            if ( dei > 0 )
            {
                if ( dei < 20)
                {
                 //   qDebug()<< "i=" << i << " j=" << j << " " << dei;
               //     drawCross1(painter,i * del, j * del, i * del + del, j * del + del);
                    int xb = i * del;
                    int yb = j * del;
                    int xe = xb + del;
                    int ye = yb + del;
                   (this->*drawFunctions[ dei-1 ])( painter, xb, yb, xe, ye );
                    // here think of coordinates
                 //   painter->drawLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
                 //   painter->drawLine(endPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());
                }
            }
        }
    }
}



void MakeSelected ::drawCross(QPainter *painter, int xb, int yb, int xe, int ye)
{
    painter->drawLine(xb,yb,xe,ye);
    painter->drawLine(xe,yb,xb,ye);
    // painter->drawLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
    // painter->drawLine(endPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());
   // qDebug() << "cross cross";
}

void MakeSelected ::drawCorn(QPainter *painter, int xb, int yb, int xe, int ye)
{
    xe = 0;
    ye = 0;
    QPointF centerEllipse;
    centerEllipse.setX(xb+del / 2);
    centerEllipse.setY(yb + del / 2);
    painter->drawEllipse(centerEllipse,del/2 - 2,del/2 - 1);
  /*  centerEllipse.setX(startPoint.x()+del / 2);
    centerEllipse.setY(startPoint.y() + del / 2);
    qDebug() << "xssx=" << centerEllipse.x() << ' ' << centerEllipse.y();
    painter->drawEllipse(centerEllipse,del/2 - 2,del/2 - 1);*/
}

void MakeSelected ::drawCrossed(QPainter *painter, int xb, int yb, int xe, int ye)
{
        painter->drawLine(xb + del/2,yb+1,
                       xe-1,ye-2);
        painter->drawLine(xb + del/2,yb+1,
                       xb+1,ye-2);
        painter->drawLine(xb+1,ye-1,xe-2,ye-2);
  /*  painter->drawLine(startPoint.x() + del/2,startPoint.y()+1,
                   endPoint.x()-1,endPoint.y()-2);
    painter->drawLine(startPoint.x() + del/2,startPoint.y()+1,
                   startPoint.x()+1,endPoint.y()-2);
    painter->drawLine(startPoint.x()+1,endPoint.y()-1,endPoint.x()-2,endPoint.y()-2);*/
}

void MakeSelected ::drawMiddle(QPainter *painter, int xb, int yb, int xe, int ye)
{
    xe = 0;
   // ye = 0;
    ye = yb + del;
     painter->drawLine(xb + del/2, yb+1,
        xb + del/2, ye - 1);
   // endPoint.setY(startPoint.y() + del);
   // painter->drawLine(startPoint.x() + del/2, startPoint.y()+1,
     //    startPoint.x() + del/2, endPoint.y() - 1);
}

void MakeSelected ::drawM(QPainter *painter, int xb, int yb, int xe, int ye)
{
   // xe = xb + del;
   // ye = yb + del;
    painter->fillRect(xb+1,yb + 1,2 * del - 2, del - 2,Qt::white);
    painter->drawLine(xb+1,yb+1,xb+ del,ye-1);
    painter->drawLine(xb+ del,ye-1,xe+del- 1,yb+1);
    /*endPoint.setX(startPoint.x() + del);
    endPoint.setY(startPoint.y() + del);
    painter->fillRect(startPoint.x()+1,startPoint.y() + 1,2 * del - 2, del - 2,Qt::white);
    painter->drawLine(startPoint.x()+1,startPoint.y()+1,startPoint.x()+ del,endPoint.y()-1);
    painter->drawLine(startPoint.x()+ del,endPoint.y()-1,endPoint.x()+del- 1,startPoint.y()+1);*/

}

void MakeSelected ::drawBrick(QPainter *painter, int xb, int yb, int xe, int ye)
{
    xe = 0;
    ye = 0;
     painter->fillRect(xb+1,yb + 1,2 * del - 2, del - 2,Qt::white);
    // painter->fillRect(startPoint.x()+1,startPoint.y() + 1,2 * del - 2, del - 2,Qt::white);
}

QRectF MakeSelected::boundingRect() const
{
    return QRectF(0,0,width,height);
}

MakeSelected::coord1 MakeSelected::getNumberInArray( QPointF p )
{
    coord1 c;
    c.i = floor( p.x() / del );
    c.j = floor( p.y() / del );
    return c;
}

MakeSelected::Choice MakeSelected::getChoice()
{
    return choice;
}

void MakeSelected::setChoiceSimple(Choice cho)
{
    choice = cho;
}

void MakeSelected::setChoice(Choice cho)
{
   choice = cho;
   if ( choice == 0 )
   {
       setSelected (true);
       wasSelected = true;
   }
   else
   {
       setSelected (false);
       copied = false;
       if (wasSelected)
       {
          // qDebug() << "was selected ";
           if ( wasShift || selectedArray != nullptr)
           {
               qDebug() << "added 1 ";
               wasShift = false;
               addSelectedArray();
               deleteSelectedArray();
           }
           else qDebug() << " not was shift ";
           wasSelected = false;
         //  addSelectedArray();
       /*    if ( selectedArray != nullptr )
           {
               qDebug() << "added 2 ";
             addSelectedArray();
             deleteSelectedArray();
           }*/
           this->update();
       }
      // else qDebug() << "not was selected ";
   }
   //this->addLine( QLineF( 10, 10, 30, 30 ),QPen(Qt::red, 1) );
  // this->addLine( QLineF( 10, 30, 30, 10 ) );
 //  qDebug() << "cho=" << choice;
}

void MakeSelected::setSelected(bool meaning)
{
    //selected = !selected;
    selected = meaning;
}

/*
void MakeSelected::setChoice(Choice choice)
{
    thisChoice = choice;
}*/
