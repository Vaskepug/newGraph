#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //int numActions = 6;

    createToolBars();
    addTabs();
    setCentralWidget(tabWidget);
    tabWidget->show();
    //selectedArray = nullptr;
    selectedArray.clear();
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged()));
}

void MainWindow::addTabs(void)
{
    //TabClass *tab1 = new TabClass(this);
    wasCopied = false;
    currentTab = 0;

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
    tabwid ->mSelected->setChoice(MakeSelected::Choice(1));

  /*  MakeSelected::Choice cho;
    cho = tabwid ->mSelected->getChoice();
    vertActions [(int) cho - 1]->setChecked(true);*/
    setRightTool();
    qDebug() << "checked selected " << (int)  MakeSelected::Choice(1);
    QLabel* statusLabel = new QLabel("Your Message");
    statusLabel->setAlignment(Qt::AlignCenter);
    ui->statusBar->addWidget(statusLabel,1);

    //ui->statusBar->showMessage("Status");
   // QLabel* nameFile;
  //  nameFile->setText("New1");
  //  statusBar()->addWidget(nameFile);

  //  tabWidget->addTab( tab2,tr("New"));
}

void MainWindow::tabChanged()
{
    int curr = tabWidget->currentIndex();
    qDebug() << "curr tab " << curr;
    tabwid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    setRightTool();
  //  MakeSelected::Choice cho;
  //  cho = tabwid ->mSelected->getChoice();
  //  vertActions [(int) cho - 1]->setChecked(true);
   //
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
    delete undoAction;
    delete redoAction;
    delete resizeAction;
    delete fastSaveAction;
    //delete vertActions;
    //if ( selectedArray != nullptr )
    if ( selectedArray.size() != 0 )
       // deleteArray(selectedArray,selectedArrayXSize);
        deleteVectorContent( selectedArray,selectedArrayYSize );
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
    bool ret = tabwid->saveAsImage();
    QMessageBox msgBox;

    if (ret)
    {
        msgBox.setText("File was saved successfully");
    }
    else
        msgBox.setText("File was not saved");
    msgBox.exec();
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
    int index = tabWidget->addTab( new TabClass(this),name);
    tabWidget->setCurrentIndex(index);
    int curr = tabWidget->currentIndex();
    tabwid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    tabwid ->mSelected->setChoice(MakeSelected::Choice(1));
    setRightTool();
    qDebug() << "new " << name ;
}

void MainWindow::setRightTool(void)
{
    MakeSelected::Choice cho;
    cho = tabwid ->mSelected->getChoice();
    qDebug() << "  changed tab " << (int)cho;
    if ( cho >= 0)
        vertActions [(int) cho]->setChecked(true);

}

void MainWindow::createToolBars(void)
{
    select = new QAction("Select",this);
    vertActions[0] = select;
    select->setIcon(QIcon(":/icons/select.png"));
    select->setCheckable(true);
    connect (select, SIGNAL(triggered()), this, SLOT(selectf()));
   //////////
    makeCross = new QAction("Make Cross",this);
    vertActions[1] = makeCross;
    makeCross->setData(int(MakeSelected::MakeCross));
    makeCross->setIcon(QIcon(":/icons/cross.png"));

    makeCross->setCheckable(true);
    //makeCross->setChecked(true);

  //  connect(makeCross, SIGNAL(triggered()), this, SLOT(makeCrossf()));
    makeCircle = new QAction("Make Circle",this);
    vertActions[2] = makeCircle;
    makeCircle->setIcon(QIcon(":/icons/circle.png"));
    makeCircle->setData(int(MakeSelected::MakeCorn));
    makeCircle->setCheckable(true);
  //  connect(makeCircle, SIGNAL(triggered()), this, SLOT(makeCirclef()));

    makeM = new QAction("Make M",this);
    vertActions[5] = makeM;
    makeM->setIcon(QIcon(":/icons/m.png"));
    makeM->setData(int(MakeSelected::MakeM));
    makeM->setCheckable(true);

    makeMiddle = new QAction("Make Middle",this);
    vertActions[4] = makeMiddle;
    makeMiddle->setIcon(QIcon(":/icons/middle.png"));
    makeMiddle->setData(int(MakeSelected::MakeMiddle));
    makeMiddle->setCheckable(true);

    makeCrossed = new QAction("Make Crossed",this);
    vertActions[3] = makeCrossed;
    makeCrossed->setIcon(QIcon(":/icons/crossed.png"));
    makeCrossed->setData(int(MakeSelected::MakeCrossed));
    makeCrossed->setCheckable(true);


    makeBrick = new QAction("Make Brick",this);
    vertActions[6] = makeBrick;
    makeBrick->setIcon(QIcon(":/icons/brick.png"));
    makeBrick->setData(int(MakeSelected::MakeBrick));
    makeBrick->setCheckable(true);

    ////////////////////////

    setGrid = new QAction("Set Grid",this);
    setGrid->setIcon(QIcon(":/icons/grid.png"));
    setGrid->setCheckable(true);
   // connect (setGrid, SIGNAL(triggered()), this, SLOT(setGridf()));

    /*select = new QAction("Select",this);
    select->setIcon(QIcon(":/icons/select.png"));
    select->setCheckable(true);
    connect (select, SIGNAL(triggered()), this, SLOT(selectf()));*/

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
       undoAction = new QAction("Undo",this);
       undoAction->setIcon(QIcon(":/icons/undo.png"));
       undoAction->setCheckable(false);
       connect(undoAction, SIGNAL(triggered()), this, SLOT(undof()));

       redoAction = new QAction("Redo",this);
       redoAction->setIcon(QIcon(":/icons/redo.png"));
       redoAction->setCheckable(false);
       connect(redoAction, SIGNAL(triggered()), this, SLOT(redof()));

        ///////////
       resizeAction = new QAction("Resize",this);
       resizeAction->setIcon(QIcon(":/icons/resize.png"));
       resizeAction->setCheckable(false);
       connect(resizeAction, SIGNAL(triggered()), this, SLOT(resizef()));
       ///////
       ////////
       fastSaveAction = new QAction("Save",this);
       fastSaveAction->setIcon(QIcon(":/icons/save1.png"));
       fastSaveAction->setCheckable(false);
       connect(fastSaveAction, SIGNAL(triggered()), this, SLOT(fastSavef()));
       ///

    vertActionGroup = new QActionGroup(this);
    vertActionGroup->setExclusive(true);
    vertActionGroup->addAction(select);
    vertActionGroup->addAction(makeCross);
    vertActionGroup->addAction(makeCircle);
    vertActionGroup->addAction(makeCrossed);
    vertActionGroup->addAction(makeMiddle);
    vertActionGroup->addAction(makeM);
    vertActionGroup->addAction(makeBrick);
  //  vertActionGroup->addAction(makeCrossed);
  //  vertActionGroup->addAction(makeMiddle);
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
    topToolbar->addAction(fastSaveAction);
    topToolbar->addAction(increase);
    topToolbar->addAction(decrease);
    topToolbar->addAction(flipHoriz);
    topToolbar->addAction(flipVert);
    topToolbar->addAction(rotateClockWise);
    topToolbar->addAction(rotateCounterClockWise);
    topToolbar->addAction(copyAction);
    topToolbar->addAction(pasteAction);
    topToolbar->addAction(cutAction);
    topToolbar->addAction(undoAction);
    topToolbar->addAction(redoAction);
    topToolbar->addAction(resizeAction);
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
 /*  for (int i = 0; i <tabWidget->count();i ++ )
   {
       //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
       TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(i));
       wid ->mSelected->setChoice(MakeSelected::Choice(action->data().toInt()));
     //  wid->drawplace->setMode(DrawingPlace::Mode(action->data().toInt()));
   }*/
   // dynamic_cast<QLineEdit*>(widget)->text();
     tabwid ->mSelected->setChoice(MakeSelected::Choice(action->data().toInt()));

}


void MainWindow::flipHorizf()
{
    /*int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->flipHorizontally();*/
    tabwid->mSelected->flipHorizontally();
    qDebug() << "horizontally";
}



void MainWindow::flipVertf()
{
  /*  int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->flipVertically(); */
    tabwid->mSelected->flipVertically();
    qDebug() << "vrtically";
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


void MainWindow::copyf()
{
    qDebug () << "111";
   /* int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->copySelected();*/
    wasCopied = tabwid->mSelected->copySelected();
    if ( wasCopied )
    {
        selectedArrayXSize = tabwid->mSelected->getSelectedArrayXSize();
        selectedArrayYSize = tabwid->mSelected->getSelectedArrayYSize();
        currentTab = tabWidget->currentIndex();
      //  if ( selectedArray != nullptr )
          if ( selectedArray.size() != 0 )
        {
            qDebug() << "New Array 111";
           // deleteArray(selectedArray,selectedArrayXSize);
            deleteVectorContent( selectedArray,  selectedArrayYSize );
            selectedArray.clear();
        }

        //qDebug() << "New Array " << selectedArrayXSize << ' ' << selectedArrayYSize;
        // locate
        allocateVector( selectedArray, selectedArrayXSize,selectedArrayYSize );
        // was locateArray(selectedArray,selectedArrayXSize,selectedArrayYSize);
      /*  selectedArray = new int *[selectedArrayXSize];
        for (int i = 0; i < selectedArrayXSize; i ++)
        {
            selectedArray[i] = new int [selectedArrayYSize];
        }*/
        // copy
      // int **sA = tabwid->mSelected->getSelectedArray();
         QVector< QVector<int> > sA = tabwid->mSelected->getSelectedArray();
        for ( int i = 0; i < selectedArrayXSize; i ++)
        {
            for ( int j = 0; j < selectedArrayYSize; j ++)
            {
                selectedArray[i][j] = sA[i][j];
            }
        }
       // qDebug() << "New Array " << selectedArray[0][0] << ' ' << selectedArray[2][2];
    }
}

void MainWindow::cutf()
{
    //int curr = tabWidget->currentIndex();
    //TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    //wid->mSelected->flipVertically();
}


void MainWindow::pastef()
{
   // tabwid->topLeft = tabwid-> mView->mapToScene( 0, 0 );
   // qDebug () << "xxx " << tabwid->topLeft.x() << ' ' << tabwid->topLeft.y();
  //  qDebug () << "222";
/*    int curr = tabWidget->currentIndex();
    TabClass *wid =dynamic_cast<TabClass *>(tabWidget->widget(curr));
    wid->mSelected->pasteSelected(); */
    if (wasCopied)
    {
        QPointF leftTopZero;
        leftTopZero.setX(0);
        leftTopZero.setY(0);
        //tabwid->mSelected->pasteSelected(tabwid->topLeft);
        if ( currentTab ==  tabWidget->currentIndex())
            tabwid->mSelected->pasteSelected(leftTopZero);
        else
        {
            //if ( tabwid->mSelected->selectedArray != nullptr )
            if ( tabwid->mSelected->selectedArray.size() != 0 )
            {
                qDebug() << "in new tab";
                tabwid->mSelected->addSelectedArray();
                tabwid->mSelected->setSelected(false);
                tabwid->mSelected->deleteSelectedArray();
                tabwid->mSelected->doUpdate();
            }
            qDebug() << "in other tab";
            tabwid->mSelected->setSelectedArrayXSize(selectedArrayXSize);
            tabwid->mSelected->setSelectedArrayYSize(selectedArrayYSize);
            tabwid->mSelected->fillSelectedArrayfromOutside(selectedArray);
            tabwid->mSelected->setSelected (true);
            tabwid->mSelected->setCopied (true);
            tabwid ->mSelected->setChoice(MakeSelected::Choice(0));
            setRightTool();
            tabwid->mSelected->pasteSelected(leftTopZero);
        }
     }
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

void MainWindow::fastSavef()
{
    qDebug() << "fast save";
    bool ret = tabwid->saveAsFile();
}

void MainWindow::redof()
{
    tabwid->undoStack->redo();
   // tabwid->mView->scale(1.5,1.5);
    qDebug() << "redo main";
}
void MainWindow::undof()
{
    tabwid->undoStack->undo();
    qDebug() << "undo main";
}
void MainWindow::resizef()
{
    int v = tabwid->getVertNumber();
    int h = tabwid->getHorNumber();
    qDebug() << "vh = " << v << ' '<<h;

    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("The number of horizontal cells"));
    //QLabel *integerLabel = new QLabel(tr(""));
    QSpinBox *integerSpinBoxH = new QSpinBox;
    integerSpinBoxH->setRange(10, 120);
    integerSpinBoxH->setSingleStep(1);
    integerSpinBoxH->setValue(h);
    form.addWidget(integerSpinBoxH);
    form.addRow(new QLabel("The number of vertical cells"));
    QSpinBox *integerSpinBoxV = new QSpinBox;
    integerSpinBoxV->setRange(10, 120);
    integerSpinBoxV->setSingleStep(1);
    integerSpinBoxV->setValue(v);
    form.addWidget(integerSpinBoxV);

    QDialogButtonBox buttonBox(Qt::Horizontal,&dialog);
    buttonBox.addButton(tr("Apply"), QDialogButtonBox::AcceptRole);
    buttonBox.addButton(tr("Cancel"), QDialogButtonBox::RejectRole);

    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "vhh" <<integerSpinBoxH -> value() << ' ' <<h;
        qDebug() << "vvv" << integerSpinBoxV -> value() << ' ' << v;
        bool doIt = true;
    //    if ( v > integerSpinBoxV -> value() ||  h > integerSpinBoxH -> value() )
     //   {
            if ( v > integerSpinBoxV -> value() || h > integerSpinBoxH -> value() )
            {
                QMessageBox msgBox;
                msgBox.setText("Some cells will be lost.");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                int otv = msgBox.exec();
                if (otv == QMessageBox::Ok)
                {
                }
                else doIt = false;
            }
            else
                qDebug() << "changes";
     /*   }
        else
        {
            doIt = false;

        } */
        if ( doIt )
        {

            int v1 = integerSpinBoxV -> value();
            int h1 = integerSpinBoxH -> value();
            int del = tabwid->getDel();
            tabwid->resizeGrid(h1*del,v1*del);
            //qDebug() << "redraw " << tabwid->getHorNumber() << ' ' << tabwid->getVertNumber() ;
            tabwid->resizeSceneArray(h1,v1);
        }
    }
    qDebug() << "resize main";
}

void MainWindow::on_actionSaveP_triggered()
{
    qDebug() << "here is saving to pattern file";
    bool ret = tabwid->saveAsFile();
    QMessageBox msgBox;

    if (ret)
    {
        msgBox.setText("File was saved successfully");
    }
    else
        msgBox.setText("File was not saved");
    msgBox.exec();
}

void MainWindow::on_actionLoadP_triggered()
{
    tabwid->loadFromFile();
}
