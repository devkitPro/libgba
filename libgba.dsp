# Microsoft Developer Studio Project File - Name="libgba" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=libgba - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libgba.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libgba.mak" CFG="libgba - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libgba - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "libgba - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "libgba - Win32 Release"

# PROP BASE Use_MFC
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f libgba.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libgba.exe"
# PROP BASE Bsc_Name "libgba.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "make -r"
# PROP Rebuild_Opt "/a"
# PROP Target_File "libgba.exe"
# PROP Bsc_Name "libgba.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "libgba - Win32 Debug"

# PROP BASE Use_MFC
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f libgba.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "libgba.exe"
# PROP BASE Bsc_Name "libgba.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "make -r"
# PROP Rebuild_Opt ""
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "libgba - Win32 Release"
# Name "libgba - Win32 Debug"

!IF  "$(CFG)" == "libgba - Win32 Release"

!ELSEIF  "$(CFG)" == "libgba - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\AffineSet.s
# End Source File
# Begin Source File

SOURCE=.\src\ArcTan.s
# End Source File
# Begin Source File

SOURCE=.\src\Compression.c
# End Source File
# Begin Source File

SOURCE=.\src\CpuSet.c
# End Source File
# Begin Source File

SOURCE=.\src\Div.s
# End Source File
# Begin Source File

SOURCE=.\src\DivArm.s
# End Source File
# Begin Source File

SOURCE=.\src\input.c
# End Source File
# Begin Source File

SOURCE=.\src\interrupt.c
# End Source File
# Begin Source File

SOURCE=.\src\IntrWait.s
# End Source File
# Begin Source File

SOURCE=.\src\MultiBoot.s
# End Source File
# Begin Source File

SOURCE=.\src\Reset.s
# End Source File
# Begin Source File

SOURCE=.\src\single_ints.s
# End Source File
# Begin Source File

SOURCE=.\src\Sound.s
# End Source File
# Begin Source File

SOURCE=.\src\Sqrt.s
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\gba_affine.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_base.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_compression.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_input.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_interrupt.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_macros.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_multiboot.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_sio.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_sound.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_systemcalls.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_types.h
# End Source File
# Begin Source File

SOURCE=.\include\gba_video.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
