#include "commands.h"
#include <QDebug>
//AddCommand::AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc,  QUndoCommand *parent)
AddCommand::AddCommand(MakeSelected *ms, MakeSelected::coord1 cc,  QUndoCommand *parent)
     : QUndoCommand(parent)
 {
       // ch1 = cho;
     mSel = ms;
     cc1 = cc;
     mSel->drawElement(cc1);
    // qDebug() << "added " << ch1;
 }

 AddCommand::~AddCommand()
 {

 }

 void AddCommand::undo()
 {
    qDebug() << "undo " << ch1;
 }

 void AddCommand::redo()
 {

 }
