/***************************************************************************

 BetterString.mcc - A better String gadget MUI Custom Class
 Copyright (C) 1997-2000 Allan Odgaard
 Copyright (C) 2005 by BetterString.mcc Open Source Team

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

#include <string.h>

#include <devices/inputevent.h>
#include <libraries/mui.h>
#include <proto/intuition.h>
#include <proto/keymap.h>

#include <newmouse.h>

#include "private.h"

static ULONG ConvertKey (struct IntuiMessage *imsg)
{
	struct InputEvent event;
	unsigned char code = '\0';

	event.ie_NextEvent		= NULL;
	event.ie_Class 			  = IECLASS_RAWKEY;
	event.ie_SubClass 		= 0;
	event.ie_Code  			  = imsg->Code;
	event.ie_Qualifier		= 0; /* imsg->Qualifier; */
	event.ie_EventAddress	= 0; /* (APTR *) *((ULONG *)imsg->IAddress); */

	MapRawKey(&event, (STRPTR)&code, 1, NULL);

	return code;
}

#define BETWEEN(a, min, max) (a >= min && a <= max)

/* wheel mouse support */
#undef	IECODE_KEY_CODE_LAST
#define	IECODE_KEY_CODE_LAST 0x7e

ULONG HandleInput(struct IClass *cl, Object *obj, struct MUIP_HandleEvent *msg)
{
	struct InstData *data = (struct InstData *)INST_DATA(cl, obj);
	BOOL nokey = FALSE, backspace = FALSE, qual_only;
	ULONG result;

	qual_only = BETWEEN(msg->imsg->Code, 0x60, 0x67); // betwenn LSHIFT/RCOMMAND

	if(qual_only || (data->Flags & (FLG_Snoop|FLG_Active) &&
		 msg->imsg->Class == IDCMP_RAWKEY &&
		 BETWEEN(msg->imsg->Code, IECODE_KEY_CODE_FIRST, IECODE_KEY_CODE_LAST) &&
		 msg->muikey != MUIKEY_GADGET_NEXT &&
		 msg->muikey != MUIKEY_GADGET_PREV))
	{
		static CONST CONST_STRPTR qualifier_name[] =
		{
			"lshift", "rshift", "capslock", "control", "lalt",
			"ralt", "lcommand", "rcommand", "numericpad", "repeat",
			NULL
		};

		ULONG qualifier = msg->imsg->Qualifier;
		char buffer[256];
		ULONG i;

		buffer[0] = 0;

		for(i=0; qualifier_name[i]; i++)
		{
			if(qualifier & (1 << i))
			{
				strcat(buffer, qualifier_name[i]);
				strcat(buffer, " ");
			}
		}

		if(qual_only)
		{
			if(*buffer)
				buffer[strlen(buffer)-1] = '\0';
		}
		else
		{
			UWORD code = msg->imsg->Code;

			if(code >= RAWKEY_F11 && code <= RAWKEY_F10)
			{
				static CONST CONST_STRPTR key_name[] =
				{
					"f11",
					"up", "down", "right", "left",
					"f1", "f2", "f3", "f4", "f5",
					"f6", "f7", "f8", "f9", "f10"
				};

				strcat(buffer, key_name[code-RAWKEY_CRSRUP]);
			}
			else switch(code)
			{
				#if defined(__amigaos4__)
				case RAWKEY_MENU:     strcat(buffer, "menu"); break;
				#elif defined(__MORPHOS__)
				case RAWKEY_SCRLOCK:  strcat(buffer, "scrlock"); break;
				#endif

				case RAWKEY_NUMLOCK:  strcat(buffer, "numlock"); break;
				case RAWKEY_INSERT:   strcat(buffer, "insert"); break;
				case RAWKEY_PAGEUP:   strcat(buffer, "page_up"); break;
				case RAWKEY_PAGEDOWN: strcat(buffer, "page_down"); break;
				case RAWKEY_PRINTSCR: strcat(buffer, "prtscr"); break;
				case RAWKEY_BREAK:    strcat(buffer, "pause"); break;
				case RAWKEY_F12:      strcat(buffer, "f12"); break;
				case RAWKEY_HOME:     strcat(buffer, "home"); break;
				case RAWKEY_END:      strcat(buffer, "end"); break;

				case RAWKEY_AUD_STOP:       strcat(buffer, "media_stop"); break;
				case RAWKEY_AUD_PLAY_PAUSE: strcat(buffer, "media_play"); break;
				case RAWKEY_AUD_PREV_TRACK: strcat(buffer, "media_prev"); break;
				case RAWKEY_AUD_NEXT_TRACK: strcat(buffer, "media_next"); break;
				case RAWKEY_AUD_SHUFFLE:    strcat(buffer, "media_rewind"); break;
				case RAWKEY_AUD_REPEAT:     strcat(buffer, "media_forward"); break;

				case RAWKEY_HELP:
					strcat(buffer, "help");
				break;

				case NM_WHEEL_UP:
					strcat(buffer, "wheel_up");
				break;

				case NM_WHEEL_DOWN:
					strcat(buffer, "wheel_down");
				break;

				case NM_WHEEL_LEFT:
					strcat(buffer, "wheel_left");
				break;

				case NM_WHEEL_RIGHT:
					strcat(buffer, "wheel_right");
				break;

				case NM_BUTTON_FOURTH:
					strcat(buffer, "wheel_button");
				break;

				default:
				{
					char *append = NULL;
					unsigned char key[2];

					key[0] = ConvertKey(msg->imsg);
					key[1] = 0;

					switch(key[0])
					{
						case 0:
							nokey = TRUE;
						break;

						case 8:
							backspace = TRUE;
							append = "backspace";
						break;

						case 9:
							append = "tab";
						break;

						case 13:
							append = ((qualifier & IEQUALIFIER_NUMERICPAD) ? "enter" : "return");
						break;

						case 27:
							append = "esc";
						break;

						case 32:
							append = "space";
						break;

						case 0x7f:
							append = "del";
						break;

						default:
							append = (char *)key;
						break;
					}

					if(append)
						strcat(buffer, append);
				}
				break;
			}
		}

		if(!nokey)
		{
			if(backspace)
			{
				if(data->Flags & FLG_Backspace)
				{
					*buffer = '\0';
					data->Flags &= ~FLG_Backspace;
				}
				else
				{
					data->Flags |= FLG_Backspace;
				}
			}
			else
			{
				data->Flags &= ~FLG_Backspace;
			}
			SetAttrs(obj, MUIA_String_Contents, buffer, TAG_DONE);
		}
		result = MUI_EventHandlerRC_Eat;
	}
	else
	  result = 0;

	return result;
}
