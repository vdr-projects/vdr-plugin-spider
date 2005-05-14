/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef VDR_SPIDER_DECK_H
#define VDR_SPIDER_DECK_H

#include "spider.h"
class Card;
typedef Array<Card> Cards;


/** --- class Deck --------------------------------------------------------- **/

class Deck
{
protected:
  Cards allCards;
public:
  int cardsInSuit;
  int suitCount;
  int deckCount;

  /** Constructor */
  Deck(int cards, int suits, int decks);

  /** Current count of cards */
  int count() const;

  /** Card in deck */
  const Card& card(int position) const;

  /** Shuffle the deck */
  void shuffle();
};


/** --- class Card --------------------------------------------------------- **/

class Card
{
public:
  int suit;
  int rank;

  /** Constructor */
  Card(int s = -1, int r = -1);

  /** Matches this card to an other card? */
  bool matchesTo(const Card& other) const;
};

#endif // VDR_SPIDER_DECK_H
