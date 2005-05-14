/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef VDR_SPIDER_SETUP_H
#define VDR_SPIDER_SETUP_H

#include <vdr/menuitems.h>


/** --- class SpiderSetup -------------------------------------------------- **/

class SpiderSetup
{
public:
  typedef enum { Mini, Normal } Variations;
  int variation;

  SpiderSetup();
  bool parse(const char* name, const char* value);
};


/** --- class SpiderSetupMenu ---------------------------------------------- **/

class SpiderSetupMenu : public cMenuSetupPage
{
private:
  const char* variationTexts[2];
  SpiderSetup& setup;
  SpiderSetup data;
protected:
  virtual void Store();
public:
  SpiderSetupMenu(SpiderSetup& setup);
};

#endif // VDR_SPIDER_SETUP_H
