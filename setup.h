/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: setup.h 5 2005-05-15 18:40:40Z tom $
 */

#ifndef VDR_SPIDER_SETUP_H
#define VDR_SPIDER_SETUP_H

#include "spider.h"
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
