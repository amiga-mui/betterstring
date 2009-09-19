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

#include <string.h>

#include <proto/exec.h>

#include "private.h"

#include "Debug.h"

static APTR pool;
#if !defined(__amigaos4__) && !defined(__MORPHOS__)
static struct SignalSemaphore poolSema;
#endif

BOOL MyCreatePool(void)
{
  BOOL success = FALSE;

  ENTER();

  #if defined(__amigaos4__)
  pool = AllocSysObjectTags(ASOT_MEMPOOL, ASOPOOL_MFlags, MEMF_SHARED,
                                          ASOPOOL_Puddle, 512,
                                          ASOPOOL_Threshold, 256,
                                          ASOPOOL_Name, "BetterString.mcc pool",
                                          ASOPOOL_Protected, TRUE,
                                          TAG_DONE);
  #elif defined(__MORPHOS__)
  pool = CreatePool(MEMF_SEM_PROTECTED, 512, 256);
  #else
  pool = CreatePool(MEMF_ANY, 512, 256);
  InitSemaphore(&poolSema);
  #endif

  if(pool != NULL)
    success = TRUE;

  RETURN(success);
  return success;
}

void MyDeletePool(void)
{
  ENTER();

  if(pool != NULL)
  {
    #if defined(__amigaos4__)
    FreeSysObject(ASOT_MEMPOOL, pool);
    #else
    DeletePool(pool);
    #endif
    pool = NULL;
  }

  LEAVE();
}

APTR MyAllocPooled(ULONG length)
{
  ULONG *mem;

  ENTER();

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ObtainSemaphore(&poolSema);
  #endif

  length = (length + sizeof(ULONG) + sizeof(ULONG) - 1) & ~(sizeof(ULONG)-1);
  if((mem = AllocPooled(pool, length)))
  {
    *mem = length;
    mem += 1;
  }

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ReleaseSemaphore(&poolSema);
  #endif

  RETURN(mem);
  return mem;
}

VOID MyFreePooled(APTR mem)
{
  ULONG *memptr, length;

  ENTER();

  memptr = &((ULONG *)mem)[-1];
  length = *memptr;

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ObtainSemaphore(&poolSema);
  #endif

  FreePooled(pool, memptr, length);

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ReleaseSemaphore(&poolSema);
  #endif

  LEAVE();
}

APTR ExpandPool(APTR mem, ULONG extra)
{
  ULONG length = ((ULONG *)mem)[-1] - sizeof(ULONG);
  ULONG sz = strlen((char *)mem) + extra;

  ENTER();

  if(length <= sz)
  {
    APTR new_mem = MyAllocPooled(sz + 20);

    CopyMem(mem, new_mem, length);
    MyFreePooled(mem);

    mem = new_mem;
  }

  RETURN(mem);
  return mem;
}
