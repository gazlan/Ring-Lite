# Microsoft Developer Studio Project File - Name="Ring" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Ring - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ring.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ring.mak" CFG="Ring - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ring - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Ring - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ring - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Ring - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Ring - Win32 Release"
# Name "Ring - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ring_api.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_codegen.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_expr.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_ext.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_hashlib.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_hashtable.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_item.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_items.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_list.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_state.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_stmt.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_string.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vm.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmcui.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmdll.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmduprange.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmexit.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmexpr.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmfile.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmfuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmgc.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmjump.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmlistfuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmlists.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmmath.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmoop.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmos.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmperformance.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmrefmeta.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmstackvars.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmstate.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmstrindex.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmtrycatch.cpp
# End Source File
# Begin Source File

SOURCE=.\ring_vmvars.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ring.h
# End Source File
# Begin Source File

SOURCE=.\ring_api.h
# End Source File
# Begin Source File

SOURCE=.\ring_codegen.h
# End Source File
# Begin Source File

SOURCE=.\ring_ext.h
# End Source File
# Begin Source File

SOURCE=.\ring_hashlib.h
# End Source File
# Begin Source File

SOURCE=.\ring_hashtable.h
# End Source File
# Begin Source File

SOURCE=.\ring_item.h
# End Source File
# Begin Source File

SOURCE=.\ring_items.h
# End Source File
# Begin Source File

SOURCE=.\ring_list.h
# End Source File
# Begin Source File

SOURCE=.\ring_parser.h
# End Source File
# Begin Source File

SOURCE=.\ring_scanner.h
# End Source File
# Begin Source File

SOURCE=.\ring_state.h
# End Source File
# Begin Source File

SOURCE=.\ring_string.h
# End Source File
# Begin Source File

SOURCE=.\ring_vm.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmcurl.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmdll.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmfile.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmgc.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmgcdata.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmlistfuncs.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmmath.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmmysql.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmodbc.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmopenssl.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmos.h
# End Source File
# Begin Source File

SOURCE=.\ring_vmrefmeta.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
