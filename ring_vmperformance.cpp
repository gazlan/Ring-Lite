#include "stdafx.h"

/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "ring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* For Better Performance */

void ring_vm_pushp(VM* pVM)
{
   RING_VM_STACK_PUSHP;
   RING_VM_STACK_OBJTYPE = RING_OBJTYPE_VARIABLE;
}

void ring_vm_pushplocal(VM* pVM)
{
   /* Check Scope Life Time */
   if (RING_VM_IR_READIVALUE(4) != pVM->nActiveScopeID)
   {
      RING_VM_IR_OPCODE = ICO_LOADADDRESS;
      #if RING_SHOWICFINAL
      RING_VM_IR_PARACOUNT = RING_VM_IR_PARACOUNT - 2;
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      #endif
      pVM->nPC--;
      return;
   }
   RING_VM_STACK_PUSHPVALUE(RING_VM_IR_READPVALUE(3));
   RING_VM_STACK_OBJTYPE = RING_OBJTYPE_VARIABLE;
}

void ring_vm_incp(VM* pVM)
{
   List* pVar;
   pVar = (List *) RING_VM_IR_READP;
   ring_list_setdouble(pVar,RING_VAR_VALUE,ring_list_getdouble(pVar,RING_VAR_VALUE) + 1);
}

void ring_vm_pushpv(VM* pVM)
{
   List* pVar;
   pVar = (List *) RING_VM_IR_READP;
   pVM->nSP++;
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      RING_VM_STACK_PUSHCVAR;
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      RING_VM_STACK_PUSHNVAR;
   }
}

void ring_vm_incjump(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   if (ring_vm_findvar(pVM,RING_VM_IR_READC) == 0)
   {
      ring_vm_newvar(pVM,RING_VM_IR_READC);
   }
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Change Instruction for Performance */
   if (pVM->nVarScope == RING_VARSCOPE_GLOBAL)
   {
      /* Replace ICO_INCJUMP with IncPJUMP for better performance */
      if (nNum1 == 1.0)
      {
         RING_VM_IR_OPCODE = ICO_INCPJUMPSTEP1;
      }
      else
      {
         RING_VM_IR_OPCODE = ICO_INCPJUMP;
      }
      ring_item_setpointer(RING_VM_IR_ITEM(1),RING_VM_STACK_READP);
   }
   else if (pVM->nVarScope == RING_VARSCOPE_LOCAL)
   {
      /* Replace ICO_INCJUMP with IncLPJUMP for better performance */
      RING_VM_IR_OPCODE = ICO_INCLPJUMP;
      ring_item_setpointer(RING_VM_IR_ITEM(3),RING_VM_STACK_READP);
      ring_item_setint(RING_VM_IR_ITEM(4),ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
   }
   pVar = (List *) RING_VM_STACK_READP;
   RING_VM_STACK_POP;
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
      ring_list_setdouble(pVar,RING_VAR_VALUE,nNum2);
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   ring_list_setdouble(pVar,RING_VAR_VALUE,nNum2 + nNum1);
   /* Jump */
   pVM->nPC = RING_VM_IR_READIVALUE(2);
}

void ring_vm_incpjump(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   pVar = (List *) RING_VM_IR_READP;
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   ring_list_setdouble(pVar,RING_VAR_VALUE,nNum2 + nNum1);
   /* Jump */
   pVM->nPC = RING_VM_IR_READIVALUE(2);
}

void ring_vm_inclpjump(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   /* Check Scope Life Time */
   if (RING_VM_IR_READIVALUE(4) != pVM->nActiveScopeID)
   {
      RING_VM_IR_OPCODE = ICO_INCJUMP;
      #if RING_SHOWICFINAL
      RING_VM_IR_PARACOUNT = RING_VM_IR_PARACOUNT - 2;
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      #endif
      pVM->nPC--;
      return;
   }
   pVar = (List *) RING_VM_IR_READPVALUE(3);
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   ring_list_setdouble(pVar,RING_VAR_VALUE,nNum2 + nNum1);
   /* Jump */
   pVM->nPC = RING_VM_IR_READIVALUE(2);
}

void ring_vm_jumpvarlenum(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   if (ring_vm_findvar(pVM,RING_VM_IR_READC) == 0)
   {
      ring_vm_newvar(pVM,RING_VM_IR_READC);
   }
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Change Instruction for Performance */
   if (pVM->nVarScope == RING_VARSCOPE_GLOBAL)
   {
      /* Replace JumpVarLENum with JumpVarPLENum for better performance */
      if (nNum1 == 1.0)
      {
         RING_VM_IR_OPCODE = ICO_JUMPVARPLENUMSTEP1;
      }
      else
      {
         RING_VM_IR_OPCODE = ICO_JUMPVARPLENUM;
      }
      ring_item_setpointer(RING_VM_IR_ITEM(1),RING_VM_STACK_READP);
   }
   else if (pVM->nVarScope == RING_VARSCOPE_LOCAL)
   {
      /* Replace JumpVarLENum with JumpVarLPLENum for better performance */
      RING_VM_IR_OPCODE = ICO_JUMPVARLPLENUM;
      ring_item_setpointer(RING_VM_IR_ITEM(4),RING_VM_STACK_READP);
      ring_item_setint(RING_VM_IR_ITEM(5),ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
      #if RING_SHOWICFINAL
      RING_VM_IR_PARACOUNT = RING_VM_IR_PARACOUNT + 2;
      ring_list_addpointer(RING_VM_IR_LIST,RING_VM_STACK_READP);
      ring_list_addint(RING_VM_IR_LIST,ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
      #endif
   }
   pVar = (List *) RING_VM_STACK_READP;
   RING_VM_STACK_POP;
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
      ring_list_setdouble(pVar,RING_VAR_VALUE,nNum2);
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   if (nNum1 < 0)
   {
      if (!(nNum2 >= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
   else
   {
      if (!(nNum2 <= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
}

void ring_vm_jumpvarplenum(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   pVar = (List *) RING_VM_IR_READP;
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   if (nNum1 < 0)
   {
      if (!(nNum2 >= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
   else
   {
      if (!(nNum2 <= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
}

void ring_vm_jumpvarlplenum(VM* pVM)
{
   List*    pVar;
   double   nNum1, nNum2;
   /* Check Scope Life Time */
   if (RING_VM_IR_READIVALUE(5) != pVM->nActiveScopeID)
   {
      RING_VM_IR_OPCODE = ICO_JUMPVARLENUM;
      #if RING_SHOWICFINAL
      RING_VM_IR_PARACOUNT = RING_VM_IR_PARACOUNT - 2;
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      ring_list_deleteitem(RING_VM_IR_LIST,ring_list_getsize(RING_VM_IR_LIST));
      #endif
      pVM->nPC--;
      return;
   }
   pVar = (List *) RING_VM_IR_READPVALUE(4);
   nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
   /* Check Data */
   if (ring_list_isstring(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,RING_VAR_VALUE));
   }
   else if (ring_list_isnumber(pVar,RING_VAR_VALUE))
   {
      nNum2 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   }
   else
   {
      ring_vm_error(pVM,RING_VM_ERROR_FORLOOPDATATYPE);
      return;
   }
   if (nNum1 < 0)
   {
      if (!(nNum2 >= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
   else
   {
      if (!(nNum2 <= RING_VM_IR_READDVALUE(2)))
      {
         /* Jump */
         pVM->nPC = RING_VM_IR_READIVALUE(3);
      }
   }
}

void ring_vm_loadfuncp(VM* pVM)
{
   List* pList;
   pVM->nFuncExecute++;
   pVM->nFuncExecute2++;
   pList = ring_list_newlist(pVM->pFuncCallList);
   ring_list_addint(pList,RING_VM_IR_READIVALUE(3));
   ring_list_addstring(pList,RING_VM_IR_READC);
   ring_list_addint(pList,RING_VM_IR_READIVALUE(2));
   ring_list_addint(pList,pVM->nSP);
   ring_list_newlist(pList);
   ring_list_addpointer(pList,pVM->cFileName);
   pVM->cFileName = (char *) RING_VM_IR_READPVALUE(4);
   ring_list_addint(pList,RING_VM_IR_READIVALUE(5));
   ring_vm_saveloadaddressscope(pVM);
}
/* For Loop Optimization When Step = 1 */

void ring_vm_incpjumpstep1(VM* pVM)
{
   List*    pVar;
   double   nNum1;
   pVar = (List *) RING_VM_IR_READP;
   /* We Don't Check Data Type */
   nNum1 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   ring_list_setdouble(pVar,RING_VAR_VALUE,nNum1 + 1);
   /* Jump */
   pVM->nPC = RING_VM_IR_READIVALUE(2);
}

void ring_vm_jumpvarplenumstep1(VM* pVM)
{
   List*    pVar;
   double   nNum1;
   pVar = (List *) RING_VM_IR_READP;
   /* We don't Check Data type */
   nNum1 = ring_list_getdouble(pVar,RING_VAR_VALUE);
   if (nNum1 > RING_VM_IR_READDVALUE(2))
   {
      /* Jump */
      pVM->nPC = RING_VM_IR_READIVALUE(3);
   }
}

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
