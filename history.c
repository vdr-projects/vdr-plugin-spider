/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "history.h"
#include "deck.h"
#include "heap.h"


/** --- class History ------------------------------------------------------ **/

/** Constructor */
History::History()
{
  executed = 0;
}

/** Destructor */
History::~History()
{
  for (unsigned int pos = history.size(); pos > 0; --pos)
  {
    // Remove object created outside of History
    delete history.back();
    history.pop_back();
  }
}

/** Current move in the history */
Move* History::current()
{
  return history[executed - 1];
}

/** Add a new move */
void History::add(Move* move)
{
  for (unsigned int pos = history.size(); pos > executed; --pos)
  {
    // Remove object created outside of History
    delete history.back();
    history.pop_back();
  }
  history.push_back(move);
  ++executed;
}

/** Set previous move as current */
void History::backward()
{
  if (movesExecuted())
    --executed;
}

/** Set next move as current */
void History::forward()
{
  if (movesToExecute())
    ++executed;
}

/** Are there executed moves in the history */
bool History::movesExecuted()
{
  return executed > 0;
}

/** Are there moves to execute in the history */
bool History::movesToExecute()
{
  return executed < history.size();
}


/** --- class DealMove ----------------------------------------------------- **/

/** Constructor */
DealMove::DealMove(Pack* s, Piles& d) :
  source(s), destination(d)
{
}

/** Do the move */
void DealMove::execute()
{
  source->deal(destination);
}

/** Redo the move */
void DealMove::takeBack()
{
  source->takeBackDeal(destination);
}


/** --- class NormalMove --------------------------------------------------- **/

/** Constructor */
NormalMove::NormalMove(Pile* s, Pile* d, int c, bool t) :
  source(s), destination(d), count(c), turn(t)
{
}

/** Do the move */
void NormalMove::execute()
{
  source->moveTo(destination, count);
  if (turn)
    source->turn();
}

/** Redo the move */
void NormalMove::takeBack()
{
  if (turn)
    source->turn();
  destination->moveTo(source, count);
}


/** --- class FinalMove ---------------------------------------------------- **/

/** Constructor */
FinalMove::FinalMove(Pile* s, FinalHeap* d, int c, bool t, bool b) :
  source(s), destination(d), count(c), turn(t), bonus(b)
{
}

/** Do the move */
void FinalMove::execute()
{
  source->moveTo(destination, count);
  if (turn)
    source->turn();
  destination->setBonus(bonus);
}

/** Redo the move */
void FinalMove::takeBack()
{
  destination->setBonus(false);
  if (turn)
    source->turn();
  destination->moveTo(source, count);
}
