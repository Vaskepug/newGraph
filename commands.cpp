#include "commands.h"
#include "functions.h"
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
     //thisSelectedArray = mSel->getSelectedArray();
  //   thisSelectedArray = mSel->selectedArray;
     oldStart = mSel->getOldStartPoint();
     oldEnd = mSel->getOldEndPoint();
     newStart = mSel->getStartPoint();
     newEnd = mSel->getEndPoint();
     copySelectedArray();
     // qDebug() << "added move " <<  oldEnd.x() << ' ' << newEnd.x();
  }

   MoveCommand::~MoveCommand()
   {
        qDebug() << "delete move";
        //if ( thisSelectedArray != nullptr )
        if ( thisSelectedArray.size() != 0 )
        {
          //  deleteArray(thisSelectedArray,thisSelectedArrayXSize);
            deleteVectorContent( thisSelectedArray, thisSelectedArrayXSize );
        /*  for( int i = 0; i < selectedArrayXSize; i++ )
          {
            //  qDebug() << "deleted " << selectedArrayXSize << ' ' << selectedArrayYSize;
                 delete [] selectedArray[i];
           }
            delete selectedArray;*/
          //was  thisSelectedArray = nullptr;
//           thisSselectedArrayXSize = 0;
  //         selectedArrayYSize = 0;
    //       wasDeleted = true;
        }
   }

   void MoveCommand::undo()
   {
       mSel->setStartPoint(oldStart);
       mSel->setStartPoint(oldStart);
       mSel->setEndPoint(oldEnd);
       mSel->setRenderSelected(true);
       mSel->setSelected(true);
        ///
       if ( mSel->getSelectedArrayXSize() == 0 && mSel->getSelectedArrayYSize() == 0 )
       {
           mSel->setSelectedArrayXSize(thisSelectedArrayXSize);
           mSel->setSelectedArrayYSize(thisSelectedArrayYSize);
           mSel->fillSelectedArrayfromOutside(thisSelectedArray);
           clearOldSelectedArray();
       }
         ///

     //was  mSel->pasteSelected(oldStart,false);
         // make selected here and delete at the old palce
         // move saved selected to the new place
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
       qDebug() << "Move redo ";
   }

   void MoveCommand::copySelectedArray()
   {
       thisSelectedArrayXSize = mSel->getSelectedArrayXSize();
       thisSelectedArrayYSize = mSel->getSelectedArrayYSize();
       allocateVector( thisSelectedArray, thisSelectedArrayXSize, thisSelectedArrayYSize );
       QVector< QVector<int> > sA = *mSel->getSelectedArray();
       for ( int i = 0; i < thisSelectedArrayXSize; i ++)
       {
           for ( int j = 0; j < thisSelectedArrayYSize; j ++)
           {
               thisSelectedArray[i][j] = sA[i][j];
           }
       }
       // locate
       // was locateArray(thisSelectedArray,thisSelectedArrayXSize,thisSelectedArrayYSize);
     /*  thisSelectedArray = new int *[mSel->getSelectedArrayXSize()];
       for (int i = 0; i < thisSelectedArrayXSize; i ++)
       {
           thisSelectedArray[i] = new int [mSel->getSelectedArrayYSize()];
       }*/
       // copy
       //int **sA = mSel->getSelectedArray();
    /*   QVector< QVector<int> > sA = mSel->getSelectedArray();
       for ( int i = 0; i < thisSelectedArrayXSize; i ++)
       {
           for ( int j = 0; j < thisSelectedArrayYSize; j ++)
           {
               thisSelectedArray[i][j] = sA[i][j];
           }
       }*/


   }

   void MoveCommand::clearOldSelectedArray()
   {
       mSel->clearSelected(newStart);
       qDebug() << "new St " << newStart << ' ' << oldStart;
   }

   void MoveCommand::pasteSelectedArray()
   {
     //  QPointF tmp;
     //  tmp.setX();
      //  mSel->pasteSelected(leftTopZero);
   }

   ///////////

  SelectCommand::SelectCommand(MakeSelected *ms,
               QUndoCommand *parent) : QUndoCommand(parent)
   {
      mSel = ms;
      pStart = mSel->getStartPoint();
      pEnd = mSel->getEndPoint();
      thisSelectedArrayXSize = mSel->getSelectedArrayXSize();
      thisSelectedArrayYSize = mSel->getSelectedArrayYSize();
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
        mSel->setSelectedArrayXSize(thisSelectedArrayXSize);
        mSel->setSelectedArrayYSize(thisSelectedArrayYSize);
        mSel->makeSelectedArray();
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
        oldStart = mSel->getOldStartPoint();
        oldEnd = mSel->getOldEndPoint();
        newStart = mSel->getStartPoint();
        newEnd = mSel->getEndPoint();
        dir = direction;
        typeA = typeOfAction;
        copySelectedArray();
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
          if ( thisSelectedArray.size() != 0 )
          {
              deleteVectorContent( thisSelectedArray, thisSelectedArrayXSize );
           }
      }

      void FlipRotateCommand::undo()
      {
        // mSel->setStartPoint(oldStart);
       //  mSel->setEndPoint(oldEnd);
         mSel->setStartPoint(newStart);
         mSel->setEndPoint(newEnd);
         mSel->setRenderSelected(true);
         mSel->setSelected(true);
          ///
         if ( mSel->getSelectedArrayXSize() == 0 && mSel->getSelectedArrayYSize() == 0 )
         {
             mSel->setSelectedArrayXSize(thisSelectedArrayXSize);
             mSel->setSelectedArrayYSize(thisSelectedArrayYSize);
             mSel->fillSelectedArrayfromOutside(thisSelectedArray);
             clearOldSelectedArray();
         }
           ///

       //was  mSel->pasteSelected(oldStart,false);
           // make selected here and delete at the old palce
           // move saved selected to the new place
         mSel->update();
    //   mSel->setSelected(false);
         qDebug() << "flip undo";
         /* was if ( typeA )
          {
              qDebug() << "flip undo";
             mSel->flip(dir);
          }
          else
          {
              mSel->rotate(dir);
          }*/
      }

      void FlipRotateCommand::redo()
      {
        mSel->setStartPoint(newStart);
        mSel->setEndPoint(newEnd);
        mSel->setRenderSelected(true);
        mSel->setSelected( true );
        mSel->update();
        qDebug() << "flip redo ";
        /*  if ( typeA )
          {
             mSel->flip(dir);
          }
          else
          {
              mSel->rotate(dir);
          }*/
      }

      void FlipRotateCommand::copySelectedArray()
      {
          thisSelectedArrayXSize = mSel->getSelectedArrayXSize();
          thisSelectedArrayYSize = mSel->getSelectedArrayYSize();
          allocateVector( thisSelectedArray, thisSelectedArrayXSize, thisSelectedArrayYSize );
          QVector< QVector<int> > sA = *mSel->getSelectedArray();
          for ( int i = 0; i < thisSelectedArrayXSize; i ++)
          {
              for ( int j = 0; j < thisSelectedArrayYSize; j ++)
              {
                  thisSelectedArray[i][j] = sA[i][j];
              }
          }
       }
      void FlipRotateCommand::clearOldSelectedArray()
      {
          mSel->clearSelected(newStart);
          qDebug() << "new St " << newStart << ' ' << oldStart;
      }
