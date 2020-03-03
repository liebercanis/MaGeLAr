include $(MGDODIR)/buildTools/config.mk
# Give the list of applications, which must be the stems of cc files with 'main'.  There
# can be more than one.  
APPS =  anaGe makeWaves anaGermanium 
# The next two lines are important
SHLIB =
ARCHIVE =
TAMDIR ?= $(ROOTSYS)
# Include the correct flags,
INCLUDEFLAGS = $(CLHEP_INCLUDE_FLAGS) -I$(MGDODIR)/Base -I$(MGDODIR)/Root -I$(MGDODIR)/Transforms -I$(MAGEDIR)/io/obj 
INCLUDEFLAGS += -I$(MGDODIR)/Majorana -I$(MGDODIR)/MJDB $(ROOT_INCLUDE_FLAGS) -I$(TAMDIR)/inc -I$(TAMDIR)/include -I$(MGDODIR)/Tabree

LIBFLAGS = -L$(MGDODIR)/lib -lMGDORoot -lMGDOBase -lMGDOTransforms -lMGDOMajorana -lMGDOGerdaTransforms -lMGDOMJDB -lMGDOTabree -lLegendRoot
LIBFLAGS += $(ROOT_LIB_FLAGS) -L/usr/local/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTDataFrame -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic -lSpectrum -L$(TAMDIR)/lib -lTAM -L/$(CLHEP_LIB_DIR) -lCLHEP-2.4.1.0 -lCLHEP-Random-2.4.1.0 -lCLHEP-RandomObjects-2.4.1.0

include $(MGDODIR)/buildTools/BasicMakefile
