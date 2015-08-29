CC := g++
CPPFLAGS := -Wall -Wextra -std=c++11
BIN := stumble
LDFLAGS := -lm -lSDL2 -lSDL2_gfx -lSDL2_image -lBox2D
RM:= rm -rf

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:src/%.cc=obj/%.o)

all: $(BIN)

clean:
	@echo Cleaning...
	@$(RM) obj dep $(BIN)

$(BIN): $(OBJS)
	@echo Linking executable $(BIN)
	@$(CC) $(LDFLAGS) $(OBJS) -o $@

obj/%.o: src/%.cc
	@echo Compiling $<
	@mkdir -p dep/$(*D) obj/$(*D)
	@$(CC) $(CPPFLAGS) -I. -Isrc -MMD -MP -MF dep/$*.d -c -o $@ $<

-include $(OBJS:obj/%.o=dep/%.d)

.PHONY: all clean

