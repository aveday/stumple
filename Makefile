CXX=g++
CFLAGS=-Wall -std=c++11
BIN=engine
LDFLAGS=-lm -lSDL2 -lSDL2_gfx -lSDL2_image -lBox2D
DEPS=engine.h Geometry.h Entity.h World.h Graphics.h Control.h Clock.h Image.h
OBJS=$(subst .h,.o,$(DEPS))

.PHONY: default
default: all

.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)

%.o: %.cc %.h
	$(CXX) $(CFLAGS) -c -o $@ $<

all: $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(OBJS)
