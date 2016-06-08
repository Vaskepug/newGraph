#ifndef DRAWCROSSES_H
#define DRAWCROSSES_H
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class DrawCrosses:public QGraphicsScene
{

    Q_OBJECT
public:
    explicit DrawCrosses(QObject *parent = 0);
    enum Choice { Nothing, MakeCross, MakeCorn, MakeCrossed,
                  MakeMiddle, MakeM, MakeBrick};
    void init(unsigned int, unsigned int);
    Choice choice;
    void setChoice(Choice cho);
  //  void setSelected();

private:
    bool selected;

//protected:
   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
#endif // DRAWCROSSES_H
