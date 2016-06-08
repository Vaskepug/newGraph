#include "drawcrosses.h"

DrawCrosses::DrawCrosses(QObject* parent): QGraphicsScene(parent)
{

}

void DrawCrosses::init(unsigned int width, unsigned int height )
{
    choice = Nothing;
    this->setSceneRect(0,0,width,height);
    selected = false;
  /*  itemToDraw = 0;
    horizCells = int (width / del);
    vertCells = int (height / del);
    this->setSceneRect(0,0,width,height);
    sceneArray.reserve(horizCells);
    QVector <int> tmp (vertCells,0);
   // qDebug() << "horiz=" << horizCells << ' ' << vertCells;
     qDebug() << "horiz=" << width << ' ' << height;
    //vector<int> c(n, -1);
    for (unsigned int i = 0; i < horizCells; i ++)
    {
      //  sceneArray[i].reserve(vertCells);
      //  for (unsigned int j = 0; j < vertCells; j ++)
      //      sceneArray[i][j] << 0;
        sceneArray.append(tmp);
    }
   // qDebug() << sceneArray[0][0];
   // g1 = new QGraphicsItemGroup();
 //   this->addItem(g1);*/

}

void DrawCrosses::setChoice(Choice cho)
{
   choice = cho;
}

/*
void DrawCrosses::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  //  if (selected) event->ignore();
    qDebug() << "mouse "<< items();
    QGraphicsScene::mousePressEvent(event);
}


void DrawCrosses::setSelected()
{
   selected = !selected;
}
*/
