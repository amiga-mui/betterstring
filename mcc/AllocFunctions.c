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

static APTR sharedPool;
#if !defined(__amigaos4__) && !defined(__MORPHOS__)
static struct SignalSemaphore sharedPoolSema;
#endif

BOOL CreateSharedPool(void)
{
  BOOL success = FALSE;

  ENTER();

  #if defined(__amigaos4__)
  sharedPool = AllocSysObjectTags(ASOT_MEMPOOL, ASOPOOL_MFlags, MEMF_SHARED,
                                                ASOPOOL_Puddle, 512,
                                                ASOPOOL_Threshold, 256,
                                                ASOPOOL_Name, "BetterString.mcc shared pool",
                                                ASOPOOL_Protected, TRUE,
                                                ASOPOOL_LockMem, FALSE,
                                                TAG_DONE);
  #elif defined(__MORPHOS__)
  sharedPool = CreatePool(MEMF_SEM_PROTECTED, 512, 256);
  #else
  sharedPool = CreatePool(MEMF_ANY, 512, 256);
  memset(&sharedPoolSema, 0, sizeof(sharedPoolSema));
  InitSemaphore(&sharedPoolSema);
  #endif

  if(sharedPool != NULL)
    success = TRUE;

  RETURN(success);
  return success;
}

void DeleteSharedPool(void)
{
  ENTER();

  if(sharedPool != NULL)
  {
    #if defined(__amigaos4__)
    FreeSysObject(ASOT_MEMPOOL, sharedPool);
    #else
    DeletePool(sharedPool);
    #endif
    sharedPool = NULL;
  }

  LEAVE();
}

#if defined(__amigaos3__)
static APTR AllocVecPooled(APTR poolHeader, ULONG memSize)
{
  ULONG *memory;

  ENTER();

  // add the number of bytes used to store the size information
  memSize += sizeof(ULONG);

  // allocate memory from the pool
  if((memory = (ULONG *)AllocPooled(poolHeader, memSize)) != NULL)
  {
    // and finally store the size of the memory block, including the size itself
    *memory++ = memSize;
  }

  RETURN(memory);
  return memory;
}
#endif

APTR SharedPoolAlloc(ULONG length)
{
  ULONG *mem;

  ENTER();

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ObtainSemaphore(&sharedPoolSema);
  #endif

  mem = AllocVecPooled(sharedPool, length);

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ReleaseSemaphore(&sharedPoolSema);
  #endif

  RETURN(mem);
  return mem;
}

#if defined(__amigaos3__)
static void FreeVecPooled(APTR poolHeader, APTR memory)
{
  ULONG *mem = (ULONG *)memory;
  ULONG memSize;

  ENTER();

  // skip back over the stored size information
  memSize = *(--mem);

  // an return the memory block to the pool
  FreePooled(poolHeader, mem, memSize);

  LEAVE();
}
#endif

void SharedPoolFree(APTR mem)
{
  ENTER();

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ObtainSemaphore(&sharedPoolSema);
  #endif

  FreeVecPooled(sharedPool, mem);

  #if !defined(__amigaos4__) && !defined(__MORPHOS__)
  ReleaseSemaphore(&sharedPoolSema);
  #endif

  LEAVE();
}

BOOL ExpandContents(struct InstData *data, ULONG extra)
{
  BOOL success = FALSE;
  ULONG sz = strlen(data->Contents) + 1 + extra;

  ENTER();

  // check if we have to expand our contents string
  if(data->ContentsAllocSize < sz)
  {
    STRPTR newContents;

    // add another 32 bytes for less expansions in the future
    sz += 32;
    if((newContents = SharedPoolAlloc(sz)) != NULL)
    {
      strlcpy(newContents, data->Contents, sz);
      SharedPoolFree(data->Contents);

      data->Contents = newContents;
      data->ContentsAllocSize = sz;

      success = TRUE;
    }
  }
  else
  {
    // no expansion necessary, instant success
    success = TRUE;
  }

  RETURN(success);
  return success;
}
