###############################################################################
##                        BrainDead GNU Makefile [Windows|MinGW-w64] Ver 1.0 ##
###############################################################################

TOPDIR		:= $(shell cd ../../ && pwd)
TARGETDIR	= $(TOPDIR)/Bin/Windows/$(ARCH)_$(BITTYPE)
OBJSDIR		= $(TOPDIR)/Obj/Windows/$(ARCH)/$(BITTYPE)/MinGW-w64/$(MINGWW64VER)/$(BUILD)

SOURCEDIR	= Source ../Common/Source ../Common/Source/OGL ../Common/Source/OAL

TARGET	:= BrainDead
OUTFILE = $(TARGETDIR)/$(TARGET)_$(MINGWW64VER).exe

PLATFORM		:= Windows
BUILD_PLATFORM	:= WINDOWS
ARCH		:= X86
BITTYPE		:= 32

MINGWW64VER = $(shell $(CPP) -dumpversion)
64BIT ?= False

ifneq ($(64BIT), False)
BITTYPE	= 64
MINGW_PREFIX	= x86_64-w64-mingw32
else
MINGW_PREFIX	= i686-w64-mingw32
endif

CPP	= $(MINGW_PREFIX)-g++
LD	= $(MINGW_PREFIX)-ld
AS	= $(MINGW_PREFIX)-as
RC	= $(MINGW_PREFIX)-windres

CPPFLAGS	=	-c -D "WIN32" -D "_WINDOWS" -D "_UNICODE" -D "UNICODE" \
				-D "BUILD_$(BUILD_DEF)" -D "PLATFORM_$(BUILD_PLATFORM)" \
				-D "PLATFORM_$(BUILD_PLATFORM)_$(ARCH)" \
				-D "PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)" \
				-D "BITSIZE_$(BITTYPE)" -D "ARCH_$(ARCH)" \
				-I"Headers" -I"$(TOPDIR)/Source/Common/Headers"
LINK		=	-lopengl32 -luser32 -lkernel32 -lgdi32 -lm -lgcc -lstdc++
LINKFLAGS	=	-L/usr/$(MINGW_PREFIX)/sys-root/mingw/lib \
				-L/lib/gcc/$(MINGW_PREFIX)/$(MINGWW64VER) \
				-Wl,--subsystem,windows

debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		CPPFLAGS += -Wall -g -D "_DEBUG"
debug:		TARGET := $(TARGET)D
debug:		$(TARGET)

release:	BUILD = Release
release:	BUILD_DEF = RELEASE
release:	CPPFLAGS += -O2 -D "NDEBUG"
release:	LINKFLAGS += -S
release:	$(TARGET)

profile:	BUILD = Profile
profile:	BUILD_DEF = PROFILE
profile:	CPPFLAGS += -Wall -g -D "_DEBUG" -O2
profile:	TARGET := $(TARGET)P
profile:	$(TARGET)

TARGETDIR:
	-mkdir -p $(TARGETDIR)

OBJSDIR:
	-mkdir -p $(OBJSDIR)

GITVERSION:
	cscript GitVersion.jse

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))

VPATH		:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

OBJS	= $(CPPFILES:.cpp=.o)

$(TARGET): GITVERSION OBJSDIR TARGETDIR $(OBJS)
	cd $(OBJSDIR) && $(CPP) -v -o "$(OUTFILE)" *.o -s $(LINKFLAGS) $(LINK)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o "$(OBJSDIR)/$@" "$<"

