#include "makeselected.h"
#include "tabclass.h"
//#include "twoheaders.h"
#include "commands.h"
#include "functions.h"


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
    locateSceneArray();
  //  qDebug() << "horiz=" << width << ' ' << height;
    drawFunctions[0] = &MakeSelected::drawCross;
    drawFunctions[1] = &MakeSelected::drawCorn;
	drawFunctions[2] = &MakeSelected::drawCrossed;
    drawFunctions[3] = &MakeSelected::drawMiddle;
	drawFunctions[4] = &MakeSelected::drawM;
    drawFunctions[5] = &MakeSelected::drawBrick;
    drawFunctions[6] = &MakeSelected::drawBigElement;


   selectedArrayXSize = 0;
   selectedArrayYSize = 0;
   //selectedArray = nullptr;
   selectedArray.clear();
   wasDeleted = true;
   copied = false;
   int a,b,rez;
   a = 7;
   b = 2;
   rez = a/b;

 //  qDebug() << "rez=" << dynamic_cast<TabClass *>(widget)->test;
 //  setChoiceSimple(Choice(1));
   qst = dynamic_cast<TabClass *>(widget)->undoStack;
  // qDebug() << qst;
    //installSceneEventFilter(this);
}

void MakeSelected::locateSceneArray()
{

    allocateVector( sceneArray, horizCells, vertCells );
}

void MakeSelected::deleteSceneArray()
{

    deleteVectorContent( sceneArray, horizCells );

}

void MakeSelected::setHorizCells(int h)
{
    horizCells = h;
}

void MakeSelected::setVertCells(int v)
{
    vertCells = v;
}


void MakeSelected::resizeSceneArray(unsigned int h, unsigned int v)
{

    setSelected(false);
    if (h > horizCells)
    {
        qDebug() << "here is vector hor" <<  ' '<<horizCells << ' ' << h<<' '<< h -horizCells ;
        QVector <int> tmp (vertCells);
        for (unsigned int i = 0; i < h - horizCells; i ++)
            sceneArray.append(tmp);
        horizCells = h;
        width = h * del;
       // sceneArray.resize(h);
    }
    else if (h < horizCells)
    {
        sceneArray.resize(h);
        horizCells = h;
        width = h * del;
    }

    if (v != vertCells)
    {
        qDebug() << "here is vector vert";
        vertCells = v;
        height = v * del;
        for (unsigned int i = 0; i < horizCells; i ++)
        {
            sceneArray[i].resize(v);
        }
    }

   // this->update();
}

void MakeSelected::fillSceneArray(QVector< QVector<int> > sA)
{
    itemsCount = 0;
    qDebug() << "cells " << horizCells << ' '<<vertCells;
    for (int i = 0; i < horizCells; i ++)
    {
        for (int j =0; j < vertCells; j ++)
        {
            sceneArray[i][j] = sA[i][j];
            if ( sA[i][j] > 0 && sA[i][j] < 10  )
                itemsCount ++;
        }
    }
}

MakeSelected::~MakeSelected()
{
    if (itemsCount > 0)
    {
        deleteSelectedArray();
        deleteSceneArray();
    }
}

QPointF MakeSelected::getStartPoint()
{
    return startPoint;
}

QVector<QVector<int> > *MakeSelected::getSceneArray()
{
    return  &sceneArray;
}

void MakeSelected::setSceneArray(QVector<QVector<int> > sA)
{
  //  deleteSceneArray();
    //locateSceneArray();
    sceneArray = sA;
}

int MakeSelected::getHorizCells()
{
    return horizCells;
}

int MakeSelected::getVertCells()
{
    return vertCells;
}


QPointF MakeSelected::getEndPoint()
{
   // qDebug() << "here is the end point " << endPoint;
    return endPoint;
}

QPointF MakeSelected::getOldStartPoint()
{
    return oldStartPoint;
}

QPointF MakeSelected::getOldEndPoint()
{
    //qDebug() << "here is the end point " << oldEndPoint;
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
 //   QUndoCommand *rotateCommand = new FlipRotateCommand(this,false,false);
 //   qst ->push(rotateCommand);

}


void MakeSelected::rotateCounterClockWise()
{
    rotate(true);
 //   QUndoCommand *rotateCommand = new FlipRotateCommand(this,true,false);
 //   qst ->push(rotateCommand);
}

void MakeSelected::saveAsImage()
{
   // qDebug() << "save";
}


void MakeSelected::rotate(bool clo)
{
    //if (selectedArray != nullptr)
  //
    qDebug() << "rotate";
    if (selectedArray.size() != 0)
    {
       // int halfx = selectedArrayXSize / 2;
       // int halfy = selectedArrayYSize / 2;
        int xsize = selectedArrayXSize;
        int ysize = selectedArrayYSize;

        // locateNew Array
        //int ** array1 = nullptr;
        QVector< QVector<int> > array1;
        allocateVector( array1, ysize, xsize );
      //was  locateArray(array1,xsize,ysize);

     /*   array1 = new int *[xsize];
        for (int i = 0; i <xsize; i ++)
        {
           array1[i] = new int [ysize];
        }*/

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


      //  showSelectedArray();
     //   showArray(array1, ysize, xsize );
        deleteVectorContent( selectedArray, selectedArrayXSize );
    // was    deleteArray(selectedArray, selectedArrayXSize);
        ///

        int delt = ( selectedArrayXSize -selectedArrayYSize ) * del  / 2 ;
       // delt = Math.floor ( delt );
        int xn = setToGrid(startPoint.x() +  delt);
        int yn = setToGrid(startPoint.y() -  delt);
     //   int xk = setToGrid(endPoint.x() -  delt);
     //   int yk = setToGrid(endPoint.y() +  delt);




        //var xn = maker.select.lastSelected.xb + clockWise * delt;
        //var yn = maker.select.lastSelected.yb - clockWise * delt;
      //  if ( yn < 0 ) yn = 0;
        ///
        selectedArrayXSize = ysize;
        selectedArrayYSize = xsize;
        int xk = xn + selectedArrayXSize * del;
        int yk = yn + selectedArrayYSize * del;
         qDebug() << "sizes " << yn << ' ' << yk << ' '<<selectedArrayYSize << ' ' << delt;
        if (xn <0)
        {
            qDebug() << "less 1";
            xn = 0;
            xk = selectedArrayXSize*del;
        }
        if (yn <0)
        {
            qDebug() << "less 2";
            yn = 0;
            yk = selectedArrayYSize*del;
        }
        if (xk > width)
        {
            qDebug() << "more 1";
            xk = width;
            xn = xk - selectedArrayXSize*del;
        }
        if (yk > height )
        {
            qDebug() << "more 2";
            yk = height;
            yn = yk - selectedArrayYSize*del;
        }
        startPoint.setX(xn);
        startPoint.setY(yn);
        endPoint.setX(xk);
        endPoint.setY(yk);
      //  qDebug() << "sizes " << startPoint << ' ' << endPoint;
      //  qDebug() << "sizes " << selectedArrayXSize << ' ' << selectedArrayYSize;
        selectedArray = array1;

       // showSelectedArray();
     //   showArray(selectedArray, selectedArrayXSize, selectedArrayYSize );
        deleteVectorContent( array1,ysize );
       // deleteArray(array1,xsize);

    }

    renderSelected = true;
    this->update();
   // qDebug() << "rotate";
}

void MakeSelected::flipHorizontally()
{
   // flip(false);
    QUndoCommand *flipCommand = new FlipRotateCommand(this,false,true);
    qst ->push(flipCommand);
}


void MakeSelected::flipVertically()
{
    QUndoCommand *flipCommand = new FlipRotateCommand(this,true,true);
    qst ->push(flipCommand);
   // flip(true);
}

void MakeSelected::clearSelected(QPointF point1)
{
    if (selectedArray.size() == 0)
    {
        qDebug () << "in clear nulllll";
     //   return false;
    }
    qDebug () << "in clear " << startPoint.x() <<' '<<selectedArrayXSize ;
    MakeSelected::coord1 cc = getNumberInArray(point1);
    int sx = cc.i;
    int sy = cc.j;
    int i1 = 0;
    int j1 = 0;
    for (int i = sx; i < sx + selectedArrayXSize; i ++)
    {
        j1 = 0;
        for (int j = sy; j < sy + selectedArrayYSize; j ++)
        {
            if ( selectedArray[i1][j1] > 0 )// && sceneArray[i][j] == 0 )
            {
                sceneArray[i][j] = 0;
                int etype = selectedArray[i1][j1];
                if ( etype  <10 )
                {
                    itemsCount --;
                }
            }
            //else
            j1 ++;
        }
        i1 ++;
    }
    renderSelected = false;
      // return true;
}

void MakeSelected::pasteSelected(QPointF point1, bool current)
{
    if ( copied )
    {
      //  qDebug () << "copied true ";
        if ( current )
            addSelectedArray(); // only for current

        int xp = point1.x();
        int yp = point1.y();
       // qDebug () << "pste " << xp ;
        startPoint.setX(xp);
        startPoint.setY(yp);
        rectWidth = selectedArrayXSize*del;
        rectHeight = selectedArrayYSize*del;
        endPoint.setX(xp + rectWidth);
        endPoint.setY(yp + rectHeight);
        renderSelected = true;
        wasDeleted = false;
        this->update();
    }
    else  qDebug () << "copied false ";
}

void MakeSelected::setCopied(bool meaning)
{
    copied =  meaning;
}

bool MakeSelected::copySelected()
{
    //if (selectedArray != nullptr)
    if (selectedArray.size() != 0)
        copied = true;
    else copied = false;
  //  qDebug () << "set to clip";
    return copied;
}

void MakeSelected::cutSelected()
{

}

void MakeSelected::flip(bool vert)
{
    qDebug() << "flip flip";
    //if (selectedArray != nullptr)
    if (selectedArray.size() != 0)
    {
        qDebug() << "sel flip";
        int d1;
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
                 //   if ( tmp > 4 && tmp < 10 ) tmp = 0;
                 //   if ( tmp > 10 ) tmp = tmp/10;
                  //  if (tmp > 0)
                   //  qDebug() << "yt=" << tmp;
                  //  if (selectedArray [j][i] > 0)
                 //   qDebug() << "yt=" << selectedArray [j][i];

                    d1 = selectedArray [selectedArrayXSize - j - 1][i];
                  //  was1 = false;
                 /*   if ( selectedArray [selectedArrayXSize - j - 1][i] > 10 )
                    {
                        d1 = selectedArray [selectedArrayXSize - j - 1][i] /10;
                        tmp = 0;
                    }*/
                    selectedArray [j][i] = d1;
                    selectedArray [selectedArrayXSize - j - 1][i] =  tmp;
               //     if ( was1 ) selectedArray [selectedArrayXSize - j - 1][i] = 0;
                    //if (selectedArray [j][i] > 0)

                   // if (selectedArray [j][i] > 10 ) selectedArray [j][i] = selectedArray [j][i] / 10;
                   // if (selectedArray [j][i] > 4 && selectedArray [j][i] < 10) selectedArray [j][i] = 0;
                }
                for (int j = 0; j <selectedArrayXSize-1; j++)
                {
                    if (selectedArray [j][i] > 10 )
                    {
                        selectedArray [j][i] = selectedArray [j][i] / 10;
                        selectedArray [j+1][i] = selectedArray [j+1][i] * 10;
                        j ++;
                    }
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
   // else qDebug() << "no sel flip";
    renderSelected = true;
    this->update();
}

void MakeSelected::showArray(QVector< QVector<int> > array1, int xlen, int ylen )
//void MakeSelected::showArray(int **array1, int xlen, int ylen )
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
 // if (shiftPressed && !selected) wasDeleted = true;
  if ( selected )
  {

        //MakeSelected::coord1 cc = getNumberInArray(startPoint);
       // int sx = cc.i;
       // int sy = cc.j;
        // first point
      if ( !shiftPressed )
      {
          // qDebug() << "in relese not shift";
            if ( endPoint.x() < startPoint.x() )
            {
                int tmp;
                tmp = endPoint.x();
                endPoint.setX( startPoint.x() );
                startPoint.setX( tmp );
            }
            if ( endPoint.y() < startPoint.y() )
            {
                int tmp;
                tmp = endPoint.y();
                endPoint.setY( startPoint.y() );
                startPoint.setY( tmp );
            }
            // not was check edge
            int x1 = getNumberInArray(startPoint).i;
            int x2 = getNumberInArray(endPoint).i-1;
            int y1 = getNumberInArray(startPoint).j;
            int y2 = getNumberInArray(endPoint).j;



            bool empty =  checkSelectedArrayEmpty();
            bool leftP = false;
            bool rightP = false;
            for (int i = y1; i < y2; i++)
            {
                   // here think about the big element

                   if ( sceneArray[x1][i] > 10 && !leftP)
                   {
                       startPoint.setX(startPoint.x() - del);
                       rectWidth += del;
                       leftP = true;
                   }
                   if ( sceneArray[x2][i] < 10 && sceneArray[x2][i] > 4 && !rightP )
                   {

                       endPoint.setX(endPoint.x() + del);
                       rectWidth += del;
                       rightP = true;
                    }
             }
            //////////////
            selectedArrayXSize = int ( (endPoint.x() - startPoint.x()) / del  );// + sx;
            selectedArrayYSize= int ( (endPoint.y() - startPoint.y()) / del  ); //+ sy;
           // addSelectedArray(); it s to mousepress after selected
         //    this->update();
            qDebug() << "mouse release " << endPoint.x();
            renderSelected = true;
            QUndoCommand *selectCommand = new SelectCommand(this);
            qst ->push(selectCommand);

           // qDebug() << "mouse release " << getNumberInArray(startPoint).i << ' '
            //         << getNumberInArray(startPoint).j <<' '<< getNumberInArray(endPoint).i
             //        << getNumberInArray(endPoint).j;
      }
      else
      {
        //  showArray(selectedArray, selectedArrayXSize, selectedArrayYSize );
          QUndoCommand *moveCommand = new MoveCommand(this);
          qst ->push(moveCommand);
         // qDebug() << "mouse release " << startPoint.x();
      }
      if ( wasDeleted == true)
      {
         // qDebug() << "was deleted true";
       /*   if ( itemsCount > 0)
          {
             bool located = locateSelectedArray();
             if ( located )
                fillSelectedArray();
            //  qDebug() << "after fill ";
          }
          else
              qDebug() << "item count zero";*/
          makeSelectedArray();
      }
    //  else qDebug() << "was deleted false";

    }
    else
    {
//        deleteSelectedArray();
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void MakeSelected::makeSelectedArray()
{

    if ( itemsCount > 0)
    {
       bool located = locateSelectedArray();
       if ( located )
          fillSelectedArray();
        qDebug() << "after fill ";
    }
    else
        qDebug() << "item count zero";
}

void MakeSelected::setItemsCount(int c)
{
    itemsCount = c;
}


int MakeSelected::getItemsCount(void)
{
    return itemsCount;
}


bool MakeSelected::checkSelectedArrayEmpty()
{
    return true;
}

void MakeSelected::deleteAllInside(void)
{
    //if (selected && selectedArray != nullptr )
    if (selected && selectedArray.size() != 0 )
    //if (selectedArray != nullptr )
    {
        //qDebug() << "delete all inside";
        deleteSelectedArray();
        this->update();
    }
   // else qDebug() << "delete all inside nullptr";
}

void MakeSelected::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if( selected )
    {
        if ( shiftPressed == false )
        {
          // qDebug() <<" not shift";
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
        QPointF pf;
        pf.setX(sx);
        pf.setY(sy);
    //    startPoint.setX(sx);
      //   qDebug() << "xxx=" ;
     //   startPoint.setY(sy);
     //   MakeSelected::coord1 cc = getNumberInArray(startPoint);
       MakeSelected::coord1 cc = getNumberInArray(pf);
       bool res = checkNumber(cc);
       if ( res )
       {
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
    //                drawElement(cc);
                   QUndoCommand *addCommand = new AddCommand(this,cc);
                   qst ->push(addCommand);
                }

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
   /* if (shiftPressed && !selected)
    {
         qDebug() << "sh pressed";
    }
    else
        qDebug() << "not sh pressed"; */
   if( selected )
   {
       mouseWasPressed = true;
        qDebug() << "selectednddd " << shiftPressed;
       if ( shiftPressed == false )
       {
           //if ( selectedArray != nullptr )
           if ( selectedArray.size() != 0 )
           {
               qDebug() << "added 3 ";
             addSelectedArray();
             deleteSelectedArray();

           }
            else qDebug() << "added 4 ";
            startPoint = event->scenePos();
            int xbeg = setToGrid(startPoint.x());
            int ybeg = setToGrid(startPoint.y());
            startPoint.setX(xbeg);
            startPoint.setY(ybeg);

            endPoint.setX(xbeg+del);
            endPoint.setY(ybeg+del);
       //     qDebug() << "no shift in press " << endPoint.x() << endPoint.y() ;
            rectWidth = 10;
            rectHeight = 10;
        //    qDebug() << "no shift in press " << rectWidth; // look here
            this->update();
       }
       else
       { // shift pressed
          whereClickedWithShift =  event->scenePos();
       //   qDebug() << "x11 " <<  endPoint.x() << ' ' << whereClickedWithShift.x();
       //   qDebug() << "y1 " <<  startPoint.y() <<' ' << whereClickedWithShift.y();
          qreal sx = startPoint.x() - whereClickedWithShift.x();
          qreal sy = startPoint.y() - whereClickedWithShift.y();
          qreal ex = endPoint.x() - whereClickedWithShift.x();
          qreal ey = endPoint.y() - whereClickedWithShift.y();
       //   qDebug() << "x11 " <<  sx << ' ' << sy << ' '<< ex <<' '<< ey;
          if ( sx <= 0
                 && sy <= 0
                 && ex > 0
                 && ey > 0 )
          {
            delX = setToGrid(sx);
            delY = setToGrid(sy);

          }
       //   else qDebug() << "not in the area";
       }
   }
   else  // draw
   {
       // startPoint = event->scenePos();
       QPointF pf = event->scenePos();
    /*   MakeSelected::coord1 cc = getNumberInArray(origPoint);
       int cellX = 0;
       int cellY = 0;
       cellX = cc.i;
       cellY = cc.j;*/
       //MakeSelected::coord1 cc = getNumberInArray(startPoint);

        MakeSelected::coord1 cc = getNumberInArray(pf);
        bool res = checkNumber(cc);
       if ( res )
       {
           if(event->button() == Qt::LeftButton)
           {
             //  qDebug() << "nnnooo selectedddd";
               int cellX = cc.i;
               int cellY = cc.j;
               if ( sceneArray[cellX][cellY] == 0 )
               {
                 //  drawElement(cc);
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
       }
     //  int xbeg = setToGrid(startPoint.x());
     //  int ybeg = setToGrid(startPoint.y());
    //   startPoint.setX(xbeg);
     //  startPoint.setY(ybeg);

   }
   QGraphicsItem::mousePressEvent(event);
}

bool MakeSelected::checkNumber(MakeSelected::coord1 cc)
{

    int cx = cc.i;
    if (cx == sceneArray.size()-1 )
    {
         if ( choice == 5 || choice == 6 )
         {
            return false;
         }
    }
    if ( cx >= sceneArray.size() )
                return false;
    int cy = cc.j;
    if ( cy >= sceneArray[0].size() ) return false;
    return true;
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
       //   qDebug() << "else than left" << itemsCount;
          this->update();
         //  itemToDraw = Delete;
  //            }
}

void MakeSelected::drawElement(MakeSelected::coord1 cc)
{
  //  MakeSelected::coord1 cc = getNumberInArray(startPoint);
    int cellX = cc.i;
    int cellY = cc.j;
  //  qDebug() << "itemmmm " << itemsCount;
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
    qDebug() << "filled";
    MakeSelected::coord1 cc = getNumberInArray(startPoint);

    int begx = cc.i;
    int begy = cc.j;
    int i1 = 0;
    int j1 = 0;
    if ( selectedArray.size() == 0  ) qDebug() << "null";
    else qDebug() << "not null " << selectedArrayXSize << ' ' << selectedArrayYSize ;
   // qDebug() << "tut " << begx << ' '<<begy << ' ' << begx+selectedArrayXSize << ' ' <<begy+selectedArrayYSize;
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


int MakeSelected:: getSelectedArrayXSize()
{
   // qDebug() << "xsi " << selectedArrayXSize;
    return selectedArrayXSize;
}

int MakeSelected:: getSelectedArrayYSize()
{
    return selectedArrayYSize;
}

void MakeSelected:: setSelectedArrayXSize(int sz)
{
    selectedArrayXSize = sz;
}

void MakeSelected:: setSelectedArrayYSize(int sz)
{
    selectedArrayYSize = sz;
}
/*
void MakeSelected:: setSelectedArray(int **arr)
{
    // was selectedArray = arr;
}
*/
void MakeSelected:: setSelectedArray(QVector< QVector<int> > arr)
{
    selectedArray = arr;
}
/*
int ** MakeSelected::getSelectedArray()
{
    int ** tmp = nullptr;
    // was return selectedArray;
    return tmp;
}*/

QVector<QVector<int> > *MakeSelected::getSelectedArray()
{
   //nt ** tmp = nullptr;
    return &selectedArray;
   //eturn tmp;
}


bool MakeSelected::locateSelectedArray()
{
   // qDebug() << "locate!!! " << selectedArrayXSize << ' ' << selectedArrayYSize ;
    if ( selectedArrayXSize == 0 ) return false;
    if ( selectedArrayYSize == 0 ) return false;
    //if ( itemsCount > 0 && selectedArray == nullptr )
    // wasif ( itemsCount > 0 && selectedArray.size() == 0 )
    if ( selectedArray.size() == 0 )
    {
      //  qDebug() << "locate 111" << selectedArrayXSize << ' ' << selectedArrayYSize << ' ' << selectedArray.size() ;
       /*   selectedArray = new int *[selectedArrayXSize];
          for (int i = 0; i < selectedArrayXSize; i ++)
          {
              selectedArray[i] = new int [selectedArrayYSize];
           //   for (int k = 0; k < selectedArrayYSize; k++)
                  //selectedArray[i][k] = 0;
                 // selectedArray[i][k] = 1;
          }*/
       // selectedArray = locateArray1(selectedArrayXSize, selectedArrayYSize);
        allocateVector( selectedArray,selectedArrayXSize, selectedArrayYSize );
       //  qDebug() << "locate " << selectedArrayXSize << ' ' << selectedArrayYSize << ' '<< selectedArray.size();
        //locateArray(selectedArray,selectedArrayXSize, selectedArrayYSize);
          wasDeleted = false;
    }
    return true;
}

void MakeSelected::fillSelectedArrayfromOutside(QVector< QVector<int> > array)
{
    if (selectedArray.size() > 0) deleteSelectedArray();
    bool located = locateSelectedArray();
    if ( located )
    {
       // qDebug() << "true loca " << selectedArrayXSize << ' ' <<selectedArrayYSize << selectedArray.size() ;
       // QVector< QVector<int> > sA = *tabwid->mSelected->getSelectedArray();
       for ( int i = 0; i < selectedArrayXSize; i ++)
       {
           for ( int j = 0; j < selectedArrayYSize; j ++)
           {
              // qDebug() << "iii=" << i << ' ' << j << ' ' << array[i][j];
               selectedArray[i][j] = array[i][j];
           }
       }
    }
   // else  qDebug() << "false loca";
    /* was selectedArray = new int *[selectedArrayXSize];
    for (int i = 0; i < selectedArrayXSize; i ++)
    {
        selectedArray[i] = new int [selectedArrayYSize];
    }
    // copy content
    for ( int i = 0; i < selectedArrayXSize; i ++)
    {
        for ( int j = 0; j < selectedArrayYSize; j ++)
        {
            selectedArray[i][j] = array[i][j];
        }
    }*/

}

void MakeSelected::doUpdate()
{
    this->update();
}


void MakeSelected::deleteSelectedArray()
{
  //  qDebug() << "delete selected array";
   /* was  if ( selectedArray != nullptr )
    {
      // was  deleteArray(selectedArray,selectedArrayXSize);
    //  for( int i = 0; i < selectedArrayXSize; i++ )
      //{
        //  qDebug() << "deleted " << selectedArrayXSize << ' ' << selectedArrayYSize;
        //     delete [] selectedArray[i];
       //}
       // delete selectedArray;
       selectedArray = nullptr;
       selectedArrayXSize = 0;
       selectedArrayYSize = 0;
       wasDeleted = true;
    }*/

    deleteVectorContent( selectedArray,  selectedArrayXSize );
   // qDebug() << "delete selected array " << selectedArray.size();
    //selectedArray = nullptr;
    selectedArrayXSize = 0;
    selectedArrayYSize = 0;
    wasDeleted = true;
}


//void MakeSelected::deleteArray(int **array1,int xlen)

int MakeSelected::setToGrid( qreal t )
{
    return setToGridCommon(t,del);
   /* int s;
    s = int ( t / del ) *del;
    //s = round( s );
   // return s;
     return (int) floor(s + 0.5);*/
}


int MakeSelected::getDel()
{
    return del;
}

void MakeSelected::paint (QPainter *painter,
                          const QStyleOptionGraphicsItem *, QWidget *)
{
    //int cellX = 0;
    //int cellY = 0;
   //  qDebug() << " in paint ";
    if ( selected )
    {
        qDebug() << " in selected ";
        if ( endPoint.x() > width )
        {
            endPoint.setX(width);
            startPoint.setX(width - selectedArrayXSize*del);
        }
        if ( startPoint.x() < 0 )
        {
            startPoint.setX(0);
            endPoint.setX(selectedArrayXSize*del);
        }
        if ( endPoint.y() > height )
        {
            endPoint.setY(height);
            startPoint.setY(height - selectedArrayYSize*del);
        }
        if ( startPoint.y() < 0 )
        {
            startPoint.setY(0);
            endPoint.setY(selectedArrayYSize*del);
        }
        QPointF topLeft (startPoint);
        QPointF bottomRight ( endPoint);
        QRectF rect (topLeft, bottomRight);
        painter->setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
       // qDebug() << "in paint " << startPoint.x() << ' ' << endPoint.x() << ' ' << selectedArray.size();
         //painter->drawRoundRect(rect,25,25);
      //  qDebug() << "was deleted in paint" <<  endPoint.x() << ' ' <<  endPoint.y() <<
     //              startPoint.x() << ' ' <<  startPoint.y() ;
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
              //  qDebug() << "renren " << endPoint;
                oldStartPoint = startPoint;
                oldEndPoint = endPoint;
                shiftPressedOnce = false;
            }

        //    if ( renderSelected ) renderSelected = false; // here is the problem

         }
        // renderSelectedArea(painter); goes to the new start point when mouse prfessed
         //addSelectedArray();
        // if (renderSelected) qDebug() << " render";

        // renderArea(painter);
     }
     else
    {
        // not selected
      //  qDebug() << "cleared";
       // clearArea(painter); why is this here

    }
    //if ( selectedArray != nullptr )
    renderArea(painter);
    if ( selectedArray.size() != 0 )
    {
      //  qDebug() << "shift in paint and render where selected";
        renderSelectedArea(painter); // here pay attention to shift

    }
    else qDebug() << "no selected array";
     //renderArea(painter);
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
    //if (selectedArray == nullptr)
    if (selectedArray.size() == 0)
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
            if ( selectedArray[i1][j1] > 0 )// && sceneArray[i][j] == 0 )
            {
                if (sceneArray[i][j] == 0) itemsCount ++;
                int etype = selectedArray[i1][j1];
             //   qDebug() << "s=" << etype;
                if ( etype  <= 4 )
                {
                    int oldType = sceneArray[i][j];
                    if ( oldType <=4  );
                    else if ( oldType < 10 )
                    {
                        sceneArray[i+1][j] = 0;
                    }
                    else
                    {
                        sceneArray[i-1][j] = 0;
                    }
                    sceneArray[i][j] = selectedArray[i1][j1];
                     // qDebug() << "s=" <<
                }
                else if ( etype < 10 )
                {
                    sceneArray[i][j] = etype;
                    sceneArray[i+1][j] = etype*10;
                }
                else
                {
                    sceneArray[i][j] = etype;
                    sceneArray[i-1][j] = etype/10;
                }
                //itemsCount ++;
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
  //  qDebug() << "render selected area";
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
       //     qDebug() << "dei="<< i1 << ' ' << j1 <<' '<< dei;
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
                    if (sceneArray [i][j] > 0)
                    {
                    //    qDebug() << "clear cell";
                        clearCell(painter, xb, yb, xe, ye);
                    }
                   (this->*drawFunctions[ dei-1 ])( painter, xb, yb, xe, ye );
                    // here think of coordinates
                 //   painter->drawLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
                 //   painter->drawLine(endPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());
                }
                else;// qDebug() << "other";
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
  //  painter->drawLine(width+50,0, width+50, 120);
  //  painter->drawLine(0,height+30,50, height30);
}
/*
void MakeSelected::checkSelectedArr()
{
    for (int i = 0; i < selectedArrayXSize; i ++)
        for (int j = 0; j < selectedArrayXSize; j ++)

}*/

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

void MakeSelected ::clearCell(QPainter *painter, int xb, int yb, int xe, int ye)
{
    xe = 0;
    ye = 0;
    painter->fillRect(xb+1,yb + 1,del - 2, del - 2,Qt::white);
    // painter->fillRect(startPoint.x()+1,startPoint.y() + 1,2 * del - 2, del - 2,Qt::white);
}

void MakeSelected ::drawBrick(QPainter *painter, int xb, int yb, int xe, int ye)
{
    xe = 0;
    ye = 0;
     painter->fillRect(xb+1,yb + 1,2 * del - 2, del - 2,Qt::white);
    // painter->fillRect(startPoint.x()+1,startPoint.y() + 1,2 * del - 2, del - 2,Qt::white);
}

void MakeSelected ::drawBigElement(QPainter *painter, int xb, int yb, int xe, int ye)
{
    // here I wll
   // xe = 0;
  //  ye = 0;
   //  painter->fillRect(xb+1,yb + 1,2 * del - 2, del - 2,Qt::white);
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
   // qDebug() << "sdfad" << c.i <<' '<< c.j;
    return c;
}

MakeSelected::Choice MakeSelected::getChoice()
{
    qDebug() << "in get cho " << (int) choice;
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
           qDebug() << "was selected ";
           //if ( wasShift || selectedArray != nullptr)
           if ( wasShift || selectedArray.size() != 0)
           {
            //   qDebug() << "added 1 ";
               wasShift = false;
             //  addSelectedArray();
             //  deleteSelectedArray();
               QUndoCommand *unselectCommand = new UnSelectCommand(this);
               qst ->push(unselectCommand);
           }
         //  else qDebug() << " not was shift ";
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
       else;// qDebug() << "not was selected ";
   }
   //this->addLine( QLineF( 10, 10, 30, 30 ),QPen(Qt::red, 1) );
  // this->addLine( QLineF( 10, 30, 30, 10 ) );
 //  qDebug() << "in set cho=" << choice;
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
