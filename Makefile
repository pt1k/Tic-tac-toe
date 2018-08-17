ifndef ($(nogui))
 nogui = 0
endif

RM 		  := rm -f
TARGET 	  := ttt
CXX 	  := g++
CXXFLAGS  := -Wall -g -std=c++11
LFLAGS    := 
ifneq (0, $(nogui))
 CXXFLAGS += -DNOGUI
else 
 LFLAGS   += -lncurses
endif

CXXEXT	 = cc
OBJEXT	 = o
DEPEXT	 = d
SRCDIR   = src
BUILDDIR = build

# $(wildcard xxx/*.cc): get all .cc files in the directory xxx/"
#SRCS := $(wildcard $(SRCDIR)/*.$(CXXEXT))
SRCS    := $(SRCDIR)/ttt.cc \
           $(SRCDIR)/engine.cc \
		   $(SRCDIR)/game.cc \
		   $(SRCDIR)/console.cc \
		   $(SRCDIR)/computermove.cc \
		   $(SRCDIR)/rules.cc
GUISRCS := $(SRCDIR)/gui.cc \
           $(SRCDIR)/curse.cc
ifeq (0,$(nogui))
  SRCS += $(GUISRCS)
endif

#OBJS = get each from SRCS by replacing extension CXXEXT with OBJEXT
#       and directory part by BUILDDIR
OBJS := $(addprefix $(BUILDDIR)/, $(patsubst %.$(CXXEXT),%.$(OBJEXT),$(notdir $(SRCS))))

DEPS := $(OBJS:.$(OBJEXT)=.$(DEPEXT))


.PHONY: show clean all 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LFLAGS) -o $(TARGET)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(CXXEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.$(DEPEXT): $(SRCDIR)/%.$(CXXEXT)
	@mkdir -p $(dir $@)
	$(CXX) -MM $(CXXFLAGS) -MT $(BUILDDIR)/$*.$(OBJEXT) $< > $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

show:
	@echo "nogui: " $(nogui)
	@echo "CXXFLAGS: " $(CXXFLAGS)
	@echo "LFLAGS:   " $(LFLAGS)
	@echo "SRCS: " $(SRCS)
	@echo "OBJS: " $(OBJS)
#	@echo "DEPS: " $(DEPS)
