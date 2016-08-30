#ifndef TWIDGET_H
#define TWIDGET_H
#include <QTabWidget>

class TWidget : public QTabWidget
{
    Q_OBJECT
    public:
       explicit TWidget(QTabWidget *parent = 0);
        QTabBar* tabBar();
        ~TWidget(){};
    public slots:
        void closeTab(int index);
};

#endif // TWIDGET_H
