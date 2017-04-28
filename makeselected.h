#ifndef MAKESELECTED_H
#define MAKESELECTED_H
//#include <QObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QUndoStack>

//#include "commands.h"
//#include "tabclass.h"
//#include "twoheaders.h"


class MakeSelected: public QGraphicsItem
{
  //  Q_OBJECT
public:
    typedef void DrawFunctions( QPainter *painter,int,int,int,int);
    typedef void (MakeSelected::*DrawFunctionsPtr)(QPainter *painter,int,int,int,int);
    DrawFunctionsPtr drawFunctions[7];

    ~MakeSelected();
    //MakeSelected(qreal width, qreal height, int del, TabClass *widget);
    MakeSelected(qreal width, qreal height, int del, QWidget *widget);


   // int **selectedArray; // should be private
    QVector< QVector<int> > selectedArray;
    void deleteAllInside(void);
   // bool itemToDraw;
    void setSelected(bool meaning);
    enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
                  MakeMiddle, MakeM, MakeBrick,MakeBigElement};
 //   enum ItemBehaviour { NotDraw, Draw, Delete };
//    Choice choice;
 //   ItemBehaviour itemToDraw;
    void setChoice(Choice cho);
    void setChoiceSimple(Choice cho);
    Choice getChoice();
    void flipHorizontally(void);
    void flipVertically(void);
    void flip(bool);
    void rotateClockWise(void);
    void rotateCounterClockWise(void);
    void rotate(bool);
    bool copySelected();
    void pasteSelected(QPointF point1, bool current);
    void clearSelected(QPointF point1);
    void cutSelected();
    void saveAsImage();
    void setWasShift(bool meaning);
    void setShiftPressed(bool meaning);
    void setShiftPressedOnce(bool meaning);
    bool getMouseWasPressed(void);
    void setMouseWasPressed(bool meaning);
    void setRenderSelected (bool meaning);
    void setCopied(bool meaning);
    bool addSelectedArray();
    void deleteSelectedArray(void);
    void deleteSceneArray();
    int getHorizCells();
    void setHorizCells(int h);
    int getVertCells();
    void setVertCells(int v);
    int getDel();
    QVector<QVector<int> > *getSceneArray();
    void setSceneArray(QVector< QVector<int> >);
    int getSelectedArrayXSize();
    int getSelectedArrayYSize();
    void setSelectedArrayXSize(int sz);
    void setSelectedArrayYSize(int sz);
    void fillSceneArray(QVector< QVector<int> > sA);
    //void setSelectedArray(int **arr);
    void setSelectedArray(QVector< QVector<int> > arr);
    //int ** getSelectedArray();
    QVector< QVector<int> > *getSelectedArray();
    void doUpdate();
    void fillSelectedArrayfromOutside(QVector<QVector<int> > array);
    void makeSelectedArray(void);
    void setItemsCount(int c);
    int getItemsCount(void);
    QPointF getStartPoint();
    QPointF getEndPoint();
    QPointF getOldStartPoint();
    QPointF getOldEndPoint();
    void setStartPoint(QPointF pf);
    void setEndPoint(QPointF pf);
    QWidget widget1;
    QUndoStack *qst;
    void resizeSceneArray(unsigned int h, unsigned int v);
    //TabClass *widget1;
    struct coord1
     {
         unsigned int i;
         unsigned int j;
     };
    void drawElement(MakeSelected::coord1 cc);
    void removeElement(MakeSelected::coord1 cc);
//protected:
   // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
  //  enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
 //                  MakeMiddle, MakeM, MakeBrick};
    Choice choice;
    QPointF startPoint;
    QPointF endPoint;
    QPointF oldStartPoint;
    QPointF oldEndPoint;
    QPointF whereClickedWithShift;

    int delX;
    int delY;
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
    void locateSceneArray();

    unsigned int horizCells;
    unsigned int vertCells;
  /*  struct coord1
     {
         unsigned int i;
         unsigned int j;
     };*/
    coord1 getNumberInArray( QPointF  );
    bool checkNumber(MakeSelected::coord1 cc);
 //   void setItemBehaviour(ItemBehaviour );
    //////
   /* /// \brief drawCross1
    /// \param painter*/
   void renderArea(QPainter *painter);
   void renderSelectedArea(QPainter *painter);

   void fillSelectedArray(void);
   bool checkSelectedArrayEmpty();
   //bool addSelectedArray();
   DrawFunctions drawCross;
   DrawFunctions drawCorn;
   DrawFunctions drawCrossed;
   DrawFunctions drawMiddle;
   DrawFunctions drawM;
   DrawFunctions drawBrick;
   DrawFunctions drawBigElement;

   //int **selectedArray;
   int selectedArrayXSize;
   int selectedArrayYSize;
   int itemsCount;
   bool selected;
   bool wasSelected;
   bool wasDeleted;
   bool wasShift;
   bool shiftPressed;
   bool mouseWasPressed;
   bool shiftPressedOnce;
   bool renderSelected;
   bool copied;
   bool locateSelectedArray(void);
   //void deleteSelectedArray(void);
  // void deleteArray(int **array1, int xlen);
   friend void deleteArray(int **array1, int xlen);
   friend void locateeArray(int **array1, int xlen, int ylen);
   //void showArray(int **array1, int xlen,int ylen );
   void showArray( QVector< QVector<int> > array1, int xlen, int ylen);
   void clearArea(QPainter *painter);
   void clearCell(QPainter *painter, int xb, int yb, int xe, int ye);
   //void flip(bool);
   //void rotate(bool);
   void showSelectedArray(void);
   int getElemType(MakeSelected::coord1 cc);
   void setRedCoordinates(void);


};

#endif // MAKESELECTED_H
