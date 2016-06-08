#include "makegrid.h"


MakeGrid::MakeGrid( int w, int h ,int del) : QGraphicsItem(),
            width1(w), height1(h), del(10)
{

}

void MakeGrid::paint (QPainter *painter,
                      const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // re-draw the grid lines from 0,0 to _width, _height

    // do horizontal first

    //QColor c (200,200,255,125);
    QColor c (0,0,250,125);

    QFont font = painter->font();
    QFontMetrics fm(font);
    int doubleDel = del * 2;
  //  qDebug() << "ff=" << fm.height();
    int thickness = 1;
    painter->setPen( QPen(c, thickness));
    int k = 0;
    int dist = width1;
    //for (int y= doubleDel; y < height1; y+=del)
    for (int y= 0; y < height1; y+=del)
    {
        if ( k % 10  == 0)
        {
            thickness = 2;
            dist = width1+5;
            painter->drawText( dist+2,y+2,QString::number(k));
            //k = 0;
        }
        else
        {
            thickness = 1;
            dist = width1;
        }
        painter->setPen( QPen(c, thickness));
       // painter->drawLine(doubleDel,y, dist, y);
         painter->drawLine(0,y, dist, y);
   /*    char num[3];
        num [0] = ' ';
        num [1] = k + '0';
        num[2] = '\0';
        //painter->drawText( width1+7,y+2, num);
        painter->drawText( width1+7,y+2,QString::number(k));*/
        k ++;
    }
    k = 0;
    dist = height1;
   // for (int x= doubleDel; x < width1; x+=del)
     for (int x=0; x < width1; x+=del)
    {
        if ( k % 10 == 0 )
        {
          //  k = 0;
            thickness = 2;
            dist = height1+5;
            painter->drawText( x-1,dist+2+fm.height(),QString::number(k));
        }
        else
        {
            thickness = 1;
            dist = height1;
        }
        painter->setPen( QPen(c, thickness));
        painter->drawLine(x,0, x, dist);
        k ++;
    }
////////////
 /*   k = 0;
    for (qreal y = top; y < bottom-10; y += gridSize)
    {
        QPointF pointt =  QPointF(right,y+5);
        char num[3];
        num [0] = ' ';
        num [1] = k + '0';
        num[2] = '\0';
        painter->drawText( pointt, num);
        k = k + 1;
        if ( k == 10 ) k = 0;
    }
    k = 0;
    for (qreal x = left; x < right; x += gridSize)
    {
        QPoint pointt = QPoint( x-1, bottom );
        char num[3];
        num [0] = ' ';
        num [1] = k + '0';
        num[2] = '\0';
        painter->drawText( pointt, num);
        k = k + 1;
        if ( k == 10 ) k = 0;
    } */
}

QRectF MakeGrid::boundingRect() const
{
    return QRectF ( static_cast<qreal>(0),
                    static_cast<qreal>(0), static_cast<qreal>(width1),
                    static_cast<qreal>( height1));
}

void MakeGrid::sizeChanged(int w, int h)
{
    width1 = w;
   height1 = h;
}

void MakeGrid::mouseMoveEvent(QGraphicsSceneDragDropEvent *)
{
}

void MakeGrid::mousePressEvent(QGraphicsSceneDragDropEvent *)
{
}

void MakeGrid::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
}

void MakeGrid::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
}

