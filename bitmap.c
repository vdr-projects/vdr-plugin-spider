/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id: bitmap.c 2 2005-05-14 22:25:56Z tom $
 */

#include "bitmap.h"
#include <vdr/config.h>
#include <vdr/osdbase.h>
#include <vdr/osd.h>
#include <ctype.h>

// Compatibility to older vdr versions
#if VDRVERSNUM < 10307
  #define tColor eDvbColor
  #define DrawRectangle Fill
  #define DrawPixel SetPixel
#endif


/** --- class Bitmap ------------------------------------------------------- **/

/** Constructor */
Bitmap::Bitmap(int width, int height) :
  cBitmap(width, height, 4)
{
}

/** Constructor for a bitmap with frame */
Bitmap::Bitmap(int width, int height, tColor frameColor, tColor backgroundColor) :
  cBitmap(width, height, 4)
{
  DrawRectangle(0, 0, width - 1, height - 1, backgroundColor);
  frame(0, 0, width - 1, height - 1, frameColor);
}

/** Constructor for a bitmap read from an xpm file */
Bitmap::Bitmap(int width, int height, const char* dir, const char* name) :
  cBitmap(width, height, 4)
{
  char* path;
  asprintf(&path, "%s/%s.xpm", dir, name);
  loadXpm(path);
  free(path);
}

/** Constructor for a card bitmap read from an xpm file */
Bitmap::Bitmap(int width, int height, const char* dir,
               const char* suit, const char* rank) :
  cBitmap(width, height, 4)
{
  char* path;
  asprintf(&path, "%s/%s_%s.xpm", dir, suit, rank);
  loadXpm(path);
  free(path);
}

/** Write a text into the bitmap */
void Bitmap::text(const char* text, bool centered)
{
  DrawRectangle(0, 0, Width() - 1, Height() - 1, clrWhite);
  frame(0, 0, Width() - 1, Height() - 1, clrRed);

#if VDRVERSNUM < 10307
  SetFont(fontOsd);
  int lineCount;
  char* wrapper = textWrapper(text, &lineCount);
  int y = max((Height() - lineCount * cOsd::LineHeight()) / 2, 0);
  char* line = wrapper;
  while (*line)
  {
    char* newline = strchr(line, '\n');
    if (newline)
      *newline = 0;
    int x = 0;
    if (centered)
      x = max((Width() - Width(line)) / 2, 0);
    Text(x, y, line, clrBlack, clrWhite);
    if (newline)
      *newline = '\n';
    if (!newline)
      break;
    line = newline + 1;
    y += cOsd::LineHeight();
  }
  free(wrapper);
#else
  const cFont* font = cFont::GetFont(fontOsd);
  cTextWrapper wrapper(text, font, Width());
  int y = max((Height() - wrapper.Lines() * font->Height()) / 2, 0);
  for (int l = 0; l < wrapper.Lines(); ++l, y += font->Height())
  {
    int x = 0;
    if (centered)
      x = max((Width() - font->Width(wrapper.GetLine(l))) / 2, 0);
    DrawText(x, y, wrapper.GetLine(l), clrBlack, clrWhite, font);
  }
#endif
}

/** Draw a frame into the bitmap */
void Bitmap::frame(int x1, int y1, int x2, int y2, tColor frameColor)
{
  DrawRectangle(x1,     y1,     x2,     y1 + 1, frameColor);
  DrawRectangle(x1,     y1,     x1 + 1, y2,     frameColor);
  DrawRectangle(x1,     y2 - 1, x2,     y2,     frameColor);
  DrawRectangle(x2 - 1, y1,     x2,     y2,     frameColor);
}

/** Load a bitmap from an xpm file - taken from ElchiAIO4d patch */
bool Bitmap::loadXpm(const char* FileName, tColor NoneColor)
{
  bool bRet = false;
  FILE *infile;
  infile = fopen(FileName, "r");
  if (infile) {
     bool ok = true;
     char buf[512];
     char *ptr;
     int state = 0;
     int width, height, colors, colwidth, cnt = 0;
     int temp;
     uint pal[65536];

     while (ok && fgets(buf, sizeof(buf), infile) != NULL) {
       int len = strlen(buf);
       ptr = buf;
       if (ptr[len - 1] == '\n')
          ptr[--len] = '\0';

       if (state > 0 && strncmp(ptr, "/*", 2) == 0) {
          continue;
          }

       switch (state) {
         case 0:
              if (strcmp(ptr, "/* XPM */") != 0) {
                 esyslog("ERROR: loading xpm %s failed: invalid header", FileName);
                 ok = false;
                 break;
                 }
              ++state;
              break;
         case 1:
              ++state;
              break;
         case 2:
              sscanf(ptr, "\"%d %d %d %d\",", &width, &height, &colors, &colwidth);
              if (colwidth > 2) {
                 esyslog("ERROR: wrong colorwidth in xpm %s", FileName);
                 ok = false;
                 break;
                 }
              cnt = 0;
              ++state;
              break;
         case 3:
              ++ptr;
              temp = 0;
              for (int i = 0; i < colwidth; ++i) {
                  temp <<= 8;
                  temp += (int)*ptr;
                  ++ptr;
                  }
              ++ptr;
              if (strncmp(ptr, "c ", 2) != 0) {
                 esyslog("ERROR: wrong character in xpm %s", FileName);
                 ok = false;
                 break;
                 }
              ptr += 2;
              if (*ptr == '#') {
                 int col = strtoul(++ptr, NULL, 16);
#if VDRVERSNUM < 10307
                 pal[temp] = 0xff000000 | ((col & 0xff) << 16) | (col & 0xff00) | ((col & 0xff0000) >> 16);
#else
                 pal[temp] = 0xff000000 | col;
#endif
                 }
              else {
                 pal[temp] = NoneColor;
                 }
              if (++cnt == colors) {
                 cnt = 0;
                 ++state;
                 }
              break;
         case 4:
              ++ptr;
              for (int p = 0; p < width; ++p) {
                  temp = 0;
                  for (int i = 0; i < colwidth; ++i) {
                      temp <<= 8;
                      temp += (int)*ptr;
                      ++ptr;
                      }
                  DrawPixel(p, cnt, (tColor)pal[temp]);
                  }
              if (++cnt == height) {
                 ++state;
                 bRet = true;
                 }
              break;
         default:
              break;
         }
       }
     fclose(infile);
     }
  return bRet;
}

#if VDRVERSNUM < 10307
/** Wrap the text to fit into the bitmap - taken from font.c in VDR 1.3.7 */
char *Bitmap::textWrapper(const char *Text, int *p_lines)
{
  char *text = strdup(Text);
  int lines = 1;

  char *Blank = NULL;
  char *Delim = NULL;
  int w = 0;

  stripspace(text); // strips trailing newlines

  for (char *p = text; *p; ) {
      if (*p == '\n') {
         lines++;
         w = 0;
         Blank = Delim = NULL;
         p++;
         continue;
         }
      else if (isspace(*p))
         Blank = p;
      int cw = Width(*p);
      if (w + cw > Width()) {
         if (Blank) {
            *Blank = '\n';
            p = Blank;
            continue;
            }
         else {
            // Here's the ugly part, where we don't have any whitespace to
            // punch in a newline, so we need to make room for it:
            if (Delim)
               p = Delim + 1; // let's fall back to the most recent delimiter
            char *s = MALLOC(char, strlen(text) + 2); // The additional '\n' plus the terminating '\0'
            int l = p - text;
            strncpy(s, text, l);
            s[l] = '\n';
            strcpy(s + l + 1, p);
            free(text);
            text = s;
            p = text + l;
            continue;
            }
         }
      else
         w += cw;
      if (strchr("-.,:;!?_", *p)) {
         Delim = p;
         Blank = NULL;
         }
      p++;
      }
  if (p_lines != NULL)
      *p_lines = lines;
  return text;
}
#endif
