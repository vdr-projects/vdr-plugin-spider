/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include "setup.h"
#include "i18n.h"
#include <strings.h>


/** --- class SpiderSetup -------------------------------------------------- **/

SpiderSetup::SpiderSetup()
{
  variation = Mini;
}

bool SpiderSetup::parse(const char* name, const char* value)
{
  if (!strcasecmp(name, "Variation"))
    variation = atoi(value);
  else
    return false;
  return true;
}


/** --- class SpiderSetupMenu ---------------------------------------------- **/

SpiderSetupMenu::SpiderSetupMenu(SpiderSetup& setup) :
  setup(setup), data(setup)
{
  variationTexts[0] = tr("Mini (one deck)");
  variationTexts[1] = tr("Normal");
  Add(new cMenuEditStraItem(tr("Variation"), &data.variation,
                            2, variationTexts));
}

void SpiderSetupMenu::Store()
{
  setup = data;
  SetupStore("Variation", setup.variation);
}
