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
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };

class DeleteCommand : public QUndoCommand
 {
 public:
    // AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc, QUndoCommand *parent = 0);
     DeleteCommand(MakeSelected *ms, MakeSelected::coord1 cc,
                   int eType, QUndoCommand *parent = 0);
     ~DeleteCommand();
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };

class MoveCommand : public QUndoCommand
 {
 public:
     MoveCommand(MakeSelected *ms, QPointF startP, QPointF endP,
                 int selectedArrayXs, int selectedArrayYs, int **selArray,
                   int eType, QUndoCommand *parent = 0);
     ~MoveCommand();
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };

class FlipRotateCommand : public QUndoCommand
 {
 public:
     FlipRotateCommand(MakeSelected *ms, QPointF startP, QPointF endP,
                 int selectedArrayXs, int selectedArrayYs, int **selArray,
                   int eType, QUndoCommand *parent = 0);
     ~FlipRotateCommand();
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };

class SelectCommand : public QUndoCommand
 {
 public:
     SelectCommand(MakeSelected *ms, QPointF startP, QPointF endP,
                 int selectedArrayXs, int selectedArrayYs, int **selArray,
                   int eType, QUndoCommand *parent = 0);
     ~SelectCommand();
    MakeSelected::Choice ch1;
    MakeSelected::coord1 cc1;
    MakeSelected *mSel;
     void undo();
     void redo();

 private:

 };
class PasteCommand : public QUndoCommand
 {
 public:
     PasteCommand(MakeSelected *ms, QPointF startP, QPointF endP,
                 int selectedArrayXs, int selectedArrayYs, int **selArray,
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
