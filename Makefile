CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11
BIN := stumble
LDFLAGS := -lm -lSDL2 -lSDL2_gfx -lSDL2_image -lBox2D
CLEAN := rm -f

.DEFAULT_GOAL := all

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
DEPS := $(SRCS:.cc=.d)

ifneq ($(MAKECMDGOALS),clean)
	-include $(DEPS)
endif

.PHONY: all clean

all: $(BIN)
	@echo Finished!

clean:
	@echo Cleaning...
	@$(CLEAN) $(OBJS) $(BIN) $(DEPS)

$(BIN): $(DEPS) $(OBJS)
	@echo Linking executable $(BIN)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN) $(OBJS)

$(OBJS): %.o : %.cc %.d
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEPS): %.d : %.cc %.h
	@echo Generating dependencies for $<
	@$(CXX) -MM -MF $@ $<

