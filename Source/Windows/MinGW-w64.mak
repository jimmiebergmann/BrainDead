###############################################################################
##                        BrainDead GNU Makefile [Windows|MinGW-w64] Ver 1.0 ##
###############################################################################

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/Windows/$(ARCH)_$(BITTYPE)
export OBJSDIR		= $(TOPDIR)/Obj/Windows/$(ARCH)/$(BITTYPE)/MinGW-w64/$(MINGWW64VER)/$(BUILD)
endif

SOURCEDIR	=	Source Resources ../Common/Source ../Common/Source/OGL \
				../Common/Source/OAL

TARGET	:= BrainDead
OUTFILE = $(TARGETDIR)/$(TARGET)_$(MINGWW64VER).exe

PLATFORM		:= Windows
BUILD_PLATFORM	:= WINDOWS
ARCH			:= X86
BITTYPE			:= 32
BUILD_TYPE		:= debug

MINGWW64VER = $(shell $(CPP) -dumpversion)
64BIT ?= False

ifneq ($(64BIT), False)
BITTYPE			= 64
MINGW_PREFIX	= x86_64-w64-mingw32
else
BITTYPE			= 32
MINGW_PREFIX	= i686-w64-mingw32
endif

##### Tools ###################################################################
CPP	= $(MINGW_PREFIX)-g++
LD	= $(MINGW_PREFIX)-ld
AS	= $(MINGW_PREFIX)-as
RC	= $(MINGW_PREFIX)-windres

CPPFLAGS	=	-c -D "WIN32" -D "_WINDOWS" -D "_UNICODE" -D "UNICODE" \
				-D "BUILD_$(BUILD_DEF)" -D "PLATFORM_$(BUILD_PLATFORM)" \
				-D "PLATFORM_$(BUILD_PLATFORM)_$(ARCH)" \
				-D "PLATFORM_$(BUILD_PLATFORM)_$(ARCH)_$(BITTYPE)" \
				-D "BITSIZE_$(BITTYPE)" -D "ARCH_$(ARCH)" \
				-I"$(TOPSRC)/Windows/Headers" -I"$(TOPSRC)/Common/Headers" \
				-I"/usr/$(MINGWW64VER)/usr/include" -std=c++0x
LINK		=	-lopengl32 -luser32 -lkernel32 -lgdi32 -lm -lgcc -lstdc++ \
				-lfreetype
LINKFLAGS	=	-L/usr/$(MINGW_PREFIX)/sys-root/mingw/lib \
				-L/lib/gcc/$(MINGW_PREFIX)/$(MINGWW64VER) \
				-Wl,--subsystem,windows
RCFLAGS		=	-D "UNICODE" -D "_UNICODE" -I"$(TOPSRC)/Windows/Resources" \
				-I"$(TOPSRC)/Windows/Headers" -l 0x0409

debug:		BUILD		= Debug
debug:		BUILD_TYPE	= debug
debug:		BUILD_DEF	= DEBUG
debug:		CPPFLAGS += -Wall -g -D "_DEBUG"
debug:		TARGET := $(TARGET)D
debug:		$(TARGET)

release:	BUILD		= Release
release:	BUILD_TYPE	= release
release:	BUILD_DEF	= RELEASE
release:	CPPFLAGS += -O2 -D "NDEBUG"
release:	LINKFLAGS += -Wl,-S
release:	TARGET := $(TARGET)
release:	$(TARGET)

profile:	BUILD		= Profile
profile:	BUILD_TYPE	= profile
profile:	BUILD_DEF	= PROFILE
profile:	CPPFLAGS += -Wall -g -D "_DEBUG" -O2
profile:	TARGET := $(TARGET)P
profile:	$(TARGET)


##### Build the object files while not in the intermediate build directory ####
ifneq ($(OBJSDIR), $(CURDIR))
TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

VERSIONINFO:
	@printf "%s" "-------------------------- Generating Version Information --"
	@printf "%s\n" "-------------------"
	@sh $(TOPSRC)/Windows/GitVersion.sh $(TOPSRC)/Windows/Headers/GitVersion.hpp
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
RCFILES		:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.rc)))

export VPATH		:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

export OBJS		:=	$(CPPFILES:.cpp=.o) \
					$(RCFILES:.rc=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime $(MAKE) \
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Windows/MinGW-w64.mak \
	$(BUILD_TYPE)
	@printf "\n%s" "----------------------------------------------------------"
	@printf "%s\n" "---------------------"
	@printf "Compile time: "
	@cat $(OBJSDIR)/compiletime
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

else
##### In the intermediate build directory #####################################
$(TARGET): $(OBJS)
	@printf "\n\n%s" "------------------------ MESSAGES FROM THE COMPILER ----"
	@printf "%s\n" "-----------------------"
	@cat $(OBJSDIR)/*.msgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating $(OUTFILE)... "
	@cd $(OBJSDIR) && $(CPP) -o "$(OUTFILE)" $(OBJS) -s $(LINKFLAGS) $(LINK)
	@printf "[OK]\n"

%.o: %.cpp
	@printf "Compiling $<... "
	@$(CPP) -MMD -MP -MF $(OBJSDIR)/$*.d $(CPPFLAGS) -o "$@" "$<" \
	2> $(OBJSDIR)/$*.msgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "----------------------------------- ERROR ---------";\
		printf "%s\n" "----------------------------";\
		cat $(OBJSDIR)/$*.msgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

%.o: %.rc
	@printf "Compiling $<... "
	@$(RC) $(RCFLAGS) -o "$(OBJSDIR)/$*.o" -i "$<" 2> $(OBJSDIR)/$*.msgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "----------------------------------- ERROR ---------";\
		printf "%s\n" "----------------------------";\
		cat $(OBJSDIR)/$*.msgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

-include $(OBJSDIR)/*.d

endif

.PHONY: clean
clean:
	@if [ ! -d "$(TARGETDIR)" ]; then\
		printf "Directory: $(TARGETDIR) does not exist\n";\
	else\
		printf "Removing files from: $(TARGETDIR)... ";\
		cd $(TARGETDIR) && rm -rf ./*;\
		printf "[OK]\n";\
	fi
	@if [ ! -d "$(OBJSDIR)" ]; then\
		printf "Directory: $(OBJSDIR) does not exist\n";\
	else\
		printf "Removing files from: $(OBJSDIR)... ";\
		cd $(OBJSDIR) && rm -rf ./*;\
		printf "[OK]\n";\
	fi


