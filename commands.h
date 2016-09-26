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

#endif // COMMANDS_H
