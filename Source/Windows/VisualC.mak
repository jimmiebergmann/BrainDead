###############################################################################
##                       BrainDead GNU Makefile [Windows|VisualC++] Ver. 1.0 ##
###############################################################################
TARGETDIR	= $(TOPDIR)\Bin\Windows\$(ARCH)_$(BITTYPE)
OBJSDIR		= $(TOPDIR)\Obj\Windows\$(ARCH)\$(BITTYPE)\VisualC\$(VCVER)\$(BUILD)
SOURCEDIR	= Source

TARGET := BrainDead
PLATFORM = Windows

BUILD_PLATFORM = WINDOWS

TOPDIR = $(shell GetTopDir.bat %CD%)

##### Tools #####
CPP		= cl.exe
LD		= link.exe
ARCH = X86
BITTYPE = 32
VCVER := Unknown
VC2010 = $(shell CL_Ver_LE.bat 16)
ifeq ($(VS2010),1)
VCVER := 2010
endif
LINK = opengl32.lib kernel32.lib user32.lib gdi32.lib
CPPFLAGS = /D"_UNICODE" /D"UNICODE" /D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" /D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)" /c /I"Headers" /I"..\Common\Headers"

##### Debug #####
debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		CPPFLAGS += /Wall /MDd /Zi /D "_DEBUG" /Fd"$(TARGETDIR)\$(TARGET).pdb"
debug:		LINKFLAGS = /DEBUG /INCREMENTAL
debug:		TARGET := $(TARGET)D
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUILD_DEF = RELEASE
release:	CPPFLAGS += /O2 /MD /GL /D "NDEBUG"
release:	LINKFLAGS = /INCREMENTAL:NO /LTCG
release:	TARGET := $(TARGET)
release:	$(TARGET)

OBJS = $(OBJSDIR)\*.obj

TARGETDIR:
	if not exist $(TARGETDIR) mkdir $(TARGETDIR)

OBJSDIR:
	if not exist $(OBJSDIR) mkdir $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
COMFILES	:= $(foreach dir,..\Common\Source,$(notdir $(wildcard $(dir)/*.cpp)))
OGLFILES	:= $(foreach dir,..\Common\Source\OGL,$(notdir $(wildcard $(dir)/*.cpp)))
OALFILES	:= $(foreach dir,..\Common\Source\OAL,$(notdir $(wildcard $(dir)/*.cpp)))

OBJS	= $(CPPFILES:.cpp=.obj)
COBJS	= $(COMFILES:.cpp=.obj)
OGLOBJS	= $(OGLFILES:.cpp=.obj)
OALOBJS	= $(OALFILES:.cpp=.obj)

$(TARGET): OBJSDIR TARGETDIR $(OBJS) $(OALOBJS) $(OGLOBJS) $(COBJS)
	cd $(OBJSDIR) && $(LD) $(LINKFLAGS) /OUT:"$(TARGETDIR)\$(TARGET).exe" *.obj $(LINKFLAGS) /MACHINE:X86 /SUBSYSTEM:WINDOWS $(LINK)

%.obj: $(SOURCEDIR)\%.cpp
	$(CPP) $(CPPFLAGS) /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\%.cpp
	$(CPP) $(CPPFLAGS) /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\OGL\%.cpp
	$(CPP) $(CPPFLAGS) /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\OAL\%.cpp
	$(CPP) $(CPPFLAGS) /Fo"$(OBJSDIR)\$@" $<

