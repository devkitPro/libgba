#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro)
endif
include $(DEVKITARM)/gba_rules

BUILD		:=	build
SOURCES		:=	src src/BoyScout src/disc_io
INCLUDES	:=	include build
DATA		:=	data

DATESTRING	:=	$(shell date +%Y)$(shell date +%m)$(shell date +%d)

ARCH	:=	-mthumb -mthumb-interwork

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	:=	-g -O3 -Wall -Wno-switch -Wno-multichar $(ARCH) $(INCLUDE)
ASFLAGS	:=	-g -Wa,--warn $(ARCH)

#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
export PATH		:=	$(DEVKITARM)/bin:$(PATH)


#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export TARGET	:=	$(CURDIR)/lib/libgba.a

export VPATH	:=	$(foreach dir,$(DATA),$(CURDIR)/$(dir)) $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

PREFIX	:=	arm-elf-

export CC	:=	$(PREFIX)gcc
export AS	:=	$(PREFIX)as
export LD	:=	$(PREFIX)gcc
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

export OFILES	:=	$(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/build

.PHONY: $(BUILD) clean docs

$(BUILD):
	@[ -d lib ] || mkdir -p lib
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

docs:
	doxygen libgba.dox

clean:
	@echo clean ...
	@rm -fr $(BUILD) *.tar.bz2

dist: $(BUILD)
	@tar --exclude=*CVS* --exclude=.svn --exclude=*build* --exclude=*.bz2 -cvjf libgba-src-$(DATESTRING).tar.bz2 include src data Makefile libgba_license.txt
	@tar --exclude=*CVS* --exclude=.svn -cvjf libgba-$(DATESTRING).tar.bz2 include lib libgba_license.txt

install: dist
	mkdir -p $(DEVKITPRO)/libgba
	bzip2 -cd libgba-$(DATESTRING).tar.bz2 | tar -xvf - -C $(DEVKITPRO)/libgba


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
$(TARGET): $(OFILES)

#---------------------------------------------------------------------------------
%.a: $(OFILES)
	@echo $@
	@rm -f $@
	@$(AR) rcs $@ $(OFILES)

%.fnt.o	:	%.fnt
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

endif
#---------------------------------------------------------------------------------
