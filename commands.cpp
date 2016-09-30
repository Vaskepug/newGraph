#include "commands.h"
#include <QDebug>
//AddCommand::AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc,  QUndoCommand *parent)
AddCommand::AddCommand(MakeSelected *ms, MakeSelected::coord1 cc,  QUndoCommand *parent)
     : QUndoCommand(parent)
 {
     mSel = ms;
     cc1 = cc;
     ch1 = mSel->getChoice();
     mSel->drawElement(cc1);
    // qDebug() << "added " << ch1;
 }

 AddCommand::~AddCommand()
 {

 }

 void AddCommand::undo()
 {

     mSel->removeElement(cc1);
   // qDebug() << "undo 11";
 }

 void AddCommand::redo()
 {
     mSel->setChoice(ch1);
     mSel->drawElement(cc1);
  //   qDebug() << "redo 11";
 }

 ////////////////////////

DeleteCommand::DeleteCommand(MakeSelected *ms, MakeSelected::coord1 cc,
                             int eType, QUndoCommand *parent)
      : QUndoCommand(parent)
  {
      mSel = ms;
      cc1 = cc;

      if ( eType < 10 )
      {
           ch1 = static_cast<MakeSelected::Choice>(eType);
          qDebug() << "et " << eType << "caster " << static_cast<MakeSelected::Choice>(eType);
         // mSel->setChoice (static_cast<MakeSelected::Choice>(eType));
      }
      else
      {
           mSel->removeElement(cc1);
          int i10 = eType / 10;
          ch1 = static_cast<MakeSelected::Choice>(i10);
          cc1.i = cc1.i - 1;
      }

  }

  DeleteCommand::~DeleteCommand()
  {

  }

  void DeleteCommand::undo()
  {
      mSel->setChoice(ch1);
      mSel->drawElement(cc1);
     qDebug() << "undo 22";
  }

  void DeleteCommand::redo()
  {
      mSel->removeElement(cc1);
      qDebug() << "redo 22";
  }
