#ifndef MAKESELECTED_H
#define MAKESELECTED_H
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>


class MakeSelected: public QGraphicsItem
{
public:
    typedef void DrawFunctions( QPainter *painter);
    typedef void (MakeSelected::*DrawFunctionsPtr)(QPainter *painter);
    DrawFunctionsPtr drawFunctions[6];
    //DrawFunctionsPtr drawFunctions[2];
  //  drawFunctionsPtr *drawFunctions;
    //void (*functptr[])(QPainter *painter) = { drawCorn, drawCross } ;
    //typedef drawFunctions_ptr drawFunctions[2];
    //drawFunctions *df[] = { drawCross,drawCorn,drawCrossed,drawMiddle,drawM,drawBrick };

    ~MakeSelected();
    MakeSelected(qreal width, qreal height,int del);
    bool wasShift;
    bool shiftPressed;
  //  enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
 //                 MakeMiddle, MakeM, MakeBrick ,SelectMode};
   // void setChoice(Choice choice);
    bool selected;
   // bool itemToDraw;
    void setSelected(void);
    enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
                  MakeMiddle, MakeM, MakeBrick};
    enum ItemBehaviour { NotDraw, Draw, Delete };
    Choice choice;
    ItemBehaviour itemToDraw;
    void setChoice(Choice cho);
//protected:
   // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF startPoint;
    QPointF endPoint;
    QPointF whereClickedWithShift;
    int delX;
    int delY;
    //Choice thisChoice;
     int     del;
    qreal   width;
    qreal   height;
    int rectWidth;
    int rectHeight;
    virtual QRectF boundingRect() const; // must be
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *); // must be
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    int setToGrid( qreal t );
    QVector< QVector<int> > sceneArray;
    unsigned int horizCells;
    unsigned int vertCells;
    struct coord1
     {
         unsigned int i;
         unsigned int j;
     };
    coord1 getNumberInArray( QPointF  );
    void setItemBehaviour(ItemBehaviour );
    //////
   void drawCross1(QPainter *painter,int,int,int,int);
   DrawFunctions drawCross;
   DrawFunctions drawCorn;
   //void drawCorn(QPainter *painter);
   void drawCrossed(QPainter *painter);
   void drawMiddle(QPainter *painter);
   void drawM(QPainter *painter);
   void drawBrick(QPainter *painter);


  //  virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;
  //  virtual void keyPressEvent(QKeyEvent *event);
   // void keyCaught(QKeyEvent *event);
//signals:
  //void keyCaught(QKeyEvent *event);

};

#endif // MAKESELECTED_H
