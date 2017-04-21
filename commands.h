#ifndef COMMANDS_H
#define COMMANDS_H

 #include <QUndoCommand>
#include "makeselected.h"

class AddCommand : public QUndoCommand
 {
 public:
    // AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc, QUndoCommand *parent = 0);
     AddCommand(MakeSelected *ms, MakeSelected::coord1 cc, QUndoCommand *parent = 0);
     ~AddCommand();
     void undo();
     void redo();

 private:
     MakeSelected::Choice ch1;
     MakeSelected::coord1 cc1;
     MakeSelected *mSel;
 };

class DeleteCommand : public QUndoCommand
 {
 public:
    // AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc, QUndoCommand *parent = 0);
     DeleteCommand(MakeSelected *ms, MakeSelected::coord1 cc,
                   int eType, QUndoCommand *parent = 0);
     ~DeleteCommand();

     void undo();
     void redo();

 private:
     MakeSelected::Choice ch1;
     MakeSelected::coord1 cc1;
     MakeSelected *mSel;

 };

class MoveCommand : public QUndoCommand
 {
 public:
     MoveCommand(MakeSelected *ms,
                 QUndoCommand *parent = 0);
     ~MoveCommand();

     void undo();
     void redo();
    friend void deleteArray(int **array1, int xlen);
 private:
     MakeSelected *mSel;
     //int **thisSelectedArray;
     QVector< QVector<int> > thisSelectedArray;
     int thisSelectedArrayXSize;
     int thisSelectedArrayYSize;
     QPointF newStart;
     QPointF newEnd;
     QPointF oldStart;
     QPointF oldEnd;
     void copySelectedArray();
     void pasteSelectedArray();
 };

class FlipRotateCommand : public QUndoCommand
 {
 public:
     FlipRotateCommand(MakeSelected *ms, bool direction,
                       bool typeOfAction, QUndoCommand *parent = 0);
     ~FlipRotateCommand();

     void undo();
     void redo();

 private:
     bool dir;
     bool typeA;
     MakeSelected *mSel;

 };

class SelectCommand : public QUndoCommand
 {
 public:
     SelectCommand(MakeSelected *ms, QUndoCommand *parent = 0);
     ~SelectCommand();
  //  MakeSelected::Choice ch1;
  //  MakeSelected::coord1 cc1;
 private:
    MakeSelected *mSel;
    QPointF pStart;
    QPointF pEnd;
    int thisSelectedArrayXSize;
    int thisSelectedArrayYSize;
     void undo();
     void redo();

 private:

 };

class UnSelectCommand : public QUndoCommand
 {
 public:
     UnSelectCommand(MakeSelected *ms, QUndoCommand *parent = 0);
     ~UnSelectCommand();
  //  MakeSelected::Choice ch1;
  //  MakeSelected::coord1 cc1;
 private:
    MakeSelected *mSel;
    QPointF pStart;
    QPointF pEnd;
     void undo();
     void redo();

 private:

 };

class PasteCommand : public QUndoCommand
 {
 public:
     PasteCommand(MakeSelected *ms, QPointF startP, QPointF endP,
                // int selectedArrayXs, int selectedArrayYs, int **selArray,
                 int selectedArrayXs, int selectedArrayYs,
                  QVector< QVector<int> > selArray,
                   int eType, QUndoCommand *parent = 0);
     ~PasteCommand();
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };

#endif // COMMANDS_H
