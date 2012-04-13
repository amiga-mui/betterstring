/***************************************************************************

 BetterString.mcc - A better String gadget MUI Custom Class
 Copyright (C) 1997-2000 Allan Odgaard
 Copyright (C) 2005-2009 by BetterString.mcc Open Source Team

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 BetterString class Support Site:  http://www.sf.net/projects/bstring-mcc/

 $Id$

***************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <clib/alib_protos.h>
#include <graphics/gfxmacros.h>
#include <proto/intuition.h>
#include <proto/graphics.h>
#include <proto/muimaster.h>

#include "private.h"

VOID PrintString(struct IClass *cl, Object *obj)
{
  struct InstData *data     = (struct InstData *)INST_DATA(cl, obj);
  struct RastPort *oldrport = _rp(obj);
  struct RastPort *rport    = &data->rport;
  struct TextFont *font     = data->Font ? data->Font : _font(obj);
  struct TextExtent tExtend;
  STRPTR contents;
  WORD width, height;
  WORD crsr_x=0, crsr_width=0, crsr_color=0;
  WORD length, offset = 0, StrLength;
  STRPTR text;
  BOOL   BlockEnabled = (isFlagSet(data->Flags, FLG_BlockEnabled) && data->BlockStart != data->BlockStop);
  UWORD  Blk_Start=0, Blk_Width=0;
  STRPTR fake_contents = NULL;
  BOOL showInactiveContents = FALSE;

  width = _mwidth(obj);
  height = font->tf_YSize;

  contents = data->Contents;
  StrLength = strlen(contents);

  if(isFlagSet(data->Flags, FLG_Secret) && (fake_contents = (STRPTR)SharedPoolAlloc(StrLength+1)))
  {
    // fill the secret copy of the string with '*' and terminate it with NUL
    if(StrLength > 0)
      memset(fake_contents, '*', StrLength);
    fake_contents[StrLength] = '\0';
    contents = fake_contents;
  }

  if(StrLength == 0 && isFlagClear(data->Flags, FLG_Active) && data->InactiveContents != NULL)
  {
    contents = data->InactiveContents;
    StrLength = strlen(contents);
    showInactiveContents = TRUE;
  }

  SetFont(rport, font);
  if(isFlagSet(data->Flags, FLG_Active) && BlockEnabled == FALSE)
  {
    char *c;

    // use the character at the current position or 'n' as a standard
    // character to calculate the current cursor width
    if(contents[data->BufferPos] != '\0')
      c = &contents[data->BufferPos];
    else
      c = (char *)"n";

    crsr_width = TextLength(rport, c, 1);
  }
  else
    crsr_width = 0;

  if(data->DisplayPos > data->BufferPos)
    data->DisplayPos = data->BufferPos;

  if(StrLength)
  {
    UWORD backdistance = TextFit(rport, contents+StrLength-1, StrLength, &tExtend, NULL, -1, width/*-crsr_width*/, font->tf_YSize);

    if(backdistance > StrLength-data->DisplayPos)
      data->DisplayPos = StrLength-backdistance;
  }

  if(data->BufferPos)
  {
    UWORD distance = TextFit(rport, contents+data->BufferPos-1, data->BufferPos, &tExtend, NULL, -1, width-crsr_width, font->tf_YSize);

    if(distance < data->BufferPos-data->DisplayPos)
      data->DisplayPos = data->BufferPos - distance;
  }

  text = contents+data->DisplayPos;
  StrLength -= data->DisplayPos;

  if(BlockEnabled)
  {
    Blk_Start = (data->BlockStart < data->BlockStop) ? data->BlockStart : data->BlockStop;
    Blk_Width = abs(data->BlockStop-data->BlockStart);

    if(Blk_Start < data->DisplayPos)
    {
      Blk_Width -= data->DisplayPos-Blk_Start;
      Blk_Start  = data->DisplayPos;
    }
    crsr_x = TextLength(rport, text, Blk_Start-data->DisplayPos);
    crsr_width = TextLength(rport, contents+Blk_Start, Blk_Width);
    crsr_color = MUIPEN(data->MarkedColor);
  }
  else
  {
    // display the cursor only if input is allowed
    if(isFlagSet(data->Flags, FLG_Active) && isFlagClear(data->Flags, FLG_NoInput))
    {
      crsr_x = TextLength(rport, text, data->BufferPos-data->DisplayPos);
      crsr_color = MUIPEN(data->CursorColor);
    }
  }

  _rp(obj) = rport;
  DoMethod(obj, MUIM_DrawBackground, 0, 0, _mwidth(obj), _mheight(obj), 0, 0, 0L);
  _rp(obj) = oldrport;

  length = TextFit(rport, text, StrLength, &tExtend, NULL, 1, width, font->tf_YSize);
  if(data->Alignment != MUIV_String_Format_Left)
  {
    UWORD textlength = TextLength(rport, text, length);

    if(crsr_width && !BlockEnabled && data->BufferPos == data->DisplayPos+StrLength)
    {
      length = TextFit(rport, text, StrLength, &tExtend, NULL, 1, width-crsr_width, font->tf_YSize);
      textlength += crsr_width;
    }

    switch(data->Alignment)
    {
      case MUIV_String_Format_Center:
        offset = (width - textlength)/2;
        break;
      case MUIV_String_Format_Right:
        offset = (width - textlength);
        break;
    }
  }

  if(crsr_width && crsr_x < width)
  {
    SetAPen(rport, crsr_color);
    if(crsr_x+crsr_width > width)
    {
      crsr_width = width-crsr_x;
    }
    RectFill(rport, offset+crsr_x, 0, offset+crsr_x+crsr_width-1, font->tf_YSize-1);
  }

  if(length)
  {
    UWORD newlength;
    LONG textcolor = isFlagSet(data->Flags, FLG_Active) ? data->ActiveText : data->InactiveText;

    Move(rport, offset, font->tf_Baseline);

    if(BlockEnabled && textcolor != (LONG)data->MarkedTextColor)
    {
      newlength = Blk_Start-data->DisplayPos;
      SetAPen(rport, MUIPEN(textcolor));
      Text(rport, text, newlength);
      text += newlength;

      newlength = (((Blk_Start-data->DisplayPos) + Blk_Width) > length) ? length - (Blk_Start-data->DisplayPos) : Blk_Width;
      SetAPen(rport, MUIPEN(data->MarkedTextColor));
      Text(rport, text, newlength);
      text += newlength;

      length -= newlength + (Blk_Start-data->DisplayPos);
    }

    // switch to italic style if the inactive text is to be displayed
    if(showInactiveContents == TRUE)
    {
      SetSoftStyle(rport, FSF_ITALIC, AskSoftStyle(rport));
      textcolor = _pens(obj)[MPEN_SHADOW];
    }

    SetAPen(rport, MUIPEN(textcolor));
    Text(rport, text, length);

    // switch back to normal style
    if(showInactiveContents == TRUE)
      SetSoftStyle(rport, FS_NORMAL, AskSoftStyle(rport));
  }

  if(fake_contents != NULL)
    SharedPoolFree(fake_contents);

  BltBitMapRastPort(data->rport.BitMap, 0, 0, _rp(obj), _mleft(obj), _mtop(obj), width, height, 0xc0);

  #if defined(__amigaos3__) || defined(__amigaos4__)
  if(MUIMasterBase->lib_Version > 20 || (MUIMasterBase->lib_Version == 20 && MUIMasterBase->lib_Revision >= 5640))
  {
    // MUI 4.0 for AmigaOS4 does the disabled pattern drawing itself,
    // no need to do this on our own
    return;
  }
  #endif

  if(isFlagSet(data->Flags, FLG_Ghosted))
  {
    UWORD GhostPattern[] = {0x4444, 0x1111};
    struct RastPort *rport = muiRenderInfo(obj)->mri_RastPort;

    SetAfPt(rport, GhostPattern, 1);
    SetAPen(rport, _pens(obj)[MPEN_SHADOW]);
    RectFill(rport, _left(obj), _top(obj), _right(obj), _bottom(obj));
    SetAfPt(rport, 0, 0);
  }
}
