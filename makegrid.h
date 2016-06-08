#ifndef MAKEGRID_H
#define MAKEGRID_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class MakeGrid : public  QGraphicsItem
{

public:
    MakeGrid(int width, int height,int del);

    public :

    void sizeChanged(int w, int h);

    private:

    int width1;
    int height1;
    int del;

    virtual QRectF boundingRect() const;
    ///< must be re-implemented in this class to provide the
    /// //diminsions of the box to the QGraphicsView
    virtual void paint (QPainter *painter,
                        const QStyleOptionGraphicsItem *option, QWidget *widget);
    ///< must be re-implemented here to pain the box on the paint-event
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);

signals:
  void keyCaught(QKeyEvent *e);
};
#endif // MAKEGRID_H
