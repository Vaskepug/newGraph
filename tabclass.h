#ifndef TABCLASS_H
#define TABCLASS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>

#include "makegrid.h"
#include "makeselected.h"
#include "drawcrosses.h"

class TabClass : public QWidget
{
    Q_OBJECT
public:
    explicit TabClass(QWidget *parent = 0);
    ~TabClass();
    MakeSelected *mSelected;
    QGraphicsScene * mScene ; //
    QGraphicsView * mView; //
    QPointF topLeft;
    void saveAsImage();
 //   DrawCrosses *mScene;
   // enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
    //              MakeMiddle, MakeM, MakeBrick ,SelectMode};

   // explicit TabClass(QWidget *parent = 0, int w=200, int h=150, int delta=10);
   // void init(int,int,int);
   // DrawingPlace *drawplace;
   // QGraphicsView* view;
   /* void keyPressEvent(QKeyEvent* e)
        {
              QMessageBox* box = new QMessageBox();
              box->setWindowTitle(QString("Hello"));
              box->setText(QString("You Pressed: ")+ e->text());
              box->show();
        };*/
signals:

public slots:


private:
 //DrawingPlace *drawplace;
    QHBoxLayout *mLayout;
   // QGraphicsScene * mScene ; ///< the scene will contain the graphics item 'StateBox'

   // StateBox * stateBox; ///< this is my custom QGraphicsItem
    MakeGrid * mGrid; ///< this is my custom QGraphicsItem
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};


#endif // TABCLASS_H
