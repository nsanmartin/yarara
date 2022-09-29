SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS = -Wall  -pedantic -I./include 
CC = g++

BUILD = build

SRCS=$(wildcard src/*.c)

yarara:
	gcc $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.c $(SRCS) $(SDL_LDFLAGS)

debug:
	gcc -g $(CFLAGS) $(SDL_CFLAGS) -o $(BUILD)/$@ main.c $(SRCS) $(SDL_LDFLAGS)


build:
	if [ ! -d build ]; then mkdir build; fi


tags:
	ctags -R -e .


clean:
	rm build/*
