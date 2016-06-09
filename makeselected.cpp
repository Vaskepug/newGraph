#include "makeselected.h"

MakeSelected::MakeSelected (qreal w, qreal h , int d)
{
    width = w;
    height = h;
    del = d;
    selected = false;
    wasShift = false;
    shiftPressed = false;
    rectWidth = del;
    rectHeight = del;
    delX = 0;
    delY = 0;
    //itemToDraw = false;
    itemToDraw = NotDraw;
    horizCells = int (width / del);
    vertCells = int (height / del);
    sceneArray.reserve(horizCells);
    QVector <int> tmp (vertCells,0);
    qDebug() << "horiz=" << width << ' ' << height;
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
       qDebug() << "init array";
       sceneArray.append(tmp);
   }
    //installSceneEventFilter(this);
}

MakeSelected::~MakeSelected()
{
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
    QGraphicsItem::mouseReleaseEvent(event);
}
/*
void MakeSelected::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "move move";
    event->ignore();
     endPoint = event->scenePos();
    if( selected )
    {
        endPoint = event->scenePos();
        int xend = int (endPoint.x() / del ) * del;
        int yend = int (endPoint.y() / del ) * del;
        endPoint.setX(xend);
        endPoint.setY(yend);
        this->update();
    }
    else
        QGraphicsItem::mouseMoveEvent(event);
     QGraphicsItem::mouseMoveEvent(event);

}*/

void MakeSelected::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if( selected )
    {
        if ( shiftPressed == false )
        {
           qDebug() <<" not shift";
            endPoint = event->scenePos();
           // int xend = int (endPoint.x() / del ) * del;
          //  int yend = int (endPoint.y() / del ) * del;
            int xend = setToGrid(endPoint.x());
            int yend = setToGrid(endPoint.y());
            endPoint.setX(xend);
            endPoint.setY(yend);
            qDebug() << "xx=" << xend << ' ' << yend <<' '<< startPoint.x();
            this->update();
        }
        else
        {
           //whereClickedWithShift =
            QPointF  tmp = event->scenePos();
            int sx = setToGrid(tmp.x()+delX);
            int sy = setToGrid(tmp.y()+delX);
            startPoint.setX(sx);
            startPoint.setY(sy);
           // startPoint.setY(tmp.y()+delY);
            endPoint.setX(startPoint.x() + rectWidth);
            endPoint.setY(startPoint.y() + rectHeight);
            this->update();
           qDebug() <<"shift";
        }
    }
   // else
        QGraphicsItem::mouseMoveEvent(event);

}
/*
void MakeSelected::keyCaught(QKeyEvent *event)
{
    qDebug() << "222";
}
*/

void MakeSelected::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   startPoint = event->scenePos();
  // itemToDraw = false;
   if( selected )
   {

       if ( shiftPressed == false )
       {
           qDebug() << "no shift in press";
            int xbeg = setToGrid(startPoint.x());
            int ybeg = setToGrid(startPoint.y());
            startPoint.setX(xbeg);
            startPoint.setY(ybeg);
            endPoint.setX(xbeg+del);
            endPoint.setY(ybeg+del);
            this->update();
       }
       else
       {
          whereClickedWithShift =  event->scenePos();
         // qDebug() << "x1 " <<  startPoint.x() < whereClickedWithShift.x();
          // qDebug() << "y1 " <<  startPoint.y() > whereClickedWithShift.y();
          qreal sx = startPoint.x() - whereClickedWithShift.x();
          qreal sy = startPoint.y() - whereClickedWithShift.y();
          qreal ex = endPoint.x() - whereClickedWithShift.x();
          qreal ey = endPoint.y() - whereClickedWithShift.y();
          if ( sx < 0
                 && sy < 0
                 && ex > 0
                 && ey > 0 )
          {
            delX = setToGrid(sx);
            delY = setToGrid(sy);
            rectWidth = endPoint.x() - startPoint.x();
            rectHeight = endPoint.y() - startPoint.y();
            qDebug() <<"shift in press " << rectWidth << ' '<< rectHeight;
          }
       }
   }
   else // draw
   {
  /*     MakeSelected::coord1 cc = getNumberInArray(origPoint);
       int cellX = 0;
       int cellY = 0;
       cellX = cc.i;
       cellY = cc.j;*/
       MakeSelected::coord1 cc = getNumberInArray(startPoint);
       int cellX = cc.i;
       int cellY = cc.j;
       if(event->button() == Qt::LeftButton)
       {

       //    qDebug() << "itemmmm " << sceneArray[cellX][cellY] << ' ' << cellX << ' ' << cellY;
           if ( sceneArray[cellX][cellY] == 0 )
           {
                //itemToDraw = Draw;
                switch (choice)
                {
                    case MakeCross:
                    case MakeCorn:
                    case MakeCrossed:
                    case MakeMiddle:
                         itemToDraw = Draw;
                         sceneArray[cellX][cellY] = choice;
                    break;
                    case MakeM:
                    case MakeBrick:
                        if ( sceneArray[cellX+1][cellY] == 0 )
                        {
                            itemToDraw = Draw;
                            sceneArray[cellX][cellY] = choice;
                            sceneArray[cellX+1][cellY] = choice*50;
                        }
                        else
                        {
                            itemToDraw = NotDraw;
                        }
                    break;
                    default:
                    break;
                }
                this->update();
           }
           else
             itemToDraw = NotDraw;
           //this->update();
       }
       else
       {
           if ( sceneArray[cellX][cellY] > 0 )
           {
               if ( sceneArray[cellX][cellY]  <= 4 )
               {
                    sceneArray[cellX][cellY] = 0;
               }
               else if ( sceneArray[cellX][cellY] < 10 )
               {
                   sceneArray[cellX][cellY] = 0;
                   sceneArray[cellX+1][cellY] = 0;
               }
               else
               {
                   sceneArray[cellX][cellY] = 0;
                   sceneArray[cellX-1][cellY] = 0;
               }
                            this->update();
                itemToDraw = Delete;
           }
           else itemToDraw = NotDraw;
       }
       int xbeg = setToGrid(startPoint.x());
       int ybeg = setToGrid(startPoint.y());
       startPoint.setX(xbeg);
       startPoint.setY(ybeg);

   }
   QGraphicsItem::mousePressEvent(event);
}

int MakeSelected::setToGrid( qreal t )
{
    int s;
    s = int ( t / del ) *del;
    return s;
}


void MakeSelected::paint (QPainter *painter,
                          const QStyleOptionGraphicsItem *, QWidget *)
{
    int cellX = 0;
    int cellY = 0;
    if ( selected )
    {
        qDebug() << "paint" << startPoint.x() << ' ' <<startPoint.y() ;
        QPointF topLeft (startPoint);
        QPointF bottomRight ( endPoint);
         QRectF rect (topLeft, bottomRight);
        painter->setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
         //painter->drawRoundRect(rect,25,25);

         painter->drawRect(rect);
     }
    else
    {
        MakeSelected::coord1 cc = getNumberInArray(startPoint);
        cellX = cc.i;
        cellY = cc.j;
        int xbeg = cellX *del;
        int ybeg = cellY *del;
     //   int xend = xbeg + del;
     //   int yend = ybeg + del;
        endPoint.setX(startPoint.x() + del);
        endPoint.setY(startPoint.y() + del);

     //   if ( itemToDraw == Draw )
      //  {
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
}



void MakeSelected ::drawCross1( QPainter *painter, int xb, int yb, int xe, int ye )
{
      painter->drawLine(xb,yb,xe,ye);
      painter->drawLine(xe,yb,xb,ye);
   //  painter->drawLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
   //  painter->drawLine(endPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());
    qDebug() << "cross cross";
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
   // ye = yb + del;
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


void MakeSelected::setChoice(Choice cho)
{
   choice = cho;
   //this->addLine( QLineF( 10, 10, 30, 30 ),QPen(Qt::red, 1) );
  // this->addLine( QLineF( 10, 30, 30, 10 ) );
   qDebug() << "cho=" << choice;
}

void MakeSelected::setSelected(void)
{
    selected = !selected;
}

/*
void MakeSelected::setChoice(Choice choice)
{
    thisChoice = choice;
}*/
