/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: game.h 2 2005-05-14 22:25:56Z tom $
 */

#ifndef VDR_SPIDER_GAME_H
#define VDR_SPIDER_GAME_H

class SpiderSetup;
class Deck;
class Tableau;
class Card;
class Bitmap;
#include <vdr/config.h>
#include <vdr/osdbase.h>
#include <vdr/osd.h>

// Compatibility to older vdr versions
#if VDRVERSNUM < 10307
  #define cOsd_ cOsdBase
#else
  #define cOsd_ cOsd
#endif


/** --- class SpiderGame --------------------------------------------------- **/

class SpiderGame : public cOsdObject
{
private:
  const SpiderSetup& setup;
  const char* confdir;
  int width, height;
  int xPos, yPos;
  int xDist, yDist;
  cOsd_* osd;
  Bitmap* info;
  const char* infoText;
  Deck* deck;
  Tableau* tableau;
  unsigned int currentPile;
  enum { cursorOnPile, selectedPile, cursorOnPack, gameOver } status;

  /** Start a new game */
  void start();

  /** Paint all pieces of the game */
  void paint();

  /** Paint the cursor onto a card */
  void paintCursor(int x, int y);

  /** Paint the pack */
  void paintPack();

  /** Paint a final heap */
  void paintFinal(unsigned int f);

  /** Paint a pile */
  void paintPile(unsigned int p);

  /** Paint an empty card frame */
  void paintFrame(int x, int y);

  /** Paint a card back */
  void paintBack(int x, int y);

  /** Paint a card */
  void paintCard(int x, int y, const Card& card);

public:

  /** Constructor */
  SpiderGame(const SpiderSetup& setup, const char* confdir);

  /** Destructor */
  virtual ~SpiderGame();

  /** Display the game on the OSD */
  virtual void Show();

  /** Process user events */
  virtual eOSState ProcessKey(eKeys key);
};

#endif // VDR_SPIDER_GAME_H
