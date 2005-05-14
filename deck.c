/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "deck.h"
#include <vdr/config.h>
#include <vdr/tools.h>
#include <stdlib.h>


/** Random number 0 .. max-1 */
unsigned int rand(unsigned int max)
{
  static unsigned int seed =
#if VDRVERSNUM >= 10318
    cTimeMs::Now();
#else
    time_ms();
#endif
  return (unsigned int)((double)max * rand_r(&seed) / (RAND_MAX + 1.0));
}


/** --- class Deck --------------------------------------------------------- **/

/** Constructor */
Deck::Deck(int cards, int suits, int decks) :
  allCards(cards * suits * decks)
{
  cardsInSuit = cards;
  suitCount = suits;
  deckCount = decks;
  shuffle();
}

/** Current count of cards */
int Deck::count() const
{
  return allCards.size();
}

/** Card in deck */
const Card& Deck::card(int position) const
{
  return allCards[position];
}

/** Shuffle the deck */
void Deck::shuffle()
{
  for (unsigned int i = 0; i < allCards.size(); ++i)
  {
    int pos = -1;
    while (pos < 0)
      pos = rand(allCards.size());
    while (allCards[pos].suit >= 0)
      pos = (pos + 1) % allCards.size();
    allCards[pos] = Card((i / cardsInSuit) % suitCount, i % cardsInSuit);
  }
}


/** --- class Card --------------------------------------------------------- **/

/** Constructor */
Card::Card(int s, int r)
{
  suit = s;
  rank = r;
}

/** Matches this card to an other card? */
bool Card::matchesTo(const Card& other) const
{
  return (suit == other.suit && rank + 1 == other.rank);
}
