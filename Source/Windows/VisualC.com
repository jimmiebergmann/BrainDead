TARGET = ZED$(ZEDTARGET).lib

COMMONDIR = ..\..\..
TARGETDIR = $(COMMONDIR)\Lib\Windows\$(ARCH)\$(BITTYPE)\VisualC\$(VCVER)\$(LIBTYPE)
OBJSDIR = $(COMMONDIR)\Obj\Windows\$(ARCH)\$(BITTYPE)\$(LIBTYPE)\VisualC\$(VCVER)\$(BUILD)\$(ZEDTARGET)
SOURCEDIR = Source
HEADERDIR = Headers
COMMONINCDIR = ..\..\Common\Headers

##### Tools #####
CPP = cl.exe
LD = link.exe
AR = lib.exe

VCVER = Unknown
##### Get the Visual Studio version based upon the compiler #####
!IF [..\CL_Ver_LE.bat 16]
VCVER = 2010
!ENDIF
!IF [..\CL_Ver_LE.bat 15]
VCVER = 2008
!ENDIF
!IF [..\CL_Ver_LE.bat 14]
VCVER = 2005
!ENDIF
!IF [..\CL_Ver_LE.bat 13]
VCVER = 2003
!ENDIF

!IFDEF DLL
DLLFLAGS = /D "ZED_DLL" /D "ZED_EXPORT" /D "_WINDLL" /D "_USRDLL"
LIBTYPE = DLL
!ELSE
DLLFLAGS = 
LIBTYPE = LIB
!ENDIF

!IFDEF RELEASE
BUILD = Release
CPPFLAGS = /O2 /MD /GL
LINKFLAGS = /INCREMENTAL:NO /LTCG
TARGET = ZED$(ZEDTARGET)
ZED_BUILD = RELEASE
!ELSEIFDEF PROFILE
BUILD = Profile
CPPFLAGS = /O2 /MDd /GL /Zi /D "_DEBUG" /Fd"$(TARGETDIR)\ZED$(ZEDTARGET)P.pdb"
LINKFLAGS = /DEBUG /INCREMENTAL:NO /LTCG /PDB:"$(TARGETDIR)\ZED$(ZEDTARGET)P_DLL.pdb"
TARGET = ZED$(ZEDTARGET)P
ZED_BUILD = PROFILE
!ELSE
BUILD = Debug
CPPFLAGS = /Wall /MDd /Zi /D "_DEBUG" /Fd"$(TARGETDIR)\ZED$(ZEDTARGET)D.pdb"
LINKFLAGS = /DEBUG /INCREMENTAL /PDB:"$(TARGETDIR)\ZED$(ZEDTARGET)D_DLL.pdb"
TARGET = ZED$(ZEDTARGET)D
ZED_BUILD = DEBUG
!ENDIF

##### Check for 64-bit compiler #####
!IF [..\64Bit_Check.bat]
BUILD_PLATFORM = WIN64_X86
MACHINE_TYPE = X64
ARCH = X86
BITTYPE = 64
!ELSE
BUILD_PLATFORM = WIN32_X86
MACHINE_TYPE = X86
ARCH = X86
BITTYPE = 32
!ENDIF

OBJS = $(OBJSDIR)\*.obj

COPYINCDIR = $(ZEDPATH)\include\Windows\$(ARCH)\$(BITTYPE)\VisualC
COPYLIBDIR = $(ZEDPATH)\lib\Windows\$(ARCH)\$(BITTYPE)\$(LIBTYPE)\VisualC\$(VCVER)

##### Copy the headers and the static and dynamic libraries over to the #####
##### desired installation path                                         #####
copyheaders: $(TARGET)
	if not exist "$(COPYINCDIR)" mkdir "$(COPYINCDIR)
	if not exist "$(COPYLIBDIR)" mkdir "$(COPYLIBDIR)
	xcopy Headers "$(COPYINCDIR)" /y
	xcopy "$(COMMONINCDIR)" "$(COPYINCDIR)" /y
	xcopy "$(TARGETDIR)\*.lib" "$(COPYLIBDIR)" /y
	xcopy "$(TARGETDIR)\*.dll" "$(COPYLIBDIR)" /y

##### Generates either a DLL or LIB #####
!IFDEF DLL
$(TARGET): $(OBJS) $(OBJSDIR) $(TARGETDIR)
	$(LD) /DLL $(LINKFLAGS) /LIBPATH:"$(TARGETDIR)" /OUT:"$(TARGETDIR)\$(TARGET).dll" /IMPLIB:"$(TARGETDIR)\$(TARGET).lib" /MACHINE:$(MACHINE_TYPE) /SUBSYSTEM:WINDOWS $(OBJSDIR)\*.obj $(ZEDLIBS)
!ELSE
$(TARGET): $(OBJS) $(OBJSDIR) $(TARGETDIR)
	$(AR) $(LINKFLAGS) /OUT:"$(TARGETDIR)\$(TARGET).lib" /MACHINE:$(MACHINE_TYPE) /SUBSYSTEM:WINDOWS $(OBJSDIR)\*.obj
!ENDIF

$(TARGETDIR):
	if not exist $(TARGETDIR) mkdir $(TARGETDIR)

$(OBJSDIR):
	if not exist $(OBJSDIR) mkdir $(OBJSDIR)

{$(SOURCEDIR)\}.cpp{$(OBJSDIR)\}.obj::
	$(CPP) $(CPPFLAGS) $(DLLFLAGS) /c /D "_WINDOWS" /D "WIN32" /D "ZED_BUILD_$(ZED_BUILD)" /D "ZED_PLATFORM_$(BUILD_PLATFORM)" /I "$(COMMONINCDIR)" $(ZEDINCDIR) $(CFLAGS) /Fo"$(OBJSDIR)\\" $<

