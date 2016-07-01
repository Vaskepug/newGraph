#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    TabClass *tab1 = new TabClass(this);

  //  TabClass *tab2 = new TabClass(this);
    tabWidget = new QTabWidget(this);
    tabWidget->addTab( tab1,tr("General"));
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
    delete vertActionGroup;
    delete plusMinusActionGroup;
    delete flipActionGroup;
    delete topToolbar;
    delete leftToolbar;
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

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
    thisExit->setCheckable(true);
    connect(thisExit, SIGNAL(triggered()), this, SLOT(thisExitf()));

    /////////
    increase = new QAction("Increase",this);
    increase->setIcon(QIcon(":/icons/plus.png"));
    increase->setCheckable(true);
   // connect(increase, SIGNAL(triggered()), this, SLOT(increaseGrid()));

    decrease = new QAction("Decrease",this);
    decrease->setIcon(QIcon(":/icons/minus.png"));
    decrease->setCheckable(true);
  //  connect(decrease, SIGNAL(triggered()), this, SLOT(decreaseGrid()));
    ////////
    flipHoriz = new QAction("Horizontal",this);
    flipHoriz->setIcon(QIcon(":/icons/horiz.png"));
    flipHoriz->setCheckable(true);
   // connect(flipHoriz, SIGNAL(triggered()), this, SLOT(flipHorizf()));

    flipVert = new QAction("Vertical",this);
    flipVert->setIcon(QIcon(":/icons/vert.png"));
    flipVert->setCheckable(true);
    // connect(flipVert, SIGNAL(triggered()), this, SLOT(flipVertf()));
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
    plusMinusActionGroup = new QActionGroup(this);
    plusMinusActionGroup ->setExclusive(true);
    plusMinusActionGroup->addAction(decrease);
    plusMinusActionGroup->addAction(increase);
    //////////
    flipActionGroup = new QActionGroup(this);
    flipActionGroup ->setExclusive(true);
    flipActionGroup->addAction(flipHoriz);
    flipActionGroup->addAction(flipVert);
    /////////
    topToolbar = new  QToolBar("Choice ToolBar", this);
    leftToolbar = new  QToolBar("Action ToolBar", this);
    addToolBar(Qt::TopToolBarArea, topToolbar);
    addToolBar(Qt::LeftToolBarArea, leftToolbar);
    leftToolbar->addActions(vertActionGroup->actions());

    /////////
   // topToolbar->addAction(increase);
  //  topToolbar->addAction(decrease);
    topToolbar->addActions(plusMinusActionGroup->actions());
    topToolbar->addActions(flipActionGroup->actions());
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

}

void MainWindow::flipVertf()
{

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
