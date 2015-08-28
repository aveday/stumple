CXX := g++
CXXFLAGS := -Wall -std=c++11 -Werror
BIN := stumble
LDFLAGS := -lm -lSDL2 -lSDL2_gfx -lSDL2_image -lBox2D

OBJS := stumble.o Entity.o World.o Graphics.o Control.o Clock.o \
	Model.o Character.o
SRCS := $(OBJS:.o=.cc)
DEPS := $(OBJS:.o=.d)

ifneq ($(MAKECMDGOALS),clean)
	-include $(DEPS)
endif

.DEFAULT_GOAL := all

.PHONY: default clean deps all
default: deps all

clean:
	rm -f $(OBJS) $(BIN) $(DEPS)
deps: $(DEPS)

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.d: %.cc
	$(CXX) -MM -MF $@ $<

