###############################################################################
##                       BrainDead GNU Makefile [Windows|VisualC++] Ver. 1.0 ##
###############################################################################

##### Define the output directories ###########################################
ifndef TOPDIR
export TOPDIR		:= $(shell GetTopDir.bat %CD%)
export TOPSRC		= $(TOPDIR)\Source
export TARGETDIR	= $(TOPDIR)\Bin\Windows\$(ARCH)_$(BITTYPE)
export OBJSDIR		= $(TOPDIR)\Obj\Windows\$(ARCH)\$(BITTYPE)\VisualC\$(VCVER)\$(BUILD)
endif

##### Specify where the source code files are #################################
SOURCEDIR	= Source ..\Common\Source ..\Common\Source\OGL ..\Common\Source\OAL

##### The base name for the project to be augmented based on build type #######
TARGET	:= BrainDead
OUTFILE	= $(TARGETDIR)\$(TARGET)_$(VCVER).exe

##### Define the directory and directive versions of the platform #############
PLATFORM		:= Windows
BUILD_PLATFORM	:= WINDOWS

##### Tools ###################################################################
CPP		:= cl.exe -nologo
LD		:= link.exe -nologo
AS		:= ml.exe /nologo
RC		:= rc.exe -nologo
CVTRES	:= cvtres.exe -nologo

##### Depending on the version of the compiler, use the 64- or 32-bit     #####
##### flags, and change the assembler if necessary                        #####
ifndef BITTYPE
ifeq ($(shell 64Bit_Check.bat),1)
export BITTYPE		:= 64
export ARCH			:= X86
export MACHINE_DEF	:= X64
export AS	 		:= ml64.exe /nologo
else
export BITTYPE		:= 32
export ARCH			:= X86
export MACHINE_DEF	:= X86
export AS			:= ml.exe /nologo
endif
endif

##### Get the version of the compiler in use and map it to the Visual     #####
##### Studio version                                                      #####
ifndef VCVER
ifeq ($(shell CL_Ver_LE.bat 16),1)
export VCVER := 2010
endif
ifeq ($(shell CL_Ver_LE.bat 15),1)
export VCVER := 2008
endif
ifeq ($(shell CL_Ver_LE.bat 14),1)
export VCVER := 2005
endif
ifeq ($(shell CL_Ver_LE.bat 13),1)
export VCVER := 2003
endif
endif

##### Common flags to provide the compiler and linker with, as well as    #####
##### libraries to link against                                           #####
CPPFLAGS	=	/c /D"WIN32" /D"_WINDOWS" /D"_UNICODE" /D"UNICODE" \
				/D"BUILD_$(BUILD_DEF)" /D"PLATFORM_$(BUILD_PLATFORM)" \
				/D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)" \
				/D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)" \
				/D"BITSIZE_$(BITTYPE)" /D"ARCH_$(ARCH)" \
				/I"$(TOPSRC)\Windows\Headers" /I"$(TOPSRC)\Common\Headers"
ASFLAGS		=	/c /D"PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)"
LINK		=	opengl32.lib kernel32.lib user32.lib gdi32.lib freetype.lib
LINKFLAGS	=	/MACHINE:$(MACHINE_DEF) /SUBSYSTEM:WINDOWS
RCFLAGS		=	/D"_UNICODE" /D"UNICODE" /I"Resources" /I"Headers" /l 0X0409
CVTRESFLAGS	=	/DEFINE:_UNICODE /DEFINE:UNICODE /MACHINE:$(MACHINE_DEF)

##### Debug ###################################################################
debug:		BUILD = Debug
debug:		BUILD_TYPE = debug
debug:		BUILD_DEF = DEBUG
debug:		CPPFLAGS_BUILD += $(CPPFLAGS) /Wall /MDd /Zi /D"_DEBUG" \
			/Fd"$(TARGETDIR)\$(TARGET)_$(VCVER).pdb"
debug:		LINKFLAGS += /DEBUG /INCREMENTAL
debug:		TARGET := $(TARGET)D
debug:		$(TARGET)

##### Release #################################################################
release:	BUILD = Release
release:	BUILD_TYPE = release
release:	BUILD_DEF = RELEASE
release:	CPPFLAGS += /O2 /MD /GL /D "NDEBUG"
release:	LINKFLAGS += /INCREMENTAL:NO /LTCG
release:	TARGET := $(TARGET)
release:	$(TARGET)

##### Profile #################################################################
profile:	BUILD = Profile
profile:	BUILD_TYPE = profile
profile:	BUILD_DEF = PROFILE
profile:	CPPFLAGS += /O2 /Wall /MDd /GL /Zi /D"_DEBUG" \
			/Fd"$(TARGETDIR)\$(TARGET)_$(VCVER).pdb"
profile:	LINKFLAGS += /DEBUG /INCREMENTAL:NO /LTCG
profile:	TARGET := $(TARGET)P
profile:	$(TARGET)

UOBJSDIR = $(subst \,/,$(OBJSDIR))
##### Build the intermediate files while not in the intermediate directory ####
ifneq ($(UOBJSDIR), $(CURDIR))
##### Create directories ######################################################
TARGETDIR:
	@if not exist $(TARGETDIR) mkdir $(TARGETDIR)

OBJSDIR:
	@if not exist $(OBJSDIR) mkdir $(OBJSDIR)

VERSIONINFO:
	@echo Gen Ver
	@cscript -nologo $(TOPSRC)\Windows\GitVersion.jse

##### Seek out the C++ and Assembly files from the SOURCEDIR directories  #####
##### defined at the beginning of this Makefile                           #####
CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
ASMFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.asm)))
RESFILES	:= $(notdir $(wildcard *.rc))

export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

##### Match file.[ext] and use it to generate file.obj ########################
export OBJS	:=	$(CPPFILES:.cpp=.obj) \
				$(ASMFILES:.asm=.obj) \
				$(RESFILES:.rc=.obj)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@$(MAKE) --no-print-directory -C $(OBJSDIR) \
	-f $(TOPSRC)/Windows/VisualC.mak $(BUILD_TYPE)

else

##### The main attraction #####################################################
$(TARGET): $(OBJS)
	@printf "Linking $(OUTFILE)... "
	@$(LD) /OUT:"$(OUTFILE)" $(OBJS) $(LINKFLAGS) $(LINK)
	@printf "[OK]\n"

%.obj: %.cpp
	@printf "Compiling $<... "
	@$(CPP) $(CPPFLAGS_BUILD) /Fo"$(OBJSDIR)\$@" $< > $(OBJSDIR)/$*.msga
	@$(CPP) /W0 /Zs /showIncludes $(CPPFLAGS) $< | sed -e "/Microsoft SDKs/Id" | sed -e "/Microsoft Visual Studio/Id" | sed -e "s/Note: Including file://I" | sed -e "s/^[ \t]*//" | sed -e "s/.cpp/.obj:/" | sed -e "$$ ! s/$$/ \\/" > $(OBJSDIR)/$*.d
	@printf "[OK]\n"

%.obj: %.asm
	@printf "Assembling $<... "
	@$(AS) $(ASFLAGS) /Fo"$(OBJSDIR)\$@" /Zi "$<"
	@printf "[OK]\n"

%.obj: %.res
	@$(CVTRES) $(CVTRESFLAGS) /OUT:"$(OBJSDIR)\$@" "$(OBJSDIR)\$<"

%.res: %.rc
	@$(RC) $(RCFLAGS) /Fo"$(OBJSDIR)\$@" $<

-include $(OBJSDIR)/*.d
endif

