###############################################################################
#                                     BrainDead Makefile [Linux x86] Ver. 1.0 #
###############################################################################

TARGETDIR	= ../../Bin/$(PLATFORM)
OBJSDIR		= ../../Obj/$(PLATFORM)/$(BUILD)
SOURCEDIR	= Source

TARGET := BrainDead

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

CC = g++

CFLAGS_EXT =
ifeq ($(UNAME), Linux)
	CFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		= -lX11 -lGL -lrt
ifeq ($(UNAME_MACHINE), x86_64)
	BUILD_PLATFORM	= LINUX_X86_64
	PLATFORM		= Linux_x86_64
endif
ifeq ($(UNAME_MACHINE), i686)
	BUILD_PLATFORM	= LINUX_X86_32
	PLATFORM		= Linux_x86_32
endif
endif

##### Debug #######
debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CFLAGS = -c -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUILD_DEF = RELEASE
release:	TARGET := $(TARGET)
release:	CFLAGS = -c -O3 $(CFLAGS_EXT)
release:	$(TARGET)

##### Profile #####
profile:	BUILD = Profile
profile:	BUILD_DEF = PROFILE
profile:	TARGET := $(TARGET)P
profile:	CFLAGS = -c -O3 -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(notdir $(CURDIR)))

.PHONY: OBJSDIR TARGETDIR

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
COMFILES	:= $(foreach dir,../Common/Source,$(notdir $(wildcard $(dir)/*.cpp)))


###############
OBJS	= $(CPPFILES:.cpp=.o)
COBJS	= $(COMFILES:.cpp=.o)
HEADERS	= $(wildcard *.hpp)
###############

$(TARGET): OBJSDIR TARGETDIR $(OBJS) $(COBJS)
	cd $(OBJSDIR) && $(CC) -o ../$(TARGETDIR)/$(TARGET) $(OBJS) $(COBJS) $(SYSLIBS)

%.o: ../Common/Source/%.cpp
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

%.o: $(SOURCEDIR)/%.cpp 
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

