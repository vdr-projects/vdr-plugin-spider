/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef VDR_SPIDER_TABLEAU_H
#define VDR_SPIDER_TABLEAU_H

#include "spider.h"
class Deck;
class Card;
class Pack;
class Pile;
typedef Array<Pile*> Piles;
class FinalHeap;
typedef Array<FinalHeap*> Finals;
class History;


/** --- class Tableau ------------------------------------------------------ **/

class Tableau
{
private:
  int dealCount;
  int cardsToOpen;
  Deck& deck;

public:
  Pack* pack;
  Piles piles;
  Finals finals;
  Pile* selected;
  bool changed;
  History* history;

  /** Constructor */
  Tableau(Deck& deck, int pileCount, int finalCount, int deals);

  /** Destructor */
  ~Tableau();

  /** Current count of deals */
  int deals();

  /** Current count of points */
  int points();

  /** Is no pile empty? */
  bool noPileEmpty();

  /** Matches all cards in all piles? */
  bool allCardsMatches();

  /** Is the game over? */
  bool gameOver();

  /** Select p-th pile by selecting up to max matching cards on its end */
  void select(int p, int max = 0);

  /** Unselect the selected pile */
  void unselect();

  /** Move cards from selected pile to p-th pile */
  void move(int p);

  /** Search move from p-th pile to the next left pile, return destination */
  int autoMoveLeft(int p);

  /** Search move from p-th pile to the next right pile, return destination */
  int autoMoveRight(int p);

  /** Search best move from p-th pile, return destination */
  int autoMove(int p);

  /** Deal one row */
  void deal();

  /** Remove one suit of cards from selected pile to the final heaps */
  void remove();

  /** Go one move backward in the history */
  void backward();

  /** Go one move forward in the history */
  void forward();
};

#endif // VDR_SPIDER_TABLEAU_H
