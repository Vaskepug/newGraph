#include "tabclass.h"

TabClass::TabClass(QWidget *parent) : QWidget(parent)
{
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mScene = new QGraphicsScene();
  //  mScene = new DrawCrosses();
  //  mScene->init(300,200);
    mView = new QGraphicsView ();
    int del = 10;
//            stateBox( new StateBox()),
    qDebug() << "mh " << this->width() << this->height();
    mScene->setSceneRect(0,0,300,200);
    mGrid = new MakeGrid(this->mScene->width(), this->mScene->height(),del);
    mSelected = new MakeSelected(this->mScene->width(), this->mScene->height(),del);
    //mSelected->setPos(10,10);
    ////////
    mLayout->addWidget(mView);
    this->setLayout(mLayout);
    mScene->addItem(mGrid);
    mScene->addItem(mSelected);
    mView->setScene( mScene);
    mView->show();
    mSelected->setFlag(QGraphicsItem::ItemIsSelectable,
                            true);
    //mSelected->setFlag(QGraphicsItem::ItemIsMovable,
     //                      true);
}

TabClass::~TabClass()
{
    delete mGrid;
    delete mScene;
    delete mView;
    delete mLayout;
  //  delete mSelected;
}


void TabClass::keyPressEvent(QKeyEvent *event)
{
       // qDebug() << "key="<<event->key();
 //   qDebug() << event->modifiers() << event->key() <<
     //           (event->key() == Qt::Key_Shift) << event->isAutoRepeat();
    if ( event->key() == Qt::Key_Shift )
    {
        qDebug() << "key=shift";
        mSelected->shiftPressed = true;
    }
    else qDebug() << "NO NO NO key=shift";
     //   emit keyCaught(event);
   /* if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else*/
       QWidget::keyPressEvent(event);
}

void TabClass::keyReleaseEvent(QKeyEvent *event)
{
     //   qDebug() << "released="<<event->key();
        if ( event->key() == Qt::Key_Shift )
            mSelected->shiftPressed = false;
     //   emit keyCaught(event);
   /* if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else*/
       QWidget::keyReleaseEvent(event);
}
