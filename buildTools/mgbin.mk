# mgbin.mk
# Created for MaGe by Jason Detwiler, June 2005
#
# This is a makefile to include when a package has executables that need to be
# compiled. In the calling makefile, define the variable MGTARGETS to hold the
# names of all executables to be compiled (each should have an associated
# [name].cc file), and MGTARGETDEPS to contain the names of all packages on
# which the executables depend. mgbin.mk should be included at the BOTTOM
# of the user's makefile, after G4's binmake.gmk has been included.  See 
# database/GNUmakefile for an example.

#EXTRA_LINK_DEPENDENCIES += $(PACKAGES)

MGBINDIR = $(MAGEDIR)/bin/Linux-g++
# here dealing with the circular dependencies.
# we remove multiple declarations
MGTARGETDEPSORTED := $(sort $(MGTARGETDEPS))
# here removing the local library we are compiling if it's a dependency
# This probably means we should be moving things into different directories.
MGTARGETDEPSOBJFILTER := $(foreach package, $(filter-out $(name), $(MGTARGETDEPSORTED)), $(MGTMPDIR)/$(package)/obj.last)
MGTARGETDEPSOBJ := $(foreach package, $(MGTARGETDEPSORTED), $(MGTMPDIR)/$(package)/obj.last)
MGTARGETDEPFILES := $(foreach target, $(MGTARGETS), $(MGTMPDIR)/exe/$(target).d)
MGTARGETOBJLASTFILES := $(foreach target, $(MGTARGETS), $(MGTMPDIR)/exe/$(target).obj.last)
MGTARGETOBJFILES := $(foreach target, $(MGTARGETS), $(MGTMPDIR)/exe/$(target).o)
MGBINS := $(addprefix $(MGBINDIR)/,$(MGTARGETS))
MGBINLIBDEPS = $(foreach package,$(MGTARGETDEPS),$(MGTMPDIR)/$(package)/lib$(package).$(MGLIBEXT))
MGBINLIBDIRS = $(foreach package,$(MGTARGETDEPS),-L$(MGTMPDIR)/$(package))
MGBINLIBS = $(G4LIBDIR)/lib$(name).$(MGLIBEXT) $(MGBINLIBDEPS) $(filter-out $(MGLIBS), $(LDLIBS)) 
MGBINLIBS += -L$(MAGEDIR)/io/obj/ -lLegendRoot
MGBINDEPS = $(patsubst %, $(MGTMPDIR)/%.d, $(MGTARGETS))

ifndef GLOBALLIBS
  ifneq ($(G4INCLUDE_EXEC),1)
    LDLIBS2EXTRA += $(foreach package, $(MGTARGETDEPS), $(shell \
        G4TMP=$(G4TMP); export G4TMP; \
        if [ \( -f $(G4LIB)/$(G4SYSTEM)/liblist \
          -a -f $(G4LIB)/$(G4SYSTEM)/libname.map \) ]; then \
        $(G4LIB)/$(G4SYSTEM)/liblist \
          -d $(MGTMPDIR)/$(package) \
          < $(G4LIB)/$(G4SYSTEM)/libname.map; fi))
    LDLIBS2EXTRA += $(foreach target, $(MGTARGETS), $(shell \
        G4TMP=$(G4TMP); export G4TMP; \
        if [ \( -f $(G4LIB)/$(G4SYSTEM)/liblist \
          -a -f $(G4LIB)/$(G4SYSTEM)/libname.map \) ]; then \
        $(G4LIB)/$(G4SYSTEM)/liblist $(MGTMPDIR)/exe/$(target).d \
          < $(G4LIB)/$(G4SYSTEM)/libname.map; fi))
  endif
endif

.PHONY: mgbin cleanmgbin FORCE 

mgbin: lib $(MGBINS)

$(MGBINS): $(MGBINDIR)/%: $(MGTMPDIR)/exe/%.obj.last
	@if [ ! -d $(MGBINDIR) ] ; then mkdir $(MGBINDIR) ;fi
	@echo Making $@ ...
ifdef CPPVERBOSE
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(MGTMPDIR)/exe/$(notdir $@).o $(objects) $(LDFLAGS) $(MGBINLIBS)
else
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(MGTMPDIR)/exe/$(notdir $@).o $(objects) $(LDFLAGS) $(MGBINLIBS)
endif

$(MGTARGETDEPSOBJFILTER): FORCE
	@$(MAKE) -C $(MAGEDIR) $(notdir $(@D)).lib
# checking to see if we need to make rootso and then making it.
	@if grep -q "rootsomake.mk" $(MAGEDIR)/$(notdir $(@D))/GNUmakefile ; then $(MAKE) -C $(MAGEDIR) $(notdir $(@D)).rootso; fi

FORCE:

$(MGTARGETOBJLASTFILES): $(MGTARGETDEPSOBJ) $(MGTARGETOBJFILES) 
	@mkdir -p $(dir $@)
	@touch $@

$(MGTMPDIR)/exe/%.d: %.cc
	@mkdir -p $(dir $@)
	@echo Making dependency for file $< ...
	@set -e; g++ $(GPPFLAGS) $(CPPFLAGS) -w $< |\
	sed 's!$*\.o!$(MGTMPDIR)/exe/& $@!' > $@; [ -s $@ ] || rm -f $@
ifneq ($(MAKECMDGOALS),clean)
-include $(MGTARGETDEPFILES)
endif 

$(MGTMPDIR)/exe/%.o: %.cc
	@mkdir -p $(dir $@)
ifdef CPPVERBOSE
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUT_OBJ)$@ $<
else
	@echo Compiling $< ...
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUT_OBJ)$@ $<
endif

clean:: cleanmgbin

cleanmgbin:
	@rm -f $(MGBINS)
	@rm -f $(MGBINDEPS)
	@rm -f $(foreach target, $(MGTARGETS), $(MGTMPDIR)/exe/$(target).*)


