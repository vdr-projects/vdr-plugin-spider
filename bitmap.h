/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: bitmap.h 2 2005-05-14 22:25:56Z tom $
 */

#ifndef VDR_SPIDER_BITMAP_H
#define VDR_SPIDER_BITMAP_H

#include <vdr/config.h>
#include <vdr/osdbase.h>
#include <vdr/osd.h>

// Compatibility to older vdr versions
#if VDRVERSNUM < 10307
  #define tColor eDvbColor
#endif


/** --- class Bitmap ------------------------------------------------------- **/

class Bitmap : public cBitmap
{
public:

  /** Constructor */
  Bitmap(int width, int height);

  /** Constructor for a bitmap with frame */
  Bitmap(int width, int height, tColor frameColor, tColor backgroundColor);

  /** Constructor for a bitmap read from an xpm file */
  Bitmap(int width, int height, const char* dir, const char* name);

  /** Constructor for a card bitmap read from an xpm file */
  Bitmap(int width, int height, const char* dir,
         const char* suit, const char* rank);

  /** Write a text into the bitmap */
  void text(const char* text, bool centered = true);

  /** Draw a frame into the bitmap */
  void frame(int x1, int y1, int x2, int y2, tColor frameColor);

  /** Load a bitmap from an xpm file - taken from ElchiAIO4d patch */
  bool loadXpm(const char* FileName, tColor NoneColor = clrTransparent);

#if VDRVERSNUM < 10307
  /** Wrap the text to fit into the bitmap - taken from font.c in VDR 1.3.7 */
  char *textWrapper(const char *Text, int *p_lines);
#endif
};

#endif // VDR_SPIDER_BITMAP_H
