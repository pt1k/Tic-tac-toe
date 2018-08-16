CXX := g++
CXXFLAGS := -Wall -g -std=c++11
TARGET := ttt
#LFLAGS := -ggdb
LFLAGS := -lncurses
RM := rm -f

CXXEXT	 = cc
OBJEXT	 = o
DEPEXT	 = d
SRCDIR   = src
BUILDDIR = build

#ifeq (0,$(gui))
# xxx = "gui == 0"
#else 
# xxx = "gui != 0"
#endif

# $(wildcard xxx/*.cc): get all .cc files in the directory xxx/"
SRCS := $(wildcard $(SRCDIR)/*.$(CXXEXT))
#OBJS = get each from SRCS by replacing extension CXXEXT with OBJEXT
#       and directory part by BUILDDIR
OBJS := $(addprefix $(BUILDDIR)/, $(patsubst %.$(CXXEXT),%.$(OBJEXT),$(notdir $(SRCS))))

DEPS := $(OBJS:.$(OBJEXT)=.$(DEPEXT))


.PHONY: clean all

all: $(TARGET)
#	@echo "xxx: " $(xxx)
#	@echo $(SRCS)
#	@echo "OBJS: " $(OBJS)
#	@echo "DEPS: " $(DEPS)

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

