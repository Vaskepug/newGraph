#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QDebug>

#include "tabclass.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBars(void);
    QToolBar* topToolbar;
    QToolBar* leftToolbar;

    QActionGroup* vertActionGroup;
   // QActionGroup* plusMinusActionGroup;
    //QActionGroup* flipActionGroup;

    QAction* decrease;
    QAction* makeCross;
    QAction* makeCircle;
    QAction* makeM;
    QAction* makeCrossed;
    QAction* makeMiddle;
    QAction* makeBrick;
    QAction* setGrid;
    QAction* thisExit;
    QAction* increase;
    QAction* select;
    QAction* flipHoriz;
    QAction* flipVert;


private slots:
    void thisExitf(void);
    void savef(void);
    void addTabs(void);
    void actionGroupClicked(QAction*);
    void selectf(void);
    void on_actionOpen_triggered();
    void flipHorizf();
    void flipVertf();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
