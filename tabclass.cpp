#include "tabclass.h"

//#include "twoheaders.h"
TabClass::TabClass(QWidget *parent) : QWidget(parent)
{
    test = 100;
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mScene = new QGraphicsScene();
    mView = new QGraphicsView ();
    del = 10;
    borderForNumbers = 20;
    undoStack = new QUndoStack();
//            stateBox( new StateBox()),
    qDebug() << "mh " << this->width() << this->height();
    border = -20;
    mScene->setSceneRect(border,border,300-border,200-border);
    horSize = this->mScene->width()-borderForNumbers;
    vertSize = this->mScene->height()-borderForNumbers;
    mGrid = new MakeGrid(horSize,
                         vertSize,del);
    mSelected = new MakeSelected(horSize,
                                 vertSize,del,this);
    //mSelected->setPos(10,10);
    ////////
    mLayout->addWidget(mView);
    this->setLayout(mLayout);
    mScene->addItem(mGrid);
    mScene->addItem(mSelected);
    mView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
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
    qDebug() << "ww " << mScene->width() <<' ' <<mScene->height();
    unsigned int wtemp = mScene->width();
    unsigned int htemp = mScene->height();
    QRectF tmprect;
    tmprect.setWidth(wtemp+30);
    tmprect.setHeight(htemp+30);
    //mScene->setSceneRect(mScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    mScene->setSceneRect(tmprect);                          // Re-shrink the scene to it's bounding contents
    QImage image(mScene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent

    QPainter painter(&image);
    mScene->render(&painter);
    image.save("file_name.png");
    tmprect.setWidth(wtemp);
    tmprect.setHeight(htemp);
    //mScene->setSceneRect(mScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    mScene->setSceneRect(tmprect);
}

TabClass::~TabClass()
{
    delete mGrid;
    delete mScene;
    delete mView;
    delete mLayout;
  //  delete mSelected;
}

int TabClass::getHorNumber()
{
    return horSize/del;
}

int TabClass::getVertNumber()
{
    return vertSize/del;
}

void TabClass::setHorNumber(int h)
{
    horSize = h * del;
}

void TabClass::setVertNumber( int v)
{
    vertSize = v * del;
}

int TabClass::getDel()
{
    return del;
}

void TabClass::resizeGrid(int h, int v)
{
    setVertNumber(v);
    setHorNumber(h);
    int h1 = h * del + borderForNumbers;
    int v1 = v * del + borderForNumbers;
    mScene->setSceneRect(border,border,h1+border,v1+border);
    qDebug() << "wh "<< mScene->width()<<' '<<mScene->height();
    mGrid->sizeChanged(h*del,v*del);
}

void TabClass::resizeSceneArray(int h, int v)
{
    mSelected->resizeSceneArray(h,v);
   /* setVertNumber(v);
    setHorNumber(h);
    h = h * del + borderForNumbers;
    v = v * del + borderForNumbers;
    mScene->setSceneRect(border,border,h+border,v+border);
    qDebug() << "wh "<< mScene->width()<<' '<<mScene->height();
    mGrid->sizeChanged(h,v);*/
}


int TabClass::getBorderForNumbers()
{
    return borderForNumbers;
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
