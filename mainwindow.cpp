#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createToolBars();
    addTabs();
    setCentralWidget(tabWidget);
    tabWidget->show();

}

void MainWindow::addTabs(void)
{
    //TabClass *tab1 = new TabClass(this);

  //  TabClass *tab2 = new TabClass(this);
   // tabWidget = new QTabWidget(this);
    tabWidget = new TWidget();
    tabWidget->addTab( new TabClass(this),"NewFile0");
    tabWidget->tabBar()->setTabTextColor(0,Qt::red);
    tabWidget->setTabsClosable(true);
    tabWidget->tabBar()->setTabTextColor(0,Qt::blue);
    tabWidget->tabBar()->setTabText(0,"111 111");
    indexNewTabs = 0;
    int curr = tabWidget->currentIndex();
    tabwid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    QLabel* statusLabel = new QLabel("Your Message");
    statusLabel->setAlignment(Qt::AlignCenter);
    ui->statusBar->addWidget(statusLabel,1);
    //ui->statusBar->showMessage("Status");
   // QLabel* nameFile;
  //  nameFile->setText("New1");
  //  statusBar()->addWidget(nameFile);

  //  tabWidget->addTab( tab2,tr("New"));
}


MainWindow::~MainWindow()
{
    delete ui;
    //delete tab1;
    delete tabWidget;
    delete makeCross;
    delete makeCircle;
    delete makeM;
    delete makeBrick;
    delete makeCrossed;
    delete makeMiddle;
    delete increase;
    delete decrease;
    delete flipVert;
    delete flipHoriz;
    delete rotateClockWise;
    delete rotateCounterClockWise;
    delete vertActionGroup;
  //  delete plusMinusActionGroup;
  //  delete flipActionGroup;
    delete topToolbar;
    delete leftToolbar;
    delete copyAction;
    delete pasteAction;
    delete cutAction;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
       // tr("Open File"), "", tr("Files (*.png *.jpg *.bmp)"));
        tr("Open File"), "", tr("Files (*.*)"));

     qDebug() << "Got filename: " << fileName;
}

void MainWindow::on_actionSave_triggered()
{
    tabwid->saveAsImage();
    //QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
   // if (!fileName.isNull())
  //  {
  //     QPixmap pixMap = this->ui->graphicsView->grab();
  //     pixMap.save(fileName);
  //  }
}

void MainWindow::on_actionNew_triggered()
{
    indexNewTabs ++;
   // QString name = "NewFile";
    QString name = QString ("NewFile%1").arg(indexNewTabs);
  //  name += indexNewTabs;
    tabWidget->addTab( new TabClass(this),name);
    qDebug() << "new " << name ;
}

void MainWindow::createToolBars(void)
{
   //////////
    makeCross = new QAction("Make Cross",this);
    makeCross->setData(int(MakeSelected::MakeCross));
    makeCross->setIcon(QIcon(":/icons/cross.png"));

    makeCross->setCheckable(true);

  //  connect(makeCross, SIGNAL(triggered()), this, SLOT(makeCrossf()));
    makeCircle = new QAction("Make Circle",this);
    makeCircle->setIcon(QIcon(":/icons/circle.png"));
    makeCircle->setData(int(MakeSelected::MakeCorn));
    makeCircle->setCheckable(true);
  //  connect(makeCircle, SIGNAL(triggered()), this, SLOT(makeCirclef()));

    makeM = new QAction("Make M",this);
    makeM->setIcon(QIcon(":/icons/m.png"));
    makeM->setData(int(MakeSelected::MakeM));
    makeM->setCheckable(true);

    makeBrick = new QAction("Make Brick",this);
    makeBrick->setIcon(QIcon(":/icons/brick.png"));
    makeBrick->setData(int(MakeSelected::MakeBrick));
    makeBrick->setCheckable(true);

    makeCrossed = new QAction("Make Crossed",this);
    makeCrossed->setIcon(QIcon(":/icons/crossed.png"));
    makeCrossed->setData(int(MakeSelected::MakeCrossed));
    makeCrossed->setCheckable(true);

    makeMiddle = new QAction("Make Middle",this);
    makeMiddle->setIcon(QIcon(":/icons/middle.png"));
    makeMiddle->setData(int(MakeSelected::MakeMiddle));
    makeMiddle->setCheckable(true);

    ////////////////////////

    setGrid = new QAction("Set Grid",this);
    setGrid->setIcon(QIcon(":/icons/grid.png"));
    setGrid->setCheckable(true);
   // connect (setGrid, SIGNAL(triggered()), this, SLOT(setGridf()));

    select = new QAction("Select",this);
    select->setIcon(QIcon(":/icons/select.png"));
    select->setCheckable(true);
    connect (select, SIGNAL(triggered()), this, SLOT(selectf()));

    thisExit = new QAction("Exit",this);
    thisExit->setIcon(QIcon(":/icons/exit.png"));
    thisExit->setCheckable(false);
    connect(thisExit, SIGNAL(triggered()), this, SLOT(thisExitf()));

    /////////
    increase = new QAction("Increase",this);
    increase->setIcon(QIcon(":/icons/plus.png"));
    increase->setCheckable(false);
    connect(increase, SIGNAL(triggered()), this, SLOT(increaseGrid()));

    decrease = new QAction("Decrease",this);
    decrease->setIcon(QIcon(":/icons/minus.png"));
    decrease->setCheckable(false);
    connect(decrease, SIGNAL(triggered()), this, SLOT(decreaseGrid()));
    ////////
    flipHoriz = new QAction("Horizontal",this);
    flipHoriz->setIcon(QIcon(":/icons/horiz.png"));
    flipHoriz->setCheckable(false);
    connect(flipHoriz, SIGNAL(triggered()), this, SLOT(flipHorizf()));

    flipVert = new QAction("Vertical",this);
    flipVert->setIcon(QIcon(":/icons/vert.png"));
    flipVert->setCheckable(false);
     connect(flipVert, SIGNAL(triggered()), this, SLOT(flipVertf()));
    ////////
     rotateClockWise = new QAction("RotateClock",this);
     rotateClockWise->setIcon(QIcon(":/icons/rotcl.png"));
     rotateClockWise->setCheckable(false);
     connect(rotateClockWise, SIGNAL(triggered()), this, SLOT(rotateClockWisef()));

     rotateCounterClockWise = new QAction("RotateCounter",this);
     rotateCounterClockWise->setIcon(QIcon(":/icons/rotcounter.png"));
     rotateCounterClockWise->setCheckable(false);
      connect(rotateCounterClockWise, SIGNAL(triggered()), this, SLOT(rotateCounterClockWisef()));
     ////////
      ////////
       copyAction = new QAction("Copy",this);
       copyAction->setIcon(QIcon(":/icons/copy.png"));
       copyAction->setCheckable(false);
       connect(copyAction, SIGNAL(triggered()), this, SLOT(copyf()));

       pasteAction = new QAction("Paste",this);
       pasteAction->setIcon(QIcon(":/icons/paste.png"));
       pasteAction->setCheckable(false);
       connect(pasteAction, SIGNAL(triggered()), this, SLOT(pastef()));

       cutAction = new QAction("Cut",this);
       cutAction->setIcon(QIcon(":/icons/cut.png"));
       cutAction->setCheckable(false);
       connect(cutAction, SIGNAL(triggered()), this, SLOT(cutf()));
       ////////

    vertActionGroup = new QActionGroup(this);
    vertActionGroup->setExclusive(true);
    vertActionGroup->addAction(select);
    vertActionGroup->addAction(makeCross);
    vertActionGroup->addAction(makeCircle);
    vertActionGroup->addAction(makeM);
    vertActionGroup->addAction(makeBrick);
    vertActionGroup->addAction(makeCrossed);
    vertActionGroup->addAction(makeMiddle);
    //////////
    connect(vertActionGroup, SIGNAL(triggered(QAction*)),
                this, SLOT(actionGroupClicked(QAction*)));
    ////////
   /* plusMinusActionGroup = new QActionGroup(this);
    plusMinusActionGroup ->setExclusive(true);
    plusMinusActionGroup->addAction(decrease);
    plusMinusActionGroup->addAction(increase);
    //////////
    flipActionGroup = new QActionGroup(this);
    flipActionGroup ->setExclusive(true);
    flipActionGroup->addAction(flipHoriz);
    flipActionGroup->addAction(flipVert);*/
    /////////
    topToolbar = new  QToolBar("Choice ToolBar", this);
    leftToolbar = new  QToolBar("Action ToolBar", this);
    addToolBar(Qt::TopToolBarArea, topToolbar);
    addToolBar(Qt::LeftToolBarArea, leftToolbar);
    leftToolbar->addActions(vertActionGroup->actions());

    /////////
    topToolbar->addAction(increase);
    topToolbar->addAction(decrease);
    topToolbar->addAction(flipHoriz);
    topToolbar->addAction(flipVert);
    topToolbar->addAction(rotateClockWise);
    topToolbar->addAction(rotateCounterClockWise);
    topToolbar->addAction(copyAction);
    topToolbar->addAction(pasteAction);
    topToolbar->addAction(cutAction);
   // topToolbar->addActions(plusMinusActionGroup->actions());
  //  topToolbar->addActions(flipActionGroup->actions());
    topToolbar->addAction(setGrid);
    topToolbar->addAction(thisExit);

}


void MainWindow::actionGroupClicked(QAction *action)
{
 //  qDebug() << "xc=" <<  makeCross->data().toInt()<<' '<<tabWidget->currentIndex();
   qDebug() <<  "dat=" << action->data().toInt();
 //  int curr = tabWidget->currentIndex();
   for (int i = 0; i <tabWidget->count();i ++ )
   {
       //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
       TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(i));
       wid ->mSelected->setChoice(MakeSelected::Choice(action->data().toInt()));
     //  wid->drawplace->setMode(DrawingPlace::Mode(action->data().toInt()));
   }
   // dynamic_cast<QLineEdit*>(widget)->text();

}


void MainWindow::flipHorizf()
{
    /*int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->flipHorizontally();*/
    tabwid->mSelected->flipHorizontally();
}



void MainWindow::flipVertf()
{
  /*  int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->flipVertically(); */
    tabwid->mSelected->flipVertically();
}


void MainWindow::copyf()
{
    qDebug () << "111";
   /* int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->copySelected();*/
    tabwid->mSelected->copySelected();
}

void MainWindow::cutf()
{
    //int curr = tabWidget->currentIndex();
    //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    //wid->mSelected->flipVertically();
}

void MainWindow::increaseGrid()
{
    //int curr = tabWidget->currentIndex();
    //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    tabwid->mView->scale(1.5,1.5);

}

void MainWindow::decreaseGrid()
{
    //int curr = tabWidget->currentIndex();
    //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    tabwid->mView->scale(1/1.5,1/1.5);

}



void MainWindow::pastef()
{
    tabwid->topLeft = tabwid-> mView->mapToScene( 0, 0 );
    qDebug () << "xxx " << tabwid->topLeft.x() << ' ' << tabwid->topLeft.y();
  //  qDebug () << "222";
/*    int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->pasteSelected(); */
    tabwid->mSelected->pasteSelected(tabwid->topLeft);
}


void MainWindow::rotateClockWisef()
{
  /*  int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->rotateClockWise(); */
    tabwid->mSelected->rotateClockWise();
}


void MainWindow::rotateCounterClockWisef()
{
    /*int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->rotateCounterClockWise();*/
    tabwid->mSelected->rotateCounterClockWise();
}


void MainWindow::thisExitf()
{
    this->close();
}

void MainWindow::selectf()
{
  //  int curr = tabWidget->currentIndex();
  //  TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
  //  wid ->mSelected->setSelected(true);
  //  wid ->mScene ->setSelected();
}



void MainWindow::savef()
{

  // qDebug() << "save";
   /*QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
   if (!fileName.isNull())
   {
       QPixmap pixMap = this->view->grab();
       pixMap.save(fileName);
   }*/
  // drawplace->clearSelection();                                                  // Selections would also render to the file
 //  drawplace->setSceneRect(drawplace->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
  // QImage image(drawplace->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
 //  QImage image(drawplace->width(), drawplace->height(), QImage::Format_ARGB32_Premultiplied);
  // qDebug()<<"wh"<< drawplace->width() <<' '<< drawplace->width();
  // image.fill(Qt::transparent);                                              // Start all pixels transparent

  // QPainter painter(&image);
  // drawplace->render(&painter);
  // image.save("file_name.png");

}


