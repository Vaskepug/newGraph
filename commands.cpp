#include "commands.h"
#include <QDebug>
//AddCommand::AddCommand(MakeSelected::Choice cho, MakeSelected::coord1 cc,  QUndoCommand *parent)
AddCommand::AddCommand(MakeSelected *ms, MakeSelected::coord1 cc,  QUndoCommand *parent)
     : QUndoCommand(parent)
 {
     mSel = ms;
     cc1 = cc;
     ch1 = mSel->getChoice();
     mSel->setSelected(false);
  //   mSel->drawElement(cc1);
     qDebug() << "added command";
 }

 AddCommand::~AddCommand()
 {

 }

 void AddCommand::undo()
 {
  //  mSel->setChoice(ch1);
    mSel->setSelected(false);
    mSel->removeElement(cc1);
    qDebug() << "undo add";
 }

 void AddCommand::redo()
 {
     mSel->setChoiceSimple(ch1);
     mSel->drawElement(cc1);
     qDebug() << "redo add";
 }

 ////////////////////////

DeleteCommand::DeleteCommand(MakeSelected *ms, MakeSelected::coord1 cc,
                             int eType, QUndoCommand *parent)
      : QUndoCommand(parent)
  {
      mSel = ms;
      cc1 = cc;
       mSel->setSelected(false);
      if ( eType < 10 )
      {
           ch1 = static_cast<MakeSelected::Choice>(eType);
          qDebug() << "et " << eType << "caster " << static_cast<MakeSelected::Choice>(eType);
         // mSel->setChoice (static_cast<MakeSelected::Choice>(eType));
      }
      else
      {
        //   mSel->removeElement(cc1);
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
      mSel->setChoiceSimple(ch1);
      mSel->drawElement(cc1);
     qDebug() << "undo del";
  }

  void DeleteCommand::redo()
  {
      mSel->setSelected(false);
      mSel->removeElement(cc1);
      qDebug() << "redo del";
  }


  MoveCommand::MoveCommand(MakeSelected *ms,
              QUndoCommand *parent) : QUndoCommand(parent)
  {
     mSel = ms;
  //   thisSelectedArray = mSel->selectedArray;
     oldStart = mSel->getOldStartPoint();
     oldEnd = mSel->getOldEndPoint();
     newStart = mSel->getStartPoint();
     newEnd = mSel->getEndPoint();
      qDebug() << "added move";
  }

   MoveCommand::~MoveCommand()
   {
        qDebug() << "delete move";
   }

   void MoveCommand::undo()
   {
       mSel->setStartPoint(oldStart);
       mSel->setEndPoint(oldEnd);
       mSel->setRenderSelected(true);
       mSel->setSelected(true);
       mSel->update();
    //   mSel->setSelected(false);
       qDebug() << "Move undo";
   }

   void MoveCommand::redo()
   {
       mSel->setStartPoint(newStart);
       mSel->setEndPoint(newEnd);
       mSel->setRenderSelected(true);
       mSel->setSelected( true );
       mSel->update();
       qDebug() << "Move redo";
   }


  SelectCommand::SelectCommand(MakeSelected *ms,
               QUndoCommand *parent) : QUndoCommand(parent)
   {
      mSel = ms;
      pStart = mSel->getStartPoint();
      pEnd = mSel->getEndPoint();
      qDebug() << "Select added";
   //   thisSelectedArray = mSel->selectedArray;
    //  oldStart = mSel->getOldStartPoint();
    //  oldEnd = mSel->getOldEndPoint();
     // newStart = mSel->getStartPoint();
     // newEnd = mSel->getEndPoint();
   }

    SelectCommand::~SelectCommand()
    {

    }

    void SelectCommand::undo()
    {
    /*    mSel->setStartPoint(oldStart);
        mSel->setEndPoint(oldEnd);
        mSel->setRenderSelected(true);
        mSel->setSelected(true);
        mSel->update();
     //   mSel->setSelected(false);*/
        mSel->setSelected(false);
        mSel->addSelectedArray();
        mSel->deleteSelectedArray();
   //     mSel->setChoice(MakeSelected::MakeCross);
        mSel->update();
        qDebug() << "Select undo";
    }

    void SelectCommand::redo()
    {
       /* mSel->setStartPoint(newStart);
        mSel->setEndPoint(newEnd);
        mSel->setRenderSelected(true);
        mSel->setSelected( true );
        mSel->update();*/
        mSel->setStartPoint(pStart);
        mSel->setEndPoint(pEnd);
        mSel->setSelected(true);
        mSel->update();
        qDebug() << "Select redo";
    }


    UnSelectCommand::UnSelectCommand(MakeSelected *ms,
                 QUndoCommand *parent) : QUndoCommand(parent)
     {
        mSel = ms;
        pStart = mSel->getStartPoint();
        pEnd = mSel->getEndPoint();
        qDebug() << "Select added";
     //   thisSelectedArray = mSel->selectedArray;
      //  oldStart = mSel->getOldStartPoint();
      //  oldEnd = mSel->getOldEndPoint();
       // newStart = mSel->getStartPoint();
       // newEnd = mSel->getEndPoint();
     }

      UnSelectCommand::~UnSelectCommand()
      {

      }

      void UnSelectCommand::redo()
      {
      /*    mSel->setStartPoint(oldStart);
          mSel->setEndPoint(oldEnd);
          mSel->setRenderSelected(true);
          mSel->setSelected(true);
          mSel->update();
       //   mSel->setSelected(false);*/
          mSel->setSelected(false);
          mSel->addSelectedArray();
          mSel->deleteSelectedArray();
     //     mSel->setChoice(MakeSelected::MakeCross);
          mSel->update();
          qDebug() << "Select undo";
      }

      void UnSelectCommand::undo()
      {
         /* mSel->setStartPoint(newStart);
          mSel->setEndPoint(newEnd);
          mSel->setRenderSelected(true);
          mSel->setSelected( true );
          mSel->update();*/
          mSel->setStartPoint(pStart);
          mSel->setEndPoint(pEnd);
          mSel->setSelected(true);
          mSel->update();
          qDebug() << "Select redo";
      }

    FlipRotateCommand::FlipRotateCommand(MakeSelected *ms, bool direction, bool typeOfAction,
                 QUndoCommand *parent) : QUndoCommand(parent)
     {
        mSel = ms;
        dir = direction;
        typeA = typeOfAction;
     /*   if ( typeA )
        {
           mSel->flip(dir);
        }
        else
        {
            mSel->rotate(dir);
        }*/
     }

      FlipRotateCommand::~FlipRotateCommand()
      {

      }

      void FlipRotateCommand::undo()
      {
          if ( typeA )
          {
             mSel->flip(!dir);
          }
          else
          {
              mSel->rotate(!dir);
          }
      }

      void FlipRotateCommand::redo()
      {
          if ( typeA )
          {
             mSel->flip(dir);
          }
          else
          {
              mSel->rotate(dir);
          }
      }

