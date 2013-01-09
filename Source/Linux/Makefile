###############################################################################
#                                     BrainDead Makefile [Linux x86] Ver. 1.0 #
###############################################################################

TOPDIR		:= $(shell cd ../../ && pwd)
TARGETDIR	= $(TOPDIR)/Bin/Linux/$(ARCH)_$(BITTYPE)
OBJSDIR		= $(TOPDIR)/Obj/Linux/$(ARCH)/$(BITTYPE)/GCC/$(GCCVER)/$(BUILD)
SOURCEDIR	= Source ../Common/Source ../Common/Source/OGL ../Common/Source/OAL

TARGET	:=	BrainDead
OUTFILE	=	$(TARGETDIR)/$(TARGET)_$(GCCVER)

PLATFORM		:= Linux
BUILD_PLATFORM	:= LINUX
ARCH			:= X86
BITTYPE			:= 32

GCCVER	= $(shell $(CPP) -dumpversion)

32BIT ?= False
64BIT ?= False

##### Get the machine type to determine which set of libraries to use #########
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

ifeq ($(UNAME), Linux)
	CFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		= -lX11 -lGL -lrt
	LINKFLAGS	=
##### Check for forced 32-bit or 64-bit builds ################################
ifneq ($(64BIT), False)
	TOOL_PREFIX	=	x86_64-pc-linux-gnu
	CFLAGS_EXT	+=	-m64
	ARCH		=	X86
	BITTYPE		=	64
else
ifneq ($(32BIT), False)
	TOOL_PREFIX	=	i686-pc-linux-gnu
	CFLAGS_EXT	+=	-m32
	ARCH		= X86
	BITTYPE		= 32
else
##### Nothing forced.  Use what the machine reports ###########################
ifeq ($(UNAME_MACHINE), x86_64)
	TOOL_PREFIX	=	x86_64-pc-linux-gnu
	CFLAGS_EXT	+=	-m64
	ARCH		=	X86
	BITTYPE		=	64
endif
ifeq ($(UNAME_MACHINE), i686)
	TOOL_PREFIX	=	i686-pc-linux-gnu
	CFLAGS_EXT	+=	-m32
	ARCH		= X86
	BITTYPE		= 32
endif
endif
endif
endif

##### Tools ###################################################################
CPP = $(TOOL_PREFIX)-g++

##### Common compiler flags ###################################################
CFLAGS	=	-c -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE) \
			-DBITSIZE_$(BITSIZE) -DARCH_$(ARCH) \
			-IHeaders -I$(TOPDIR)/Source/Common/Headers
##### Debug #######
debug:		BUILD		= Debug
debug:		BUILD_DEF	= DEBUG
debug:		TARGET		:= $(TARGET)D
debug:		CFLAGS		+= -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD		= Release
release:	BUILD_DEF	= RELEASE
release:	TARGET		:= $(TARGET)
release:	LINKFLAGS	+= -S
release:	CFLAGS		+= -O3 $(CFLAGS_EXT)
release:	$(TARGET)

##### Profile #####
profile:	BUILD		= Profile
profile:	BUILD_DEF	= PROFILE
profile:	TARGET		:= $(TARGET)P
profile:	CFLAGS		+= -O3 -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(notdir $(CURDIR)))

.PHONY: OBJSDIR TARGETDIR

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

VERSIONINFO:
	@echo "-------------------------- Generating Version Information ----------------"
	@sh ./GitVersion.sh
	@echo "--------------------------------------------------------------------------"

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))

VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

OBJS	:= $(CPPFILES:.cpp=.o)

$(TARGET): VERSIONINFO OBJSDIR TARGETDIR $(OBJS)
	cd $(OBJSDIR) && $(CPP) -v -o $(OUTFILE) $(OBJS) $(SYSLIBS)

%.o: %.cpp 
	$(CPP) $(CFLAGS) $(SYSIPATH) $< -o $(OBJSDIR)/$@

endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

