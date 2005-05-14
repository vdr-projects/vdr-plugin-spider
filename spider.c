/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: spider.c 2 2005-05-14 22:25:56Z tom $
 */

#include "spider.h"
#include "game.h"
#include "setup.h"
#include "i18n.h"
#include <vdr/plugin.h>


static const char* VERSION       = "0.1.0";
static const char* DESCRIPTION   = "Spider Arachnid - the best patience game";
static const char* MAINMENUENTRY = "Spider Arachnid";


/** --- class SpiderPlugin ------------------------------------------------- **/

class SpiderPlugin : public cPlugin
{
private:
  SpiderSetup setup;
public:
  virtual const char* Version() { return VERSION; }
  virtual const char* Description() { return tr(DESCRIPTION); }
  virtual bool Start();
  virtual const char* MainMenuEntry() { return tr(MAINMENUENTRY); }
  virtual cOsdObject* MainMenuAction();
  virtual cMenuSetupPage* SetupMenu();
  virtual bool SetupParse(const char* name, const char* value);
};

bool SpiderPlugin::Start()
{
  RegisterI18n(Phrases);
  return true;
}

cOsdObject* SpiderPlugin::MainMenuAction()
{
  return new SpiderGame(setup, ConfigDirectory(Name()));
}

cMenuSetupPage* SpiderPlugin::SetupMenu()
{
  return new SpiderSetupMenu(setup);
}

bool SpiderPlugin::SetupParse(const char* name, const char* value)
{
  return setup.parse(name, value);
}

VDRPLUGINCREATOR(SpiderPlugin); // Don't touch this!
