#include "stdafx.h"

/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "ring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Items* ring_items_new()
{
   Items*   pItems;

   pItems = new Items;

   pItems->pValue = ring_item_new(ITEMTYPE_NOTHING);
   pItems->pNext = NULL;
   pItems->pPrev = NULL;
   return pItems;
}

Items* ring_items_delete(Items* pItems)
{
   ASSERT(pItems);

   pItems->pValue = ring_item_delete(pItems->pValue);

   delete[] pItems;
   pItems = NULL;

   return pItems;
}

void ring_items_print(Items* pItems)
{
   ASSERT(pItems != NULL);
   ring_item_print(pItems->pValue);
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
