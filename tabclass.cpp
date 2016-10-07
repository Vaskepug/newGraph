#include "tabclass.h"

//#include "twoheaders.h"
TabClass::TabClass(QWidget *parent) : QWidget(parent)
{
    test = 100;
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mScene = new QGraphicsScene();
    mView = new QGraphicsView ();
    int del = 10;
    int borderForNumbers = 20;
    undoStack = new QUndoStack();
//            stateBox( new StateBox()),
    qDebug() << "mh " << this->width() << this->height();
    mScene->setSceneRect(0,0,300,200);
    mGrid = new MakeGrid(this->mScene->width()-borderForNumbers,
                         this->mScene->height()-borderForNumbers,del);
    mSelected = new MakeSelected(this->mScene->width()-borderForNumbers,
                                 this->mScene->height()-borderForNumbers,del,this);
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

   //this->setTabText("nene");
   // topLeft     = mView->mapToScene( 0, 0 );
    //mSelected->setFlag(QGraphicsItem::ItemIsMovable,
     //                      true);
}

void TabClass::saveAsImage()
{
  /* QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
   if (!fileName.isNull())
   {
      //QPixmap pixMap = this->ui->graphicsView->grab();
      QPixmap pixMap = mView->grab();
      pixMap.save(fileName);
   }*/
    mScene->clearSelection();                                                  // Selections would also render to the file
    mScene->setSceneRect(mScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(mScene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent

    QPainter painter(&image);
    mScene->render(&painter);
    image.save("file_name.png");
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
        qDebug() << "key=shift in tab";
        mSelected->setWasShift( true );
        mSelected->setShiftPressed( true );
        if ( mSelected->getMouseWasPressed() ) mSelected->setShiftPressedOnce(true);
    }
    else if (event->key() == Qt::Key_Delete)
    {
        qDebug() << "key=pressed in tab";
        mSelected->deleteAllInside();
    }
    else
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
        {
            mSelected->setShiftPressed(false);
        }
     //   emit keyCaught(event);
   /* if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else*/
       QWidget::keyReleaseEvent(event);
}
