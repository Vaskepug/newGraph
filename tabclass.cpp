#include "tabclass.h"
#include "functions.h"

//#include "twoheaders.h"
TabClass::TabClass(QWidget *parent) : QWidget(parent)
{
    test = 100;
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mScene = new QGraphicsScene();
    mView = new QGraphicsView ();
    del = 10;
    newFile = true;

    borderForNumbers = 20;
    undoStack = new QUndoStack();
//            stateBox( new StateBox()),
    //qDebug() << "mh " << this->width() << this->height();
    border = -20;
    mScene->setSceneRect(border,border,200-border,300-border);
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

bool TabClass::saveAsImage()
{
   QString initialFileName =  "NewImage.png";
  // QString fileName= QFileDialog::getSaveFileName(this, tr("Save image"), QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    QString fileName= QFileDialog::getSaveFileName(this, tr("Save image"), initialFileName, "PNG (*.png)" );
   if (fileName.isNull())
   {
       return false;
      //QPixmap pixMap = this->ui->graphicsView->grab();
    //  QPixmap pixMap = mView->grab();
   //   pixMap.save(fileName);
   }
   else
   {
     //  bool doIt = true;
     //  QFileInfo checkFile(fileName);
          // check if file exists and if yes: Is it really a file and no directory?
     /*  if (checkFile.exists() && checkFile.isFile())
       {
           QMessageBox msgBox;
           msgBox.setText("The file exists. Would you like to replace it&");
           msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
           int otv = msgBox.exec();
           if (otv == QMessageBox::Ok)
           {
                qDebug() << "can save " << fileName;
           }
           else doIt = false;
       }
       else
       {
            qDebug() << "file for saving " << fileName;
           //return false;
       }*/
   }

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
    //image.save("file_name.png");
    image.save(fileName);
    tmprect.setWidth(wtemp);
    tmprect.setHeight(htemp);
    //mScene->setSceneRect(mScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    mScene->setSceneRect(tmprect);
    return true;
}


bool TabClass::saveAsFile()
{
   QString initialFileName =  "NewPettern.fil";
   if (!loadedFileName.isNull())
   {
       fileWriting("loaded");
       qDebug() << "not null";
       return true;
   }
  // QString fileName= QFileDialog::getSaveFileName(this, tr("Save image"), QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
   QString fileName= QFileDialog::getSaveFileName(this, tr("Save pattern"), initialFileName, "FIL (*.fil)" );
   if (fileName.isNull())
   {
       return false;
      //QPixmap pixMap = this->ui->graphicsView->grab();
    //  QPixmap pixMap = mView->grab();
   //   pixMap.save(fileName);
   }
   else
   {
      fileWriting(fileName);
      loadedFileName = fileName;
   }

    return true;
}

void TabClass::fileWriting(QString fname)
{
    if (!loadedFileName.isNull())
    {
        fname = loadedFileName;
        qDebug() << "it is inside " << loadedFileName;
    }
    QFile file(fname);
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    QTextStream stream(&file);
    stream << "Only test "<<endl ;
    //stream << mScene->width()<<' '<< mScene->height()<<endl ;
    int v = mSelected->getVertCells();
    int h = mSelected->getHorizCells();
    stream << v*del<<' '<< h*del << endl ;
    QVector< QVector<int> > *sA = mSelected->getSceneArray();
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < v; j++)
        {
            int deg = (*sA)[i][j];
            stream << deg  << ' ';
        }
        stream << endl ;
    }
    file.close();
}


bool TabClass::loadFromFile()
{
    QString  fileName= QFileDialog::getOpenFileName(this, tr("Open pattern"), QCoreApplication::applicationDirPath(), "FIL (*.fil)" );
    if (fileName.isNull()) return false;
   //  QString fileName= "D://qtprj//test1//build-newGraph-Desktop-Debug//13.fil";
   // qDebug() << "loaded " <<  fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite)) return true;
    QTextStream stream(&file);
    QString strLine = stream.readLine();
    strLine = stream.readLine();
    QStringList fields = strLine.split(" ");
    int w = fields[0].toInt();
    int h = fields[1].toInt();
    int wd = w/del;
    int hd = h/del;
   // qDebug() <<"wa read " <<fields[0].toInt()<<' '<<fields[1].toInt();
    resizeGrid(h,w);
    QVector< QVector<int> > sA;
    allocateVector( sA, hd, wd );
    for (int i = 0; i < hd; i++)
    {
       // qDebug() << "i=" << i;
        strLine = stream.readLine();
      //  qDebug() << "str " <<strLine;
        QStringList fields1 = strLine.split(" ");
        for (int j = 0; j < wd; j ++)
        {
           // qDebug() << "j=" << ' '<< j <<' '<<fields1[j].toInt();;
            sA[i][j] = fields1[j].toInt();
        }
    }
    mSelected->resizeSceneArray(hd,wd);
    mSelected->fillSceneArray(sA);
    //mSelected->deleteSceneArray();
   //  mSelected->setHorizCells(wd);
  //   mSelected->setVertCells(hd);
   //  mSelected->setSceneArray(sA);

    deleteVectorContent( sA,  hd );

   // resizeSceneArray(h,v);
   file.close();
   loadedFileName = fileName;
  // return fileName;
   newFile = false;
    return false;
}


bool TabClass::isFileNew()
{
    return newFile;
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
    horSize = h;
}

void TabClass::setVertNumber( int v)
{
    vertSize = v;
}

int TabClass::getDel()
{
    return del;
}

void TabClass::resizeGrid(int h, int v)
{
    setVertNumber(v);
    setHorNumber(h);
    qDebug() << "here goes v " << getVertNumber()<<' '<<getHorNumber();
    int h1 = h + borderForNumbers;
    int v1 = v + borderForNumbers;
    mScene->setSceneRect(border,border,h1+border,v1+border);
    qDebug() << "whhhh "<< h<<' '<<v;
    mGrid->sizeChanged(h,v);
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
