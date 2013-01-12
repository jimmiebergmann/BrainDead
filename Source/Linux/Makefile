###############################################################################
#                                     BrainDead Makefile [Linux x86] Ver. 1.0 #
###############################################################################

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/Linux/$(ARCH)_$(BITTYPE)
export OBJSDIR		= $(TOPDIR)/Obj/Linux/$(ARCH)/$(BITTYPE)/GCC/$(GCCVER)/$(BUILD)
export DEPSDIR		= $(TOPDIR)/Deps/Linux/$(ARCH)/$(BITTYPE)/GCC/$(GCCVER)
endif
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
	CPPFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		= -lX11 -lGL -lrt
	LINKFLAGS	=
##### Check for forced 32-bit or 64-bit builds ################################
ifneq ($(64BIT), False)
	TOOL_PREFIX	=	x86_64-pc-linux-gnu
	CPPFLAGS_EXT	+=	-m64
	ARCH		=	X86
	BITTYPE		=	64
else
ifneq ($(32BIT), False)
	TOOL_PREFIX	=	i686-pc-linux-gnu
	CPPFLAGS_EXT	+=	-m32
	ARCH		= X86
	BITTYPE		= 32
else
##### Nothing forced.  Use what the machine reports ###########################
ifeq ($(UNAME_MACHINE), x86_64)
	TOOL_PREFIX	=	x86_64-pc-linux-gnu
	CPPFLAGS_EXT	+=	-m64
	ARCH		=	X86
	BITTYPE		=	64
endif
ifeq ($(UNAME_MACHINE), i686)
	TOOL_PREFIX	=	i686-pc-linux-gnu
	CPPFLAGS_EXT	+=	-m32
	ARCH		= X86
	BITTYPE		= 32
endif
endif
endif
endif

##### Tools ###################################################################
CPP = $(TOOL_PREFIX)-g++

##### Common compiler flags ###################################################
CPPFLAGS =	-c -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH) \
			-DPLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE) \
			-DBITSIZE_$(BITTYPE) -DARCH_$(ARCH) \
			-I$(TOPSRC)/Linux/Headers -I$(TOPSRC)/Common/Headers
##### Debug #######
debug:		BUILD		= Debug
debug:		BUILD_DEF	= DEBUG
debug:		TARGET		:= $(TARGET)D
debug:		CPPFLAGS		+= -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD		= Release
release:	BUILD_DEF	= RELEASE
release:	TARGET		:= $(TARGET)
release:	LINKFLAGS	+= -S
release:	CPPFLAGS		+= -O3 $(CPPFLAGS_EXT)
release:	$(TARGET)

##### Profile #####
profile:	BUILD		= Profile
profile:	BUILD_DEF	= PROFILE
profile:	TARGET		:= $(TARGET)P
profile:	CPPFLAGS		+= -O3 -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(CURDIR))

.PHONY: OBJSDIR TARGETDIR

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

VERSIONINFO:
	@printf "%s" "-------------------------- Generating Version Information "
	@printf "%s\n" "---------------------"
	@sh $(TOPSRC)/Linux/GitVersion.sh ./Headers/GitVersion.hpp
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))

export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

export OBJS	:= $(CPPFILES:.cpp=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@$(MAKE) --no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Linux/Makefile

else
##### In the intermediate build directory #####################################

$(TARGET): $(OBJS)
	@printf "\n\n%s" "-------------------------- MESSAGES FROM THE COMPILER --"
	@printf "%s\n" "-----------------------"
	@cat $(OBJSDIR)/*.msgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating: $(OUTFILE)... "
	@cd $(OBJSDIR) && $(CPP) -o $(OUTFILE) $(OBJS) $(SYSLIBS)
	@printf "[OK]\n"

%.o: %.cpp
	@printf "Compiling: $<... "
	@$(CPP) -MMD -MP -MF $(OBJSDIR)/$*.d $(CPPFLAGS) $(SYSIPATH) $< \
	-o $(OBJSDIR)/$@ 2> $(OBJSDIR)/$*.msgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	fi;\
	if [[ $$RETVAL != 0 ]]; then\
		printf "\n\n%s" "----------------------------------- ERROR ---------";\
		printf "%s\n" "----------------------------------";\
		cat $(OBJSDIR)/$*.msgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

DEPENDS	:= $(OBJFILES:.o=.d)

-include $(DEPENDS)

endif

.PHONY: clean
clean:
	@printf "Removing files from: $(TARGETDIR)... "
	@cd $(TARGETDIR) && rm -rf ./*
	@printf "[OK]\n"
	@printf "Removing files from: $(OBJSDIR)... "
	@cd $(OBJSDIR) && rm -rf ./*
	@printf "[OK]\n"

