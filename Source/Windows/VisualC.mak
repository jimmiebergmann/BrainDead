###############################################################################
##                       BrainDead GNU Makefile [Windows|VisualC++] Ver. 1.0 ##
###############################################################################

##### Define the output directories ###########################################
TOPDIR		:= $(shell GetTopDir.bat %CD%)
TARGETDIR	= $(TOPDIR)\Bin\Windows\$(ARCH)_$(BITTYPE)
OBJSDIR		= $(TOPDIR)\Obj\Windows\$(ARCH)\$(BITTYPE)\VisualC\$(VCVER)\$(BUILD)

##### Specify where the source code files are #################################
SOURCEDIR	= Source ..\Common\Source ..\Common\Source\OGL ..\Common\Source\OAL

##### The base name for the project to be augmented based on build type #######
TARGET	:= BrainDead
OUTFILE	= $(TARGETDIR)\$(TARGET)_$(VCVER).exe

##### Define the directory and directive versions of the platform #############
PLATFORM		:= Windows
BUILD_PLATFORM	:= WINDOWS

##### Tools ###################################################################
CPP		:= cl.exe
LD		:= link.exe
AS		:= ml.exe
RC		:= rc.exe
CVTRES	:= cvtres.exe

##### Depending on the version of the compiler, use the 64- or 32-bit     #####
##### flags, and change the assembler if necessary                        #####
ARCH		:= X86
BITTYPE		:= 32
MACHINE_DEF	:= X86

ifeq ($(shell 64Bit_Check.bat),1)
BITTYPE		:= 64
MACHINE_DEF	:= X64
AS			:= ml64.exe
endif

##### Get the version of the compiler in use and map it to the Visual     #####
##### Studio version                                                      #####
VCVER := Unknown
ifeq ($(shell CL_Ver_LE.bat 16),1)
VCVER := 2010
endif
ifeq ($(shell CL_Ver_LE.bat 15),1)
VCVER := 2008
endif
ifeq ($(shell CL_Ver_LE.bat 14),1)
VCVER := 2005
endif
ifeq ($(shell CL_Ver_LE.bat 13),1)
VCVER := 2003
endif

##### Common flags to provide the compiler and linker with, as well as    #####
##### libraries to link against                                           #####
CPPFLAGS	=	/c /D"WIN32" /D"_WINDOWS" /D"_UNICODE" /D"UNICODE" \
				/D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" \
				/D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)" \
				/D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)" \
				/D"BITSIZE_$(BITTYPE)" /D"ARCH_$(ARCH)" \
				/I"Headers" /I"..\Common\Headers"
ASFLAGS		=	/c /D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)"
LINK		=	opengl32.lib kernel32.lib user32.lib gdi32.lib
LINKFLAGS	=	/MACHINE:$(MACHINE_DEF) /SUBSYSTEM:WINDOWS
RCFLAGS		=	/D"_UNICODE" /D"UNICODE" /I"Resources" /I"Headers" /l 0X0409
CVTRESFLAGS	=	/DEFINE:_UNICODE /DEFINE:UNICODE /MACHINE:$(MACHINE_DEF)

##### Debug ###################################################################
debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		CPPFLAGS += /Wall /MDd /Zi /D"_DEBUG" \
			/Fd"$(TARGETDIR)\$(TARGET)_$(VCVER).pdb"
debug:		LINKFLAGS += /DEBUG /INCREMENTAL
debug:		TARGET := $(TARGET)D
debug:		$(TARGET)

##### Release #################################################################
release:	BUILD = Release
release:	BUILD_DEF = RELEASE
release:	CPPFLAGS += /O2 /MD /GL /D "NDEBUG"
release:	LINKFLAGS += /INCREMENTAL:NO /LTCG
release:	TARGET := $(TARGET)
release:	$(TARGET)

##### Profile #################################################################
profile:	BUILD = Profile
profile:	BUILD_DEF = PROFILE
profile:	CPPFLAGS += /O2 /Wall /MDd /GL /Zi /D"_DEBUG" \
			/Fd"$(TARGETDIR)\$(TARGET)_$(VCVER).pdb"
profile:	LINKFLAGS += /DEBUG /INCREMENTAL:NO /LTCG
profile:	TARGET := $(TARGET)P
profile:	$(TARGET)

##### Create directories ######################################################
TARGETDIR:
	if not exist $(TARGETDIR) mkdir $(TARGETDIR)

OBJSDIR:
	if not exist $(OBJSDIR) mkdir $(OBJSDIR)

GITVERSION:
	cscript GitVersion.jse

##### Seek out the C++ and Assembly files from the SOURCEDIR directories  #####
##### defined at the beginning of this Makefile                           #####
CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
ASMFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.asm)))
RESFILES	:= $(notdir $(wildcard *.rc))

VPATH		:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

##### Match file.[ext] and use it to generate file.obj ########################
OBJS	:=	$(CPPFILES:.cpp=.obj) \
			$(ASMFILES:.asm=.obj) \
			$(RESFILES:.rc=.obj)

##### The main attraction #####################################################
$(TARGET): GITVERSION OBJSDIR TARGETDIR $(OBJS)
	cd $(OBJSDIR) && $(LD) /OUT:"$(OUTFILE)" *.obj $(LINKFLAGS) $(LINK)

%.obj: %.cpp
	$(CPP) $(CPPFLAGS) /Fo"$(OBJSDIR)\$@" $<

%.obj: %.asm
	$(AS) $(ASFLAGS) /Fo"$(OBJSDIR)\$@" /Zi "$<"

%.obj: %.res
	$(CVTRES) $(CVTRESFLAGS) /OUT:"$(OBJSDIR)\$@" "$(OBJSDIR)\$<"

%.res: %.rc
	$(RC) $(RCFLAGS) /Fo"$(OBJSDIR)\$@" $<
