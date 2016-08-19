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
    typedef void DrawFunctions( QPainter *painter,int,int,int,int);
    typedef void (MakeSelected::*DrawFunctionsPtr)(QPainter *painter,int,int,int,int);
    DrawFunctionsPtr drawFunctions[6];

    ~MakeSelected();
    MakeSelected(qreal width, qreal height,int del);
    bool wasShift;
    bool shiftPressed;
    bool selected;
    bool renderSelected;
    void deleteAllInside(void);
   // bool itemToDraw;
    void setSelected(bool meaning);
    enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
                  MakeMiddle, MakeM, MakeBrick};
 //   enum ItemBehaviour { NotDraw, Draw, Delete };
    Choice choice;
 //   ItemBehaviour itemToDraw;
    void setChoice(Choice cho);
    void flipHorizontally(void);
    void flipVertically(void);
    void rotateClockWise(void);
    void rotateCounterClockWise(void);
    void copySelected();
    void pasteSelected();
    void cutSelected();
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
 //   void setItemBehaviour(ItemBehaviour );
    //////
   /* /// \brief drawCross1
    /// \param painter*/
   void renderArea(QPainter *painter);
   void renderSelectedArea(QPainter *painter);
   void drawCross1(QPainter *painter,int,int,int,int);
   void fillSelectedArray(void);
   bool addSelectedArray();
   DrawFunctions drawCross;
   DrawFunctions drawCorn;
   DrawFunctions drawCrossed;
   DrawFunctions drawMiddle;
   DrawFunctions drawM;
   DrawFunctions drawBrick;
   void drawElement(MakeSelected::coord1 cc);
   int **selectedArray;
   int selectedArrayXSize;
   int selectedArrayYSize;
   int itemsCount;
   bool wasSelected;
   bool wasDeleted;
   bool copied;
   void locateSelectedArray(void);
   void deleteSelectedArray(void);
   void deleteArray(int **array1, int xlen);
   void showArray(int **array1, int xlen,int ylen );
   void clearArea(QPainter *painter);
   void flip(bool);
   void rotate(bool);
   void showSelectedArray(void);
};

#endif // MAKESELECTED_H
