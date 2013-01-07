###############################################################################
##                       BrainDead GNU Makefile [Windows|VisualC++] Ver. 1.0 ##
###############################################################################
TARGETDIR	= ..\..\Bin\$(PLATFORM)
OBJSDIR		= ..\..\Obj\$(PLATFORM)\$(BUILD)
SOURCEDIR	= Source

TARGET := BrainDead

PLATFORM = Windows
BUILD_PLATFORM = WINDOWS_X86_32
##### Tools #####
CPP		= cl.exe
LD		= link.exe

VCVER = Unknown

CPPFLAGS = /D"_UNICODE" /D"UNICODE"

debug: BUILD = Debug
debug: BUILD_DEF = DEBUG
debug: CPPFLAGS += /Wall /MDd /Zi /D "_DEBUG" /Fd"$(TARGETDIR)\$(TARGET).pdb"
debug: LINKFLAGS = /DEBUG /INCREMENTAL
debug: LINK = opengl32.lib kernel32.lib user32.lib gdi32.lib
debug: TARGET = BrainDeadD
debug: $(TARGET)

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
	cd $(OBJSDIR) && $(LD) $(LINKFLAGS) /OUT:"..\$(TARGETDIR)\$(TARGET).exe" *.obj $(LINKFLAGS) /MACHINE:X86 /SUBSYSTEM:WINDOWS $(LINK)

%.obj: $(SOURCEDIR)\%.cpp
	$(CPP) $(CPPFLAGS) /D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" /D"PLATFORM_WINDOWS" /c /I"Headers" /I"../Common/Headers" /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\%.cpp
	$(CPP) $(CPPFLAGS) /D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" /D"PLATFORM_WINDOWS" /c /I"Headers" /I"../Common/Headers" /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\OGL\%.cpp
	$(CPP) $(CPPFLAGS) /D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" /D"PLATFORM_WINDOWS" /c /I"Headers" /I"../Common/Headers" /Fo"$(OBJSDIR)\$@" $<

%.obj: ..\Common\Source\OAL\%.cpp
	$(CPP) $(CPPFLAGS) /D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" /D"PLATFORM_WINDOWS" /c /I"Headers" /I"../Common/Headers" /Fo"$(OBJSDIR)\$@" $<

