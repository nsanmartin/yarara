SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CXXFLAGS = -Wall -std=c++17 -I./include 
CC = g++

BUILD = build
TESTS_SRC = $(subst .cpp,, $(wildcard ./tests/*.cpp))
TESTS = $(subst ./tests/,, $(patsubst %,$(BUILD)/%,$(TESTS_SRC)))

OBJ=./obj
OBJS_SRC = $(subst .cpp,.o, $(wildcard ./src/*.cpp))
OBJS = $(subst ./src/,, $(patsubst %,$(OBJ)/%,$(OBJS_SRC)))


build/%: tests/%.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $< $(OBJS)  $(SDL_LDFLAGS)

yarara:
	gcc -Wall -pedantic -I./include -o ./build/$@ main.c src/yrr-*.c $(SDL_LDFLAGS)

tests: $(TESTS)


build:
	if [ ! -d build ]; then mkdir build; fi

obj: build
	if [ ! -d obj ]; then mkdir obj; fi


obj/%.o: src/%.cpp obj
	g++ $(CXXFLAGS) -c -o $@ $<

tags:
	ctags -R -e .


clean:
	rm build/*
