# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = ../../../gbdk2020/gbdk-2020-git/build/gbdk/
# GBDK_HOME = ../../../
LCC = $(GBDK_HOME)bin/lcc

VERSION=0.85

# Alternate languages can be passed in as follows
# de en es fr it nl pt
# make LANG_CODE=<lang code>
ifndef LANG_CODE
	LANG_CODE=en
endif

CFLAGS += -DLANG_CODE=$(LANG_CODE)
# CFLAGS += -Wf--max-allocs-per-node50000
# CFLAGS += -Wf--max-allocs-per-node150000 # diminishing (but present) size returns after this
# CFLAGS += -Wf--max-allocs-per-node500000
# CFLAGS += -Wf--opt-code-size # This doesn't shrink code size much vs -Wf--max-allocs-per-node150000

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=gb pocket

# Configure platform specific LCC flags here:
LCCFLAGS_gb      = -Wm-yc # ColorNo MBC  Wl-yt0x1B # Set an MBC for banking (1B-ROM+MBC5+RAM+BATT)
LCCFLAGS_pocket  = -Wm-yc # No MBC -Wl-yt0x1B # Usually the same as required for .gb
LCCFLAGS_duck    = # No MBC -Wl-yt0x1B # Usually the same as required for .gb
LCCFLAGS_gbc     = # No MBC -Wl-yt0x1B -Wm-yc # Same as .gb with: -Wm-yc (gb & gbc) or Wm-yC (gbc exclusive)
LCCFLAGS_sms     =
LCCFLAGS_gg      =

LCCFLAGS += $(LCCFLAGS_$(EXT)) # This adds the current platform specific LCC Flags


# Set ROM name (11 chars max in CGB land)
LCCFLAGS += -Wm-yn"GB-WORDYL"

# No autobanking needed for 32k ROM
# LCCFLAGS += -Wl-j -Wm-yoA -Wm-ya4 -autobank -Wb-ext=.rel -Wb-v # MBC + Autobanking related flags
LCCFLAGS += -debug # Uncomment to enable debug output
# LCCFLAGS += -v     # Uncomment for lcc verbose output


# You can set the name of the ROM file here
PROJECTNAME = GBWORDYL_$(VERSION)_$(LANG_CODE)

# Add language directory to include path
CFLAGS += -Wf-I"$(LANGDIR)/"
CFLAGS += -debug
CFLAGS += -Wf-MMD

# Code size improvements continue to show up to 250000
# 15000 seems to balance code size improvements vs compile time
# CFLAGS += -Wf--max-allocs-per-node15000

# EXT?=gb # Only sets extension to default (game boy .gb) if not populated
SRCDIR      = src
LANGDIR     = $(SRCDIR)/lang_$(LANG_CODE)

OBJDIR      = obj/$(EXT)/$(LANG_CODE)

RESDIR      = res
BINDIR      = build/$(EXT)
MKDIRS      = $(OBJDIR) $(BINDIR) # See bottom of Makefile for directory auto-creation

BINS	    = $(OBJDIR)/$(PROJECTNAME).$(EXT)
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c)))
CSOURCES    += $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
CSOURCES_LANG += $(foreach dir,$(LANGDIR),$(notdir $(wildcard $(dir)/*.c)))

ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))

OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o)
OBJS        += $(ASMSOURCES:%.s=$(OBJDIR)/%.o)
OBJS        += $(CSOURCES_LANG:%.c=$(OBJDIR)/%.o)

# Builds all targets sequentially
all: $(TARGETS)

# Dependencies
DEPS = $(OBJS:%.o=%.d)

-include $(DEPS)

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

# Compile .c files in "src/<LANG_CODE>/" to .o object files
$(OBJDIR)/%.o:	$(LANGDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(CFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(CFLAGS) -S -o $@ $<PROJECTNAME

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $(OBJS)


langs:
	${MAKE} LANG_CODE=de
	${MAKE} LANG_CODE=en
	${MAKE} LANG_CODE=es
	${MAKE} LANG_CODE=fr
	${MAKE} LANG_CODE=it
	${MAKE} LANG_CODE=nl
	${MAKE} LANG_CODE=la
#   PT full answer file is too big
#	${MAKE} LANG_CODE=pt

langs-clean:
	${MAKE} clean LANG_CODE=de
	${MAKE} clean LANG_CODE=en
	${MAKE} clean LANG_CODE=es
	${MAKE} clean LANG_CODE=fr
	${MAKE} clean LANG_CODE=it
	${MAKE} clean LANG_CODE=nl
	${MAKE} clean LANG_CODE=la
#   PT full answer file is too big
#	${MAKE} LANG_CODE=pt

dictionaries: langs-compress

langs-compress:
	make -C compress compress-all-langs


romusage:
# Ignores failure if romusage not in path
	-romusage build/gb/GBWORDYL_$(VERSION)_$(LANG_CODE).noi; romusage build/gb/GBWORDYL_$(VERSION)_$(LANG_CODE).noi > romusage.txt

clean:
	@echo Cleaning
	@for target in $(TARGETS); do \
		$(MAKE) $$target-clean; \
	done

# Include available build targets
include Makefile.targets


# create necessary directories after Makefile is parsed but before build
# info prevents the command from being pasted into the makefile
ifneq ($(strip $(EXT)),)           # Only make the directories if EXT has been set by a target
$(info $(shell mkdir -p $(MKDIRS)))
endif
