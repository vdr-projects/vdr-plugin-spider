/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: history.h 85 2007-06-20 16:14:45Z tom $
 */

#ifndef VDR_SPIDER_HISTORY_H
#define VDR_SPIDER_HISTORY_H

#include "spider.h"
class Pack;
class Pile;
typedef Array<Pile*> Piles;
class FinalHeap;
class Move;
typedef Vector<Move*> Moves;


/** --- class History ------------------------------------------------------ **/

class History
{
private:
  Moves history;
  unsigned int executed;

public:

  /** Constructor */
  History();

  /** Destructor */
  ~History();

  /** Current move in the history */
  Move* current();

  /** Add a new move */
  void add(Move* move);

  /** Set previous move as current */
  void backward();

  /** Set next move as current */
  void forward();

  /** Are there executed moves in the history */
  bool movesExecuted();

  /** Are there moves to execute in the history */
  bool movesToExecute();
};


/** --- base class Move ---------------------------------------------------- **/

class Move
{
public:

  /** Destructor */
  virtual ~Move() {};

  /** Do the move */
  virtual void execute() = 0;

  /** Redo the move */
  virtual void takeBack() = 0;
};


/** --- class DealMove ----------------------------------------------------- **/

class DealMove : public Move
{
private:
  Pack* source;
  Piles& destination;

public:

  /** Constructor */
  DealMove(Pack* s, Piles& d);

  /** Do the move */
  void execute();

  /** Redo the move */
  void takeBack();
};


/** --- class NormalMove --------------------------------------------------- **/

class NormalMove : public Move
{
private:
  Pile* source;
  Pile* destination;
  int count;
  bool turn;

public:

  /** Constructor */
  NormalMove(Pile* s, Pile* d, int c, bool t);

  /** Do the move */
  void execute();

  /** Redo the move */
  void takeBack();
};


/** --- class FinalMove ---------------------------------------------------- **/

class FinalMove : public Move
{
private:
  Pile* source;
  FinalHeap* destination;
  int count;
  bool turn;
  bool bonus;

public:

  /** Constructor */
  FinalMove(Pile* s, FinalHeap* d, int c, bool t, bool b);

  /** Do the move */
  void execute();

  /** Redo the move */
  void takeBack();
};

#endif // VDR_SPIDER_HISTORY_H
