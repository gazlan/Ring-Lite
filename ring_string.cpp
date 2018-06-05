#include "stdafx.h"

/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "ring.h"
/* Functions */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RING_API String* ring_string_new(const char* str)
{
   int   x;
   x = strlen(str);
   return ring_string_new2(str,x);
}

RING_API String* ring_string_new2(const char* str,int nStrSize)
{
   String*  pString;
   int      x;

   pString = new String;

   pString->cStr = new char[nStrSize + 1];

   /* Copy String */
   for (x = 0; x < nStrSize; x++)
   {
      pString->cStr[x] = str[x];
   }
   pString->cStr[nStrSize] = '\0';
   pString->nSize = nStrSize;
   return pString;
}

RING_API String* ring_string_delete(String* pString)
{
   ASSERT(pString);

   delete[] pString->cStr;
   pString->cStr = NULL;

   delete pString;
   pString = NULL;

   return NULL;
}

RING_API int ring_string_size(String* pString)
{
   ASSERT(pString != NULL);
   return pString->nSize;
}

RING_API void ring_string_set(String* pString,const char* str)
{
   int   x;
   ASSERT(pString != NULL);
   x = strlen(str);
   ring_string_set2(pString,str,x);
}

RING_API void ring_string_set2(String* pString,const char* str,int nStrSize)
{
   ASSERT(pString);
   ASSERT(pString->cStr);

   delete[] pString->cStr;
   pString->cStr = NULL;
   
   pString->cStr = new char[nStrSize + 1];

   /* Copy String */
   for (int x = 0; x < nStrSize; x++)
   {
      pString->cStr[x] = str[x];
   }
   pString->cStr[nStrSize] = '\0';
   pString->nSize = nStrSize;
}

RING_API void ring_string_add(String* pString,const char* str)
{
   int   x;
   x = strlen(str);
   ring_string_add2(pString,str,x);
}

RING_API void ring_string_add2(String* pString,const char* str,int nStrSize)
{
   int   x;
   int   x2;
   char* cStr;
   ASSERT(pString != NULL);
   x2 = nStrSize + ring_string_size(pString);
   cStr = pString->cStr;

   pString->cStr = new char[x2 + 1];

   /* Copy String */
   for (x = 0; x < ring_string_size(pString); x++)
   {
      pString->cStr[x] = cStr[x];
   }
   for (x = 0; x < nStrSize; x++)
   {
      pString->cStr[x + ring_string_size(pString)] = str[x];
   }
   pString->cStr[x2] = 0;
   pString->nSize = x2;

   delete[] cStr;
   cStr = NULL;
}

RING_API void ring_string_print(String* pString)
{
   ASSERT(pString != NULL);
   printf("%s \n",pString->cStr);
}

RING_API void ring_string_setfromint(String* pString,int x)
{
   char  cStr[20];
   ASSERT(pString != NULL);
   sprintf(cStr,"%d",x);
   ring_string_set(pString,cStr);
}

RING_API char* ring_string_lower(char* cStr)
{
   unsigned int x;
   for (x = 0; x < strlen(cStr); x++)
   {
      if (isalpha(cStr[x]))
      {
         cStr[x] = (char)tolower(cStr[x]);
      }
   }
   return cStr;
}

RING_API char* ring_string_lower2(char* cStr,int nStrSize)
{
   int   x;
   for (x = 0; x < nStrSize; x++)
   {
      if (isalpha(cStr[x]))
      {
         cStr[x] = (char)tolower(cStr[x]);
      }
   }
   return cStr;
}

RING_API char* ring_string_upper(char* cStr)
{
   unsigned int x;
   for (x = 0; x < strlen(cStr); x++)
   {
      if (isalpha(cStr[x]))
      {
         cStr[x] = (char)toupper(cStr[x]);
      }
   }
   return cStr;
}

RING_API char* ring_string_upper2(char* cStr,int nStrSize)
{
   int   x;
   for (x = 0; x < nStrSize; x++)
   {
      if (isalpha(cStr[x]))
      {
         cStr[x] = (char)toupper(cStr[x]);
      }
   }
   return cStr;
}

RING_API char* ring_string_find(char* cStr1,char* cStr2)
{
   return ring_string_find2(cStr1,strlen(cStr1),cStr2,strlen(cStr2));
}

RING_API char* ring_string_find2(char* cStr1,int nStrSize1,char* cStr2,int nStrSize2)
{
   int   nPos, x;
   nPos = 0;
   if ((nStrSize1 - nStrSize2) < 0)
   {
      return NULL;
   }
   while (nPos <= (nStrSize1 - nStrSize2))
   {
      x = 0;
      while ((x < nStrSize2) && (cStr1[nPos + x] == cStr2[x]))
      {
         x++;
      }
      if (x == nStrSize2)
      {
         return cStr1 + nPos;
      }
      nPos++;
   }
   return NULL;
}

void ring_string_test()
{
   #define nMaxValue 10
   String*  mystr[nMaxValue];
   int      x;
   String*  pString;
   for (x = 0; x < nMaxValue; x++)
   {
      mystr[x] = ring_string_new("Wow Really i like the c language so much");
      ring_string_print(mystr[x]);
   }
   for (x = 0; x < nMaxValue; x++)
   {
      mystr[x] = ring_string_delete(mystr[x]);
   }
   /* Test String Add */
   pString = ring_string_new("Hello ");
   ring_string_add(pString,"World");
   printf("\nTest String Add , Output = %s\n",ring_string_get(pString));
   ring_string_add(pString," Welcome to the C programming language");
   printf("\nTest String Add , Output = %s\n",ring_string_get(pString));
   ring_string_delete(pString);
   /* Test String to Lower */
   pString = ring_string_new("Welcome to my StrinG");
   printf("Test string to lower \n");
   printf("%s\n",ring_string_tolower(pString));
   ring_string_delete(pString);
   getchar();
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
