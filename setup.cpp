/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * Copyright (C) 2005-2007, Thomas G�nther <tom@toms-cafe.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * $Id: setup.cpp 95 2007-09-21 23:01:10Z tom $
 */

#include "setup.h"
#include "i18n.h"
#include <strings.h>

using namespace SpiderPlugin;


//--- class SpiderPlugin::SetupData --------------------------------------------

/** Constructor
 *
 * Initialize the setup parameters of the plugin with standard values.
 */
SetupData::SetupData()
{
  variation = Mini;
}

/** Parse the setup parameters of the plugin.
 *
 * This method is called for each setup parameter the plugin has previously
 * stored in the global setup data.
 */
bool SetupData::parse(const char* name, const char* value)
{
  if (!strcasecmp(name, "Variation"))
    variation = atoi(value);
  else
    return false;
  return true;
}


//--- class SpiderPlugin::SetupPage --------------------------------------------

/** Constructor */
SetupPage::SetupPage(SetupData& setup) :
  setup(setup), data(setup)
{
  variationTexts[0] = tr("Mini (one deck)");
  variationTexts[1] = tr("Normal");
  Add(new cMenuEditStraItem(tr("Variation"), &data.variation,
                            2, variationTexts));
}

/** Store the setup parameters of the plugin.
 *
 * The setup parameters of the plugin are stored into the global setup data
 * file.
 */
void SetupPage::Store()
{
  setup = data;
  SetupStore("Variation", setup.variation);
}
