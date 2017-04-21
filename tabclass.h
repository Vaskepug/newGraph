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
#include <QUndoStack>

#include "makegrid.h"
#include "makeselected.h"
#include "drawcrosses.h"
//#include "twoheaders.h"

//class MakeSelected;

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
    bool saveAsImage();
    bool saveAsFile();
    bool loadFromFile();
    void changeGrid(int,int);
    int test;
    bool isFileNew();
    QUndoStack *undoStack;
    int getHorNumber();
    int getVertNumber();
    int getDel();
    int getBorderForNumbers();
    void resizeGrid(int h, int v);
    void resizeSceneArray(int h, int v);
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
    int del;
    int horSize;
    int vertSize;
    int borderForNumbers;
    int border;
    bool newFile;

    QString loadedFileName;
    QHBoxLayout *mLayout;
    void setHorNumber(int);
    void setVertNumber(int);
    void fileWriting(QString fname);
   // QGraphicsScene * mScene ; ///< the scene will contain the graphics item 'StateBox'

   // StateBox * stateBox; ///< this is my custom QGraphicsItem
    MakeGrid * mGrid; ///< this is my custom QGraphicsItem
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};


#endif // TABCLASS_H
