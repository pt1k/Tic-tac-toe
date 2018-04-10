CXX := g++
#CXXFLAGS := -Wall -ggdb
CXXFLAGS := -Wall -g -std=c++11
TARGET := ttt
#LFLAGS := -ggdb
LFLAGS := 
RM := rm -f


# $(wildcard *.cc /xxx/xxx/*.cc): get all .cc files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cc)
# $(patsubst %.cc,%.o,$(SRCS)): substitute all ".cc" file name strings to ".o" file name strings
OBJS := $(patsubst %.cc,%.o,$(SRCS))

DEPS := $(SRCS:.cc=.depends)



.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJS) -o $(TARGET)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cc
	$(CXX) -MM $(CXXFLAGS) $< > $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

