/* ******************************************************************** **
** @@ Ring hash table
** @  Copyrt : Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com>
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  : Include file for standard system include files, or project specific
** @  Notes  : include files that are used frequently, but are changed infrequently
** ******************************************************************** */

#ifndef _RING_HASHTABLE_HPP_
#define _RING_HASHTABLE_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

// Data
typedef struct HashItem
{
   char* cKey;
   char  nItemType;
   union HashValue
   {
      int      nIndex;
      void*    pValue;
   } HashValue;
   struct HashItem*  pNext;
} HashItem;

typedef struct HashTable
{
   HashItem**     pArray;
   int            nItems;
   int            nLinkedLists;
   int            nRebuildSize;
} HashTable;

// Functions
HashTable*     ring_hashtable_new();

DWORD       ring_hashtable_hashkey(HashTable* pHashTable,const char* cKey);
HashItem*   ring_hashtable_newitem(HashTable* pHashTable,const char* cKey);
void        ring_hashtable_newnumber(HashTable* pHashTable,const char* cKey,int x);
void        ring_hashtable_newpointer(HashTable* pHashTable,const char* cKey,void* x);
HashItem*   ring_hashtable_finditem(HashTable* pHashTable,const char* cKey);
int         ring_hashtable_findnumber(HashTable* pHashTable,const char* cKey);
void*       ring_hashtable_findpointer(HashTable* pHashTable,const char* cKey);
void        ring_hashtable_deleteitem(HashTable* pHashTable,const char* cKey);
HashTable*  ring_hashtable_delete(HashTable* pHashTable);
void        ring_hashtable_print(HashTable* pHashTable);
void        ring_hashtable_test();
void        ring_hashtable_rebuild(HashTable* pHashTable);

// Macro
#define RING_HASHITEMTYPE_NOTYPE       (0)
#define RING_HASHITEMTYPE_NUMBER       (1)
#define RING_HASHITEMTYPE_POINTER      (2)

/* ******************************************************************** **
** @@ internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@ external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ Global Function Prototypes
** ******************************************************************** */

#endif

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
