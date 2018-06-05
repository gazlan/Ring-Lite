#include "stdafx.h"

/*
** Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com>
** Header Files
*/
#include "ring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RING_API Item* ring_item_new(int ItemType)
{
   Item* pItem;

   pItem = new Item;

   /* Set Type */
   pItem->nType = ITEMTYPE_NOTHING;
   /* Delete pointer information */
   pItem->data.pPointer = NULL;
   pItem->nObjectType = 0;
   /* Delete number information */
   pItem->data.dNumber = 0;
   pItem->data.iNumber = 0;
   pItem->NumberFlag = ITEM_NUMBERFLAG_NOTHING;
   /* Reference Count */
   ring_vm_gc_cleardata(pItem);
   ring_item_settype(pItem,ItemType);
   return pItem;
}

RING_API Item* ring_item_delete(Item* pItem)
{
   ASSERT(pItem);

   ring_vm_gc_deleteitem(pItem);
   
   return NULL;
}

RING_API void ring_item_print(Item* pItem)
{
   int   ItemType;
   
   ASSERT(pItem);
      
   ItemType = pItem->nType;

   switch (ItemType)
   {
      case ITEMTYPE_NOTHING :
         /* Work */
         break;
      case ITEMTYPE_STRING :
         /* Work */
         ring_string_print(pItem->data.pString);
         break;
      case ITEMTYPE_NUMBER :
         /* Work */
         if (pItem->NumberFlag == ITEM_NUMBERFLAG_INT)
         {
            printf("%d\n ",pItem->data.iNumber);
         }
         else
         {
            printf("%f \n",pItem->data.dNumber);
         }
         break;
      case ITEMTYPE_POINTER :
         /* Work */
         printf("%p",pItem->data.pPointer);
         break;
      case ITEMTYPE_LIST :
         /* Work */
         ring_list_print(pItem->data.pList);
         break;
   }
}

RING_API void ring_item_content_delete(Item* pItem)
{
   ASSERT(pItem != NULL);
   switch (pItem->nType)
   {
      case ITEMTYPE_STRING :
         /* Work */
         pItem->data.pString = ring_string_delete(pItem->data.pString);
         break;
      case ITEMTYPE_LIST :
         /* Work */
         pItem->data.pList = ring_list_delete(pItem->data.pList);
         break;
   }
   /* Set Type */
   pItem->nType = ITEMTYPE_NOTHING;
   /* Delete pointer information */
   pItem->data.pPointer = NULL;
   pItem->nObjectType = 0;
   /* Delete number information */
   pItem->data.dNumber = 0;
   pItem->data.iNumber = 0;
   pItem->NumberFlag = ITEM_NUMBERFLAG_NOTHING;
}

RING_API void ring_item_settype(Item* pItem,int ItemType)
{
   ASSERT(pItem != NULL);
   /* When we set the type we remove the current content at first */
   ring_item_content_delete(pItem);
   switch (ItemType)
   {
      case ITEMTYPE_NOTHING :
         pItem->nType = ITEMTYPE_NOTHING;
         break;
      case ITEMTYPE_STRING :
         pItem->nType = ITEMTYPE_STRING;
         pItem->data.pString = ring_string_new(" ");
         break;
      case ITEMTYPE_NUMBER :
         pItem->nType = ITEMTYPE_NUMBER;
         pItem->data.dNumber = 0;
         pItem->data.iNumber = 0;
         break;
      case ITEMTYPE_POINTER :
         pItem->nType = ITEMTYPE_POINTER;
         pItem->data.pPointer = NULL;
         pItem->nObjectType = 0;
         break;
      case ITEMTYPE_LIST :
         pItem->nType = ITEMTYPE_LIST;
         pItem->data.pList = ring_list_new(0);
         break;
      case ITEMTYPE_FUNCPOINTER :
         pItem->nType = ITEMTYPE_FUNCPOINTER;
         pItem->data.pFunc = NULL;
         break;
   }
}
/*
** Functions to deal with array of items
** int
*/

RING_API void ring_itemarray_setint(Item pList[],int index,int number)
{
   ring_item_settype(&pList[index],ITEMTYPE_NUMBER);
   pList[index].data.iNumber = number;
   pList[index].NumberFlag = ITEM_NUMBERFLAG_INT;
}
/* Pointers */

RING_API void ring_itemarray_setpointer(Item pList[],int index,void* pValue)
{
   ring_item_settype(&pList[index],ITEMTYPE_POINTER);
   pList[index].data.pPointer = pValue;
   pList[index].nObjectType = 0;
}
/* double */

RING_API void ring_itemarray_setdouble(Item pList[],int index,double number)
{
   ring_item_settype(&pList[index],ITEMTYPE_NUMBER);
   pList[index].data.dNumber = number;
   pList[index].NumberFlag = ITEM_NUMBERFLAG_DOUBLE;
}
#define ring_list_getint(pList,index) ( ring_list_getitem(pList,index)->data.iNumber )
#define ring_list_getpointer(pList,index) ( ring_list_getitem(pList,index)->data.pPointer )
#define ring_list_getfuncpointer(pList,index) ( ring_list_getitem(pList,index)->data.pFunc )
#define ring_list_callfuncpointer(pList,index,x) ( ring_list_getitem(pList,index)->data.pFunc(x) )
#define ring_list_getdouble(pList,index) ring_list_getitem(pList,index)->data.dNumber
#define ring_list_getstring(pList,index) ( ring_string_get(ring_item_getstring(ring_list_getitem(pList,index))) )
#define ring_list_getstringobject(pList,index) ( ring_item_getstring(ring_list_getitem(pList,index)) )
#define ring_list_getstringsize(pList,index) ( ring_string_size(ring_item_getstring(ring_list_getitem(pList,index))) )
/* String */

RING_API void ring_itemarray_setstring(Item pList[],int index,const char* str)
{
   ring_item_settype(&pList[index],ITEMTYPE_STRING);
   ring_string_set(pList[index].data.pString,str);
}

RING_API void ring_itemarray_setstring2(Item pList[],int index,const char* str,int nStrSize)
{
   ring_item_settype(&pList[index],ITEMTYPE_STRING);
   ring_string_set2(pList[index].data.pString,str,nStrSize);
}
/* Functions to deal with one item */

RING_API void ring_item_setstring(Item* pItem,const char* cStr)
{
   ring_item_settype(pItem,ITEMTYPE_STRING);
   ring_string_set(ring_item_getstring(pItem),cStr);
}

RING_API void ring_item_setstring2(Item* pItem,const char* cStr,int nStrSize)
{
   ring_item_settype(pItem,ITEMTYPE_STRING);
   ring_string_set2(ring_item_getstring(pItem),cStr,nStrSize);
}

RING_API void ring_item_setdouble(Item* pItem,double x)
{
   ring_item_settype(pItem,ITEMTYPE_NUMBER);
   pItem->data.dNumber = x;
   pItem->NumberFlag = ITEM_NUMBERFLAG_DOUBLE;
}

RING_API void ring_item_setpointer(Item* pItem,void* pValue)
{
   ring_item_settype(pItem,ITEMTYPE_POINTER);
   pItem->data.pPointer = pValue;
   pItem->nObjectType = 0;
}

RING_API void ring_item_setint(Item* pItem,int x)
{
   ring_item_settype(pItem,ITEMTYPE_NUMBER);
   pItem->data.iNumber = x;
   pItem->NumberFlag = ITEM_NUMBERFLAG_INT;
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
