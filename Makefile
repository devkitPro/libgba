#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
-include $(DEVKITARM)/gba_rules

BUILD		:=	build
SOURCES		:=	src src/BoyScout
INCLUDES	:=	include

DATESTRING	:=	$(shell date +%Y)$(shell date +%m)$(shell date +%d)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	:=	-g -O3 -Wall -Wno-switch -Wno-multichar -mthumb -mthumb-interwork $(INCLUDE)
ASFLAGS	:=	-g -Wa,--warn -mthumb -mthumb-interwork

#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
export PATH		:=	$(DEVKITARM)/bin:$(PATH)


#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export TARGET	:=	$(CURDIR)/lib/libgba.a

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

PREFIX	:=	arm-elf-

export CC		:=	$(PREFIX)gcc
export AS		:=	$(PREFIX)as
export LD		:=	$(PREFIX)gcc
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

CFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export OFILES	:=	$(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/build

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d lib ] || mkdir -p lib
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile


clean:
	@echo clean ...
	@rm -fr $(BUILD) *.tar.bz2
	
dist: $(BUILD)
	@tar --exclude=*CVS* --exclude=*build* --exclude=*.bz2 -cvjf libgba-src-$(DATESTRING).tar.bz2 *
	@tar --exclude=*CVS* -cvjf libgba-$(DATESTRING).tar.bz2 include lib license.txt

install: dist
	mkdir -p $(INSTALLDIR)/libgba
	bzip2 -cd libgba-$(DATESTRING).tar.bz2 | tar -xv -C $(INSTALLDIR)/libgba


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
$(TARGET): $(OFILES)

#---------------------------------------------------------------------------------
%.a: $(OFILES)
	@echo $@
	@$(AR) rcs $@ $(OFILES)

-include $(DEPENDS)

endif
#---------------------------------------------------------------------------------
