#include "stdafx.h"

/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "ring.h"
#include <sys/types.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
/* Windows Only */
// #include <windows.h>
#else
// #include <sys/stat.h>
// #include <dirent.h>
#endif
/* Functions */

void ring_vm_file_loadfunctions(RingState* pRingState)
{
   ring_vm_funcregister("fopen",ring_vm_file_fopen);
   ring_vm_funcregister("fclose",ring_vm_file_fclose);
   ring_vm_funcregister("fflush",ring_vm_file_fflush);
   ring_vm_funcregister("freopen",ring_vm_file_freopen);
   ring_vm_funcregister("tempfile",ring_vm_file_tempfile);
   ring_vm_funcregister("tempname",ring_vm_file_tempname);
   ring_vm_funcregister("fseek",ring_vm_file_fseek);
   ring_vm_funcregister("ftell",ring_vm_file_ftell);
   ring_vm_funcregister("rewind",ring_vm_file_rewind);
   ring_vm_funcregister("fgetpos",ring_vm_file_fgetpos);
   ring_vm_funcregister("fsetpos",ring_vm_file_fsetpos);
   ring_vm_funcregister("clearerr",ring_vm_file_clearerr);
   ring_vm_funcregister("feof",ring_vm_file_feof);
   ring_vm_funcregister("ferror",ring_vm_file_ferror);
   ring_vm_funcregister("perror",ring_vm_file_perror);
   ring_vm_funcregister("rename",ring_vm_file_rename);
   ring_vm_funcregister("remove",ring_vm_file_remove);
   ring_vm_funcregister("fgetc",ring_vm_file_fgetc);
   ring_vm_funcregister("fgets",ring_vm_file_fgets);
   ring_vm_funcregister("fputc",ring_vm_file_fputc);
   ring_vm_funcregister("fputs",ring_vm_file_fputs);
   ring_vm_funcregister("ungetc",ring_vm_file_ungetc);
   ring_vm_funcregister("fread",ring_vm_file_fread);
   ring_vm_funcregister("fwrite",ring_vm_file_fwrite);
   ring_vm_funcregister("dir",ring_vm_file_dir);
   ring_vm_funcregister("read",ring_vm_file_read);
   ring_vm_funcregister("write",ring_vm_file_write);
   ring_vm_funcregister("fexists",ring_vm_file_fexists);
}

void ring_vm_file_fopen(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISSTRING(1) && RING_API_ISSTRING(2))
   {
      fp = fopen(RING_API_GETSTRING(1),RING_API_GETSTRING(2));
      RING_API_RETCPOINTER(fp,RING_VM_POINTER_FILE);
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fclose(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         RING_API_RETNUMBER(fclose(fp));
         RING_API_SETNULLPOINTER(1);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fflush(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         RING_API_RETNUMBER(fflush(fp));
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_freopen(void* pPointer)
{
   FILE* fp;
   FILE* fp2;
   if (RING_API_PARACOUNT != 3)
   {
      RING_API_ERROR(RING_API_MISS3PARA);
      return;
   }
   if (RING_API_ISSTRING(1) && RING_API_ISSTRING(2) && RING_API_ISPOINTER(3))
   {
      fp = (FILE *) RING_API_GETCPOINTER(3,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         fp2 = freopen(RING_API_GETSTRING(1),RING_API_GETSTRING(2),fp);
         RING_API_RETCPOINTER(fp2,RING_VM_POINTER_FILE);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_tempfile(void* pPointer)
{
   FILE* fp;
   fp = tmpfile();
   RING_API_RETCPOINTER(fp,RING_VM_POINTER_FILE);
}

void ring_vm_file_tempname(void* pPointer)
{
   RING_API_RETSTRING(tmpnam(NULL));
}

void ring_vm_file_fseek(void* pPointer)
{
   int   nResult;
   FILE* fp;
   if (RING_API_PARACOUNT != 3)
   {
      RING_API_ERROR(RING_API_MISS3PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISNUMBER(2) && RING_API_ISNUMBER(3))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);

      if (fp)
      {
         nResult = fseek(fp,(int) RING_API_GETNUMBER(2),(int) RING_API_GETNUMBER(3));
         RING_API_RETNUMBER(nResult);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_ftell(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         RING_API_RETNUMBER(ftell(fp));
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_rewind(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         rewind(fp);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fgetpos(void* pPointer)
{
   fpos_t*  pos;
   int      nResult;
   FILE*    fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         pos = NULL;
         nResult = fgetpos(fp,pos);
         if (nResult == 0)
         {
            RING_API_RETCPOINTER(pos,RING_VM_POINTER_FILEPOS);
         }
         else
         {
            RING_API_RETNUMBER(nResult);
         }
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fsetpos(void* pPointer)
{
   int      nResult;
   FILE*    fp;
   fpos_t*  pos;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISPOINTER(2))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      pos = (fpos_t *) RING_API_GETCPOINTER(2,RING_VM_POINTER_FILEPOS);
      if ((fp != NULL) && (pos != NULL))
      {
         nResult = fsetpos(fp,pos);
         RING_API_RETNUMBER(nResult);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_clearerr(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         clearerr(fp);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_feof(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         RING_API_RETNUMBER(feof(fp));
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_ferror(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         RING_API_RETNUMBER(ferror(fp));
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_perror(void* pPointer)
{
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      perror(RING_API_GETSTRING(1));
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_rename(void* pPointer)
{
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISSTRING(1) && RING_API_ISSTRING(2))
   {
      rename(RING_API_GETSTRING(1),RING_API_GETSTRING(2));
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_remove(void* pPointer)
{
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      remove(RING_API_GETSTRING(1));
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fgetc(void* pPointer)
{
   int   c;
   char  cStr[2];
   FILE* fp;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISPOINTER(1))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         c = fgetc(fp);
         if (c != EOF)
         {
            cStr[0] = (char) c;
            cStr[1] = 0;
            RING_API_RETSTRING(cStr);
         }
         else
         {
            RING_API_RETNUMBER(c);
         }
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fgets(void* pPointer)
{
   char* cStr;
   int   nSize;
   FILE* fp;
   char* cResult;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISNUMBER(2))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp)
      {
         nSize = (int) RING_API_GETNUMBER(2);

         if (nSize < 1)
         {
            RING_API_ERROR(RING_VM_FILE_BUFFERSIZE);
            return;
         }
         nSize++;

         cStr = new char[nSize];

         cResult = fgets(cStr,nSize,fp);
         
         if (cResult)
         {
            RING_API_RETSTRING(cStr);
         }
         else
         {
            RING_API_RETNUMBER(0);
         }

         delete[] cStr;
         cStr = NULL;
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fputc(void* pPointer)
{
   int   c;
   FILE* fp;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISSTRING(2))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         c = fputc(RING_API_GETSTRING(2)[0],fp);
         if (c != EOF)
         {
            RING_API_RETNUMBER(1);
         }
         else
         {
            RING_API_RETNUMBER(0);
         }
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

/* ******************************************************************** **
** @@ ring_vm_file_fputs()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void ring_vm_file_fputs(void* pPointer)
{
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   
   if (RING_API_ISPOINTER(1) && RING_API_ISSTRING(2))
   {
      FILE*    fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      
      if (fp)
      {
         int   c = fputs(RING_API_GETSTRING(2),fp);

         if (c != EOF)
         {
            RING_API_RETNUMBER(1);
         }
         else
         {
            RING_API_RETNUMBER(0);
         }
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_ungetc(void* pPointer)
{
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }

   if (RING_API_ISPOINTER(1) && RING_API_ISSTRING(2))
   {
      FILE*    fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);

      if (fp)
      {
         int   c = ungetc(RING_API_GETSTRING(2)[0],fp);

         if (c != EOF)
         {
            RING_API_RETNUMBER(1);
         }
         else
         {
            RING_API_RETNUMBER(0);
         }
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fread(void* pPointer)
{
   char* cStr;
   int   nSize;
   int   nResult;
   FILE* fp;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISNUMBER(2))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);

      if (fp)
      {
         nSize = (int) RING_API_GETNUMBER(2);

         if (nSize < 1)
         {
            RING_API_ERROR(RING_VM_FILE_BUFFERSIZE);
            return;
         }

         cStr = new char[nSize];

         nResult = fread(cStr,1,nSize,fp);
         
         if (!nResult)
         {
            RING_API_RETNUMBER(nResult);
         }
         else
         {
            RING_API_RETSTRING2(cStr,nResult);
         }

         delete[] cStr;
         cStr = NULL;
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fwrite(void* pPointer)
{
   int   nResult;
   FILE* fp;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS2PARA);
      return;
   }
   if (RING_API_ISPOINTER(1) && RING_API_ISSTRING(2))
   {
      fp = (FILE *) RING_API_GETCPOINTER(1,RING_VM_POINTER_FILE);
      if (fp != NULL)
      {
         nResult = fwrite(RING_API_GETSTRING(2),1,RING_API_GETSTRINGSIZE(2),fp);
         RING_API_RETNUMBER(nResult);
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_dir(void* pPointer)
{
   const char*       cStr;
   List*             pList, * pList2;
   #ifdef _WIN32
   /* Windows Only */
   WIN32_FIND_DATA   fdFile;
   HANDLE            hFind;
   String*           pString;
   #else
   DIR*              pDir;
   struct dirent*    pDirent;
   struct stat       st;
   #endif
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      cStr = RING_API_GETSTRING(1);
      pList = RING_API_NEWLIST;
      #ifdef _WIN32
      /* Windows Only */
      pString = ring_string_new(cStr);
      ring_string_add(pString,"\\*.*");
      cStr = ring_string_get(pString);
      if (!((hFind = FindFirstFile(cStr,&fdFile)) == INVALID_HANDLE_VALUE))
      {
         do
         {
            if (strcmp(fdFile.cFileName,".") != 0 && strcmp(fdFile.cFileName,"..") != 0)
            {
               pList2 = ring_list_newlist(pList);
               ring_list_addstring(pList2,fdFile.cFileName);
               if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
               {
                  ring_list_adddouble(pList2,1);
               }
               else
               {
                  ring_list_adddouble(pList2,0);
               }
            }
         }
         while (FindNextFile(hFind,&fdFile));
         RING_API_RETLIST(pList);
      }
      else
      {
         RING_API_ERROR(RING_API_BADDIRECTORY);
      }
      ring_string_delete(pString);
      #else
      pDir = opendir(cStr);
      if (pDir != NULL)
      {
         while ((pDirent = readdir(pDir)))
         {
            pList2 = ring_list_newlist(pList);
            ring_list_addstring(pList2,pDirent->d_name);
            stat(pDirent->d_name,&st);
            if (S_ISDIR(st.st_mode))
            {
               ring_list_adddouble(pList2,1);
            }
            else
            {
               ring_list_adddouble(pList2,0);
            }
         }
         closedir(pDir);
         RING_API_RETLIST(pList);
      }
      else
      {
         RING_API_ERROR(RING_API_BADDIRECTORY);
      }
      #endif
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_read(void* pPointer)
{
   FILE*    fp;
   long int nSize;
   char*    cBuffer;
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      fp = fopen(RING_API_GETSTRING(1),"rb");
      if (fp == NULL)
      {
         return;
      }
      fseek(fp,0,SEEK_END);
      nSize = ftell(fp);
      fseek(fp,0,SEEK_SET);

      cBuffer = new char[nSize];

      fread(cBuffer,1,nSize,fp);
      fclose(fp);
      RING_API_RETSTRING2(cBuffer,nSize);

      delete[] cBuffer;
      cBuffer = NULL;
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_write(void* pPointer)
{
   FILE* fp;
   if (RING_API_PARACOUNT != 2)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      if (RING_API_ISSTRING(2))
      {
         fp = fopen(RING_API_GETSTRING(1),"w+b");
         fwrite(RING_API_GETSTRING(2),RING_API_GETSTRINGSIZE(2),1,fp);
         fclose(fp);
      }
      else
      {
         RING_API_ERROR("Error in second parameter, Function requires string !");
         return;
      }
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

void ring_vm_file_fexists(void* pPointer)
{
   if (RING_API_PARACOUNT != 1)
   {
      RING_API_ERROR(RING_API_MISS1PARA);
      return;
   }
   if (RING_API_ISSTRING(1))
   {
      RING_API_RETNUMBER(ring_fexists(RING_API_GETSTRING(1)));
   }
   else
   {
      RING_API_ERROR(RING_API_BADPARATYPE);
   }
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
