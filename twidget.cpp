#include "twidget.h"

TWidget::TWidget(QTabWidget *parent) : QTabWidget(parent)
{
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
}

void TWidget::closeTab(int index)
{
    this->removeTab(index);
}

QTabBar* TWidget::tabBar()
{
    return QTabWidget::tabBar();
}
