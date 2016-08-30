#include "tabclass.h"

TabClass::TabClass(QWidget *parent) : QWidget(parent)
{
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mScene = new QGraphicsScene();
    mView = new QGraphicsView ();
    int del = 10;
//            stateBox( new StateBox()),
    qDebug() << "mh " << this->width() << this->height();
    mScene->setSceneRect(0,0,300,200);
    mGrid = new MakeGrid(this->mScene->width()-20, this->mScene->height()-20,del);
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
        mSelected->wasShift = true;
        mSelected->shiftPressed = true;
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
            mSelected->shiftPressed = false;
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
